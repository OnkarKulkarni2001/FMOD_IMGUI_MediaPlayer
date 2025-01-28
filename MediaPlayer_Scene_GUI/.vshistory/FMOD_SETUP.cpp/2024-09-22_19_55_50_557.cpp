#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cAudioManager.h"
using namespace std;

int main()
{
	FMODInitialization initializationObject;

	FMOD_RESULT result;
	FMOD::System* fmodSystem = initializationObject.Initialized(result);
	FMOD::Channel* channel;
	FMOD::Sound* sound;

	bool bIsPlaying = false;
	
	/*result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		cout << "System creation error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System created successfully!" << endl;
	}

	result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		cout << "FMOD initialization error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System initialization successfull!" << endl;
	}*/

	/*string filePath;
	cout << "Enter filename with path: " << endl;
	cin >> filePath;

	const char* filename = filePath.c_str();

	result = fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK) {
		cout << "Sound creation unsuccessful :(" << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "Sound created successfully!" << endl;
	}*/
	cAudioManager audioManager;
	audioManager.loadAssets();
	audioManager.unloadAssets();



	fmodSystem->release();
	return 0;
}