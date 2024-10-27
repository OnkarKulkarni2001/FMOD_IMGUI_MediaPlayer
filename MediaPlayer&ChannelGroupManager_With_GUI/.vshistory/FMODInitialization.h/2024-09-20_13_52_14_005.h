#pragma once
#include "AudioUtils.hpp"
#include "fmod.hpp"

class FMODInitialization
{
	FMOD_RESULT result;
	FMOD::System* fmodSystem = nullptr;

	result = FMOD::System_Create(&fmodSystem);

};

