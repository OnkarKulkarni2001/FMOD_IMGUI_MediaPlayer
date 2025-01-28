#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
using namespace std;

int main()
{
	//FMODInitialization::FMODInitialization();	
	FMOD::System* fmodSystem = nullptr;
	FMOD::Channel* channel;
	FMOD::Sound* sound;
	FMOD_RESULT result;
	
	result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		cout << "System creation error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System created successfully!" << endl;
	}

	result = fmodSystem->init(512, FMOD_DEFAULT, 0);
	if (result != FMOD_OK) {
		cout << "FMOD initialization error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System initialization successfull!" << endl;
	}

	const char* filename = "D:\\Media Fundamentals\\MediaPlayer\\audio\\wave.mp3";
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