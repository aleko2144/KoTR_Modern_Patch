#include "STrailersPhysFix.h"
#include "..\utils\CPatch.h"
#include "..\utils\ConfigUtils.h"

#include "..\GameApp\Car_V.h"
#include "..\GameApp\Vehicle.h"

//#include <iostream>

float strailerMass_coeff_before = 0.7;
float strailerMass_coeff_after  = 0.9;

float tractorI_multp   = 1.0;
float strailerI_multp  = 1.0;

float steer_correction = 2.3;

bool applySteerCorrection;
char __fastcall OnCallCar_V_make_frs(int *carV, int edx, int a1){
	bool is_player_car = Car_V::isPlayerCarV(carV);
	bool is_has_trailer = Car_V::isTrailerAttached(carV);
	bool is_in_sim_mode = Car_V::isInSimulatorMode(carV);
	bool is_trailer_loaded = false;

	if (is_has_trailer){
		int *vehicle = (int*)*(int*)0x6F6930;
		is_trailer_loaded = Vehicle::isTrailerLoaded(vehicle);
	}

	//std::cout << is_trailer_loaded << std::endl;

	if (is_player_car && is_in_sim_mode && is_has_trailer && is_trailer_loaded){
		applySteerCorrection = true;
	} else {
		applySteerCorrection = false;
	}

	//std::cout << applySteerCorrection << std::endl;

	return Car_V::make_frs(carV, a1);
}

//steering func
double __cdecl OnCall4F4DF0(int mode, float steer, float speed_ms){
	double result = sub_4F4DF0(mode, steer, speed_ms);
	
	if (applySteerCorrection)
		result *= steer_correction;

	return result;
}

bool __fastcall OnCallProcessRoadtrainMovement(int *tractor){
	if (Vehicle::isInSimulatorMode(tractor)){
		strailerMass_coeff_before = 0.7;
		strailerMass_coeff_after  = 1.2;
	} else {
		strailerMass_coeff_before = 0.5;
		strailerMass_coeff_after  = 0.6;
	}

	if (!Vehicle::isTrailerLoaded(tractor)){
		strailerMass_coeff_before = 0.8;
		strailerMass_coeff_after  = 0.9;
	}

	return Vehicle::processRoadtrainMovement(tractor);
}

//What does this "patch" actually do:
//1) In the road train movement calculation function, it adjusts the parameters so that the semitrailer's mass is reduced and the tractor's mass
// is increased (a sort of weight transfer from the semitrailer to the tractor, although this isn't quite true).
//
//2) In the steering function, it simplifies steering in the same way as the game does in arcade mode. However, this change only applies when
// the game is in simulator mode and the player's trailer is loaded.
//
//3) Disables couple detach when the trailer is bouncing on uneven roads.
//
//All this "fixes" working bad at low FPS.

void STrailersPhysFix::injectHooks(){
	//Изначально сделано осенью-зимой 2025-го в рамках попытки сделать патч к игре только редактированием exe-файла, в итоге забросил этот проект,
	//так как редактированием лишь существующего кода игру полностью не поправить, а добавлять полностью новый код в уже откомпилированный exe - для меня это слишком)
	//
	//Originally made in the november-december of 2025 as part of an attempt to make a patch for the game using only editing the .exe file, I eventually abandoned this project,
	//since editing only the existing code alone won't completely fix the game, and adding completely new code to an already compiled .exe is too much for me :)
	//
	//What this code does (inside original roadtrain movement function):
	//1. before physical calculations:
	// mass correction:
	// local float strailerMass *= strailerMass_coeff_before
	// local float tractorMass   = tractorMass + strailerMass
	//
	// inertia vectors correction:
	// local Vector3 strailerI *= strailerI_multp
	// local Vector3 tractorI  *= trailerI_multp
	//
	// local float strailerMass *= strailerMass_coeff_after
	//
	//2. inside physical calculations:
	// replaces sqrt(strailerMass * tractorMass / (strailerMass + tractorMass));
	//       to sqrt(tractorMass  * tractorMass / (tractorMass  + tractorMass));
	//
	// also disables strailer detach at some events (to prevent the trailer from detaching when driving
	// on rough terrain - deserts or swamps, because this is very unrealistic)
	//
	//3. corrects steering function, adds multipling from arcade steering when tractor in simulator mode with attached semitrailer
	// otherwise steering limited too much so roadtrain don't turn it's moving direction
	//
	//This entire code replaces a section in the function where variables are reset that are used in code that is definitely never executed in the game.


	unsigned char mod_bytes[] = {0xD9, 0x44, 0x24, 0x28, 0xD8, 0x0D, 0x18, 0x17, 0x67, 0x00, 0xD9, 0x5C, 0x24, 0x28, 0xD9, 0x44, 0x24,
								 0x28, 0xD9, 0x44, 0x24, 0x24, 0xDE, 0xC1, 0xD9, 0x5C, 0x24, 0x24, 0xD9, 0x84, 0x24, 0x88, 0x01, 0x00,
								 0x00, 0xD8, 0x0D, 0x50, 0xC2, 0x64, 0x00, 0xD9, 0x9C, 0x24, 0x88, 0x01, 0x00, 0x00, 0xD9, 0x84, 0x24,
								 0x8C, 0x01, 0x00, 0x00, 0xD8, 0x0D, 0x50, 0xC2, 0x64, 0x00, 0xD9, 0x9C, 0x24, 0x8C, 0x01, 0x00, 0x00,
								 0xD9, 0x84, 0x24, 0x90, 0x01, 0x00, 0x00, 0xD8, 0x0D, 0x50, 0xC2, 0x64, 0x00, 0xD9, 0x9C, 0x24, 0x90,
								 0x01, 0x00, 0x00, 0xD9, 0x84, 0x24, 0x94, 0x01, 0x00, 0x00, 0xD8, 0x0D, 0xC8, 0xF3, 0x64, 0x00, 0xD9,
								 0x9C, 0x24, 0x94, 0x01, 0x00, 0x00, 0xD9, 0x84, 0x24, 0x98, 0x01, 0x00, 0x00, 0xD8, 0x0D, 0xC8, 0xF3,
								 0x64, 0x00, 0xD9, 0x9C, 0x24, 0x98, 0x01, 0x00, 0x00, 0xD9, 0x84, 0x24, 0x9C, 0x01, 0x00, 0x00, 0xD8,
								 0x0D, 0xC8, 0xF3, 0x64, 0x00, 0xD9, 0x9C, 0x24, 0x9C, 0x01, 0x00, 0x00, 0xD9, 0x44, 0x24, 0x28, 0xD8,
								 0x0D, 0x58, 0xC2, 0x64, 0x00, 0xD9, 0x5C, 0x24, 0x28, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
								 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

	CPatch::SetBytes(0x559262, &mod_bytes, sizeof(mod_bytes));

	CPatch::SetChar(0x559A28, 36); //args switch in sqrt() function
	CPatch::SetChar(0x559A30, 36);

	CPatch::SetInt(0x55A836, 0);   //disable strailer detach on bad roads

	//correction coeffs
	CPatch::SetPointer(0x559268, &strailerMass_coeff_before);
	CPatch::SetPointer(0x5592FC, &strailerMass_coeff_after);

	CPatch::SetPointer(0x5592C3, &tractorI_multp);
	CPatch::SetPointer(0x559287, &strailerI_multp);

	//redirect calls
	CPatch::RedirectCall(0x4F5131, &OnCall4F4DF0);
	CPatch::RedirectCall(0x4F556B, &OnCall4F4DF0);

	CPatch::RedirectCall(0x4F5CE1, &OnCallCar_V_make_frs);
	CPatch::RedirectCall(0x4F859F, &OnCallCar_V_make_frs);

	CPatch::RedirectCall(0x55D91C, &OnCallProcessRoadtrainMovement);

	//std::cout << "sizeof=" << sizeof(mod_bytes) << std::endl;
	//std::cout << "&steer_correction=" << std::hex << &steer_correction << std::endl;
}
