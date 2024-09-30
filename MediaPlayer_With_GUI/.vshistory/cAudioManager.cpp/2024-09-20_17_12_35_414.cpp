#include "cAudioManager.h"
#include "FMODInitialization.h"
#include <fstream>

FMODInitialization initializationObject;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;

void cAudioManager::loadAssets() {

	string filePath;
	cout << "Enter filename with path: " << endl;
	cin >> filePath;
	const char* filename = filePath.c_str();

	result = fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK) {
		cout << "Sound creation unsuccessful :(" << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "Sound created successfully!" << endl;
	}
}

void cAudioManager::unloadAssets() {

}

void cAudioManager::play() {

}

void cAudioManager::pause() {

}

void cAudioManager::stop() {

}

void cAudioManager::setPitch() {

}

void cAudioManager::setVolume() {

}

void cAudioManager::setPan() {

}