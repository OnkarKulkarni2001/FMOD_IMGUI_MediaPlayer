#include "cAudioManager.h"
#include "FMODInitialization.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

FMODInitialization initializationObject;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;
std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers

void cAudioManager::loadAssets() {

    string folderPath;
    cout << "Enter the folder path containing the songs: ";
    cin >> folderPath;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            const auto& filePath = entry.path();
            const char* filename = filePath.string().c_str();

            FMOD::Sound* newSound;
            result = fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &newSound);

            if (result != FMOD_OK) {
                cout << "Sound creation unsuccessful for file " << filePath << ": "
                    << FMOD_ErrorString(result) << endl;
            }
            else {
                cout << "Sound " << filePath << " loaded successfully!" << endl;
                sounds.push_back(newSound); // Store the new sound in the vector
            }
        }
    }
}

void cAudioManager::unloadAssets() {

}

void cAudioManager::play() {
	result = fmodSystem->playSound(sound, nullptr, false, &channel);
	bool bIsPlaying = false;

	do {
		channel->isPlaying(&bIsPlaying);
		fmodSystem->update();
	} while (bIsPlaying);
}

void cAudioManager::pause() {

}

void cAudioManager::stop() {
	sound->release();
}

void cAudioManager::setPitch() {

}

void cAudioManager::setVolume() {

}

void cAudioManager::setPan() {

}