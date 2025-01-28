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
	FMOD::Channel* channel;
	FMOD::Sound* sound;

	const char* filename = "audio/wave.wav";
	fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);

	fmodSystem->playSound(sound, NULL, false, &channel);
	return 0;
}