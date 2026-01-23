#ifndef TECH_SYSTEM_FIX_H
#define TECH_SYSTEM_FIX_H

namespace TechSystemFix {
	double		 Upgrade_GetCurrentValue(float *upg);
	void		 Upgrade_SetCurrentValue(float *upg, float value);
	void __cdecl OnVehicleSetUpgrades(int *vehicle);
	void		 injectHooks();
}

#endif
