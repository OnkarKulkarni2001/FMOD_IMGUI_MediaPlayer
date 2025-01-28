#pragma once
#include "AudioUtils.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
using namespace std;

class FMODInitialization
{
	FMOD::System* fmodSystem = nullptr;

	FMOD_RESULT result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) 
	{
		cout << "FMOD initialization error" << FMOD_ErrorString(result) << endl;
	}

};

