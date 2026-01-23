#include "ConfigUtils.h"
#include <Windows.h>

float GetPrivateProfileFloat(char* selection, char* variableName, char* defaultValue, char* filename){
	char buf[256];
	GetPrivateProfileStringA(selection, variableName, defaultValue, buf, sizeof(buf), filename);
	return atof(buf);
}

double GetPrivateProfileDouble(char* selection, char* variableName, char* defaultValue, char* filename){
	char buf[256];
	GetPrivateProfileStringA(selection, variableName, defaultValue, buf, sizeof(buf), filename);
	return atof(buf);
}