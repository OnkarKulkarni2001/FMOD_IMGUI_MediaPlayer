#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
using namespace std;

int main()
{
	FMOD_RESULT result;
	FMODInitialization::FMODInitialization();	
	FMOD::System* fmodSystem = nullptr;
	FMOD::Channel* channel;
	FMOD::Sound* sound;

	const char* filename = "audio/wave.wav";
	fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK) {
		cout << "Sound creation unsuccessful :(" << FMOD_ErrorString(result) << endl;
	}

	fmodSystem->playSound(sound, NULL, false, &channel);
	if (result != FMOD_OK) {
		cout << "Sound is not playing!!!" << FMOD_ErrorString(result) << endl;
	}
	return 0;
}