#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
using namespace std;

int main()
{
	FMODInitialization::FMODInitialization();
	FMOD::System* fmodSystem = nullptr;
	FMOD_RESULT result = FMOD::System_Create(&fmodSystem);
	result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	return 0;
}