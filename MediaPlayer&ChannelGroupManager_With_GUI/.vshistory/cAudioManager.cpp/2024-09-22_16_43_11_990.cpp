#include "cAudioManager.h"
#include "FMODInitialization.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <vector>

namespace fs = boost::filesystem;

FMODInitialization initializationObject;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;
std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers

void cAudioManager::loadAssets() {

    std::string folderPath;
    std::cout << "Enter the folder path containing the songs: ";
    std::cin >> folderPath;

    fs::path dir(folderPath);
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_regular_file(entry.status())) {
                const auto& filePath = entry.path();
                const char* filename = filePath.string().c_str();

                FMOD::Sound* newSound;
                result = fmodSystem->createSound(filename, FMOD_DEFAULT, 0, &newSound);

                if (result != FMOD_OK) {
                    std::cout << "Sound creation unsuccessful for file " << filePath << ": "
                        << FMOD_ErrorString(result) << std::endl;
                }
                else {
                    std::cout << "Sound " << filePath << " loaded successfully!" << std::endl;
                    sounds.push_back(newSound); // Store the new sound in the vector
                }
            }
        }
    }
    else {
        std::cout << "Invalid directory." << std::endl;
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