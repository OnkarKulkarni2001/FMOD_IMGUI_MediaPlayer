#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
using namespace std;

int main()
{
	FMODInitialization::FMODInitialization();
	
	FMOD_RESULT result;
	FMOD::System* fmodSystem = nullptr;
	const char* filename = "audio/jaguar.wav";

	FMOD::Sound* sound;
	fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);

	FMOD::Channel* channel;
	fmodSystem->playSound(sound, NULL, false, &channel);
	return 0;
}