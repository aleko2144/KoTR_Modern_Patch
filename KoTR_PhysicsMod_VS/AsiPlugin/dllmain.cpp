#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <fstream>

#include "dllmain.h"

#include "detours.h"

using namespace std;

class CVector {
public:
	float x;
	float y;
	float z;
	CVector(){
		x = 0;
		y = 0;
		z = 0;
	}
	void setFromArgs(float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}
	void setFromPtr(float* ptr){
		x = ptr[0];
		y = ptr[1];
		z = ptr[2];
	}
	long double getLength(){
		return sqrt(x * x + y * y + z * z);
	}
	CVector CVector::normalize(){
		CVector result;
		float coeff = (1.0 / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
		result.x = this->x * coeff;
		result.y = this->y * coeff;
		result.z = this->z * coeff;
		return result;
	}
	CVector CVector::operator+ (const CVector& rhs){
		CVector result;
		result.x = this->x + rhs.x;
		result.y = this->y + rhs.y;
		result.z = this->z + rhs.z;
		return result;
	}
	CVector CVector::operator- (const CVector& rhs){
		CVector result;
		result.x = this->x - rhs.x;
		result.y = this->y - rhs.y;
		result.z = this->z - rhs.z;
		return result;
	}
	CVector CVector::operator* (const long double& rhs){
		CVector result;
		result.x = this->x * rhs;
		result.y = this->y * rhs;
		result.z = this->z * rhs;
		return result;
	}
	CVector CVector::operator* (const CVector& rhs){
		CVector result;
		result.x = this->x * rhs.x;
		result.y = this->y * rhs.y;
		result.z = this->z * rhs.z;
		return result;

	}
};

class CMatrix {
public:
	CVector right;
	CVector top;
	CVector at;
	CVector pos;
	CMatrix(){
		right.x = 0;
		right.y = 0;
		right.z = 0;

		top.x = 0;
		top.y = 0;
		top.z = 0;

		at.x = 0;
		at.y = 0;
		at.z = 0;

		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
	}
	CVector GetRadians(){
		CVector result;

		double cy = sqrt(this->at.z*this->at.z + this->at.x*this->at.x);

		if (cy > 16*FLT_EPSILON)
		{
			result.z = (float) atan2(this->right.y, this->top.y);
			result.x = (float) atan2(- this->at.y, (float) cy);
			result.y = (float) atan2(this->at.x, this->at.z);
		}
		else
		{
			result.z = (float) atan2(- this->top.x, this->right.x);
			result.x = (float) atan2(- this->at.y, (float) cy);
			result.y = 0;
		}

		return result;
	}
};


CVector CVector_MultiplyOnMatrix(CVector a1, CMatrix mtx){
	CVector result; 

	result.x = (mtx.right.x * a1.x) + (mtx.right.y * a1.y) + (mtx.right.z * a1.z);
	result.y = (mtx.top.x   * a1.x) + (mtx.top.y   * a1.y) + (mtx.top.z   * a1.z);
	result.z = (mtx.at.x    * a1.x) + (mtx.at.y    * a1.y) + (mtx.at.z    * a1.z);

	return result;	
}

void DisplayConsole(){
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

double _fastcall Car_V_getSemiTrailerSaddleLoad(DWORD* vehicle, DWORD EDX, CVector* v2){
	return 0.3;
}

CMatrix * _fastcall GetVehicleMatrix(DWORD* vehicle, CMatrix* v2){
	typedef CMatrix * (__thiscall * GetVehicleMatrix)(DWORD* vehicle, CMatrix* v2);
	return GetVehicleMatrix(0x57DE10)((DWORD*)(((char*)vehicle) + 0x10), v2);
}

//при 1.75 прикольно

//float arcade_coeff       = 1.5;
float correct_coeff_mass = 1.0; //2.15;
float correct_coeff_I    = 1.0; //1.15
int   time_value_ms      = 2;  //10

float c_coeff_mass[2]; //2.15;
float c_coeff_I[2];  //1.15
float power_coeff_sim = 0.31;
float power_coeff_arc = 0.20;
float trailer_coeff[2];
//float couple_angle_lim = 0.53407;

bool is_arcad_mode(DWORD *Car_V){
	//*(_DWORD *)(*(_DWORD *)(v2[154] + 21600) + 10088)
	bool sim_mode = *(int*)(((char*)Car_V) + 10088);
	//cout << "arcad=" << arcad << endl;

	return !sim_mode;
}

bool is_player(DWORD *Car_V){
	DWORD* playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	DWORD* playerCar_V = (DWORD *)(playerVehicle[5400]);

	return Car_V == playerCar_V;
}

int getSemitrailerType(){
	DWORD* playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	DWORD* trailerVehicle = (DWORD *)playerVehicle[5470];

	if (!trailerVehicle)
		return 0;

	DWORD trailerTechID = trailerVehicle[2605];
	//cout << (*(DWORD*)((0x697888 + (2416 * trailerTechID) + 0x948))) << endl;

	return (*(DWORD*)((0x697888 + (2416 * trailerTechID) + 0x948))); //1 - обычный,  2 - платформа, 3 - цистерна
}


bool is_couple_detached;
void check_couple_state(){
	DWORD* playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);
	DWORD pl_field_5473 = *(DWORD*)(((char*)playerVehicle) + 0x5584);

	is_couple_detached = (pl_field_5473 != 0);
}

void correct_coeffs(DWORD *Car_V){
	int par_idx = 0;
	if (is_arcad_mode(Car_V)){
		par_idx = 1;
	}

	float speed_ms = *(float*)((char*)Car_V + 0x332C);

	//сюда же можно добавить проверку углов поворота тягача/прицепа
	if (!(GetTickCount() % time_value_ms) && speed_ms > 5.5 && !is_couple_detached){ //5.5 = 19.8 ; скорость < 7 м/с (25.2 км/ч), чтобы не катился вниз на горках
		correct_coeff_mass = c_coeff_mass[par_idx];
		correct_coeff_I = c_coeff_I[par_idx];

		//если обрабатывается полуприцеп
		if (!is_player(Car_V)){
			correct_coeff_mass = trailer_coeff[par_idx] * c_coeff_mass[par_idx];
			correct_coeff_I    = trailer_coeff[par_idx] * c_coeff_I[par_idx];
		}

		//cout << "coeffs new\n";
	} else {
		correct_coeff_mass = 1.0;
		correct_coeff_I = 1.0;
		//cout << "coeffs std\n";
	}

	//автоматическое отключение зеркала заднего вида
	if (*(DWORD*)0x6F6A64){
		*(DWORD*)0x6F6A64 = 0;
	}
}

int __fastcall sub_4EBC00(DWORD *_this, DWORD EDX, DWORD *a2, DWORD *a3){
	signed int v3; // eax
	int result; // eax
	DWORD *v5; // edx
	DWORD *v6; // eax

	check_couple_state();

	//*((_DWORD *)v1 + 5473)
	// v263 = *(_DWORD *)(*((_DWORD *)v1 + 5400) + 13124) == 0;
	// v273 = *(_DWORD *)(*(_DWORD *)(v3 + 21600) + 13124) == 0;

	v3 = _this[49];
	if ( v3 >= 5 )
		return 0;
	v5 = &_this[3 * v3 + 95];
	*v5 = *a2;
	v5[1] = a2[1];
	v5[2] = a2[2];
	v6 = &_this[3 * _this[49] + 110];
	*v6 = *a3;
	v6[1] = a3[1];
	v6[2] = a3[2];
	result = _this[49];
	_this[49] = result + 1;
	return result;
}

//----- (004F8150) --------------------------------------------------------
CVector *__fastcall Car_V_get_unk1_Field_158(DWORD *Car_V, DWORD EDX, CVector *a2){
  a2 = (CVector*)(((char*)Car_V) + 0x237C);
  //float *mass = (float*)(((char*)Car_V) + 0x2640);

  //a2->x = a2->x / *mass;
  //a2->y = a2->y / *mass;
  //a2->z = a2->z / *mass;

  correct_coeffs(Car_V);

  a2->x = a2->x * correct_coeff_mass;
  a2->y = a2->y * correct_coeff_mass;
  a2->z = a2->z * correct_coeff_mass;


  return a2;
}

//----- (004F8180) --------------------------------------------------------
CVector *__fastcall Car_V_get_unk1_Field_194(DWORD *Car_V, DWORD EDX, CVector *a2){
  a2 = (CVector*)(((char*)Car_V) + 0x23B8);

  //float *techScaleVectorI = (float*)(((char*)Car_V) + 0x1F48);

  correct_coeffs(Car_V);

  a2->x = a2->x * correct_coeff_I; //(*techScaleVectorI * 0.8);
  a2->y = a2->y * correct_coeff_I; //(*techScaleVectorI * 0.8);
  a2->z = a2->z * correct_coeff_I; //(*techScaleVectorI * 0.8);

  //cout << "is_player=" << is_player(Car_V) << " arcad=" << is_arcad_mode(Car_V) << endl;

  return a2;
}

float GetPrivateProfileFloat(string selection, string varname, string default_val, string filename){
	float to_return;
	char* returnedString = new char[256];
	GetPrivateProfileStringA(selection.c_str(), varname.c_str(), default_val.c_str(), returnedString, 256, filename.c_str());
	to_return = atof(returnedString);
	return to_return;
}

void update_tractor_params(){
	DWORD* playerVehicle = (DWORD*)(*(DWORD*)0x6F6930);

	if (!playerVehicle)
		return;

	DWORD* playerCar_V = (DWORD *)(playerVehicle[5400]);
	int    playerTechID = playerVehicle[2605];

	DWORD* trailerVehicle = (DWORD *)playerVehicle[5470];


	float* maxrotmomentum_original = (float*)((0x697888 + (2416 * playerTechID) + 0xC0));
	float* maxrotmomentum_current  = (float*)(((char*)playerCar_V) + 0x3EBC + 0xC);

	if (!trailerVehicle){
		//cout << "no trailer\n";
		*maxrotmomentum_current = *maxrotmomentum_original;
	} else {
		//cout << "trailer\n";
		if (is_arcad_mode(playerCar_V)){
			*maxrotmomentum_current = *maxrotmomentum_original * power_coeff_arc; // / c_coeff_mass + c_coeff_I;
		} else {
			*maxrotmomentum_current = *maxrotmomentum_original * power_coeff_sim; // / c_coeff_mass + c_coeff_I;
		}
	}
}

void CALLBACK OnTimer(HWND hwnd, UINT msg, UINT_PTR idTimer, DWORD dwTime){
	if (*(DWORD *)0x6D2098){
		update_tractor_params();
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{

	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!GetPrivateProfileInt("mod", "enabled", 0, ".\\KoTR_PhysicsMod.ini"))
				return TRUE;

			SetTimer(0, 0, 50, OnTimer);

			bool display_console = GetPrivateProfileInt("mod", "display_console", 0, ".\\KoTR_PhysicsMod.ini");

			time_value_ms = GetPrivateProfileInt("tractor_physics", "correct_time_ms",    2,      ".\\KoTR_PhysicsMod.ini");
			c_coeff_mass[0]  = GetPrivateProfileFloat("tractor_physics", "correct_coeff_2271s", "2.15", ".\\KoTR_PhysicsMod.ini");
			c_coeff_mass[1]  = GetPrivateProfileFloat("tractor_physics", "correct_coeff_2271a", "2.15", ".\\KoTR_PhysicsMod.ini");
			c_coeff_I[0]     = GetPrivateProfileFloat("tractor_physics", "correct_coeff_2286s", "1.15", ".\\KoTR_PhysicsMod.ini");
			c_coeff_I[1]     = GetPrivateProfileFloat("tractor_physics", "correct_coeff_2286a", "1.15", ".\\KoTR_PhysicsMod.ini");
			power_coeff_sim   = GetPrivateProfileFloat("tractor_physics", "power_correct_simul", "0.30", ".\\KoTR_PhysicsMod.ini");
			power_coeff_arc   = GetPrivateProfileFloat("tractor_physics", "power_correct_arcad", "0.30", ".\\KoTR_PhysicsMod.ini");
			trailer_coeff[0] = GetPrivateProfileFloat("tractor_physics", "trailer_coeff_simul", "1.0", ".\\KoTR_PhysicsMod.ini");
			trailer_coeff[1] = GetPrivateProfileFloat("tractor_physics", "trailer_coeff_arcad", "1.0", ".\\KoTR_PhysicsMod.ini");
			//couple_angle_lim = GetPrivateProfileFloat("tractor_physics", "coupler_angle_limit", "0.53407", ".\\KoTR_PhysicsMod.ini");
			//arcade_coeff = GetPrivateProfileFloat("tractor_physics", "arcade_mode_coeff",  "1.0", ".\\KoTR_PhysicsMod.ini");

			if (display_console){
				DisplayConsole();
				cout << "Physics Mod (2025.01.11) started\nMod values:\n";
				//cout << "PhysicsMod:\n";
				cout << "  time_value_ms =" << time_value_ms << endl;
				cout << "  c_coeff_mass  =" << c_coeff_mass[0] << " | " << c_coeff_mass[1] << endl;
				cout << "  c_coeff_I     =" << c_coeff_I[0] << " | " << c_coeff_I[1]  << endl;
				cout << "  c_power_sim   =" << power_coeff_sim << endl;
				cout << "  c_power_arc   =" << power_coeff_arc << endl;
				cout << "  trailer_coeff =" << trailer_coeff[0] << " | " << trailer_coeff[1] << endl;
				//cout << "  coupler_angle =" << couple_angle_lim << endl;
				//cout << "  arcade_coeff =" << arcade_coeff << endl;
			}

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			DWORD addr_4F8150 = 0x4F8150;
			DetourAttach(&(LPVOID&)addr_4F8150, &Car_V_get_unk1_Field_158);
			DWORD addr_4F8180 = 0x4F8180;
			DetourAttach(&(LPVOID&)addr_4F8180, &Car_V_get_unk1_Field_194);

			DWORD addr_4EBC00 = 0x4EBC00;
			DetourAttach(&(LPVOID&)addr_4EBC00, &sub_4EBC00);

			DetourTransactionCommit();
			
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
