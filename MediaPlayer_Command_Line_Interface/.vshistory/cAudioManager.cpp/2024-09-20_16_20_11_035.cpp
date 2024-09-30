#include "cAudioManager.h"
#include "FMODInitialization.h"
#include <filesystem>

FMODInitialization initializationObject;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;

void cAudioManager::loadAssets() {
	const char* filePath = "audio";
	
	const char* filename = filePath;
	bool bIsLastSong = false;
	while (bIsLastSong) {

	}
	// below code in for or while loop
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