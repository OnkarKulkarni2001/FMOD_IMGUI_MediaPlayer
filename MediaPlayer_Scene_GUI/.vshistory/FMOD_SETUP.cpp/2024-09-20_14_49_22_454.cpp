#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
using namespace std;

int main()
{
	FMODInitialization::FMODInitialization();	
	FMOD::System* fmodSystem = nullptr;
	FMOD::Channel* channel;
	FMOD::Sound* sound;
	FMOD_RESULT result;
	
	result = FMOD::System_Create(&fmodSystem);
	result = fmodSystem->init(512, FMOD_DEFAULT, 0);

	const char* filename = "audio/wave.wav";
	result = fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK) {
		cout << "Sound creation unsuccessful :(" << FMOD_ErrorString(result) << endl;
	}

	result = fmodSystem->playSound(sound, NULL, false, &channel);
	if (result != FMOD_OK) {
		cout << "Sound is not playing!!!" << FMOD_ErrorString(result) << endl;
	}
	return 0;
}