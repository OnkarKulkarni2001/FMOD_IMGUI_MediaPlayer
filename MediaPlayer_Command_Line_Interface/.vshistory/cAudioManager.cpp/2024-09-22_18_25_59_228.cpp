#include "cAudioManager.h"
#include "FMODInitialization.h"
#include <fstream>
#include <vector>
#include <Windows.h>

FMODInitialization initializationObject;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;
std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers
std::vector<std::string> soundFileNames;

void cAudioManager::loadAssets() {

    std::string folderPath;
    std::cout << "Enter the folder path containing the songs: ";
    std::cin >> folderPath;

    // Convert std::string to std::wstring
    std::wstring wideFolderPath(folderPath.begin(), folderPath.end());
    std::wstring searchPath = wideFolderPath + L"\\*"; // Use wide string for search path

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Could not open directory: " << folderPath << std::endl;
        return;
    }

    int n = 1;
    do {
        // Check if the found entry is a file
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::wstring filePath = wideFolderPath + L"\\" + findFileData.cFileName; // Use wide string
            FMOD::Sound* newSound;
            FMOD_RESULT result = fmodSystem->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &newSound);

            if (result != FMOD_OK) {
                std::cerr << "Sound creation unsuccessful for file " << std::string(filePath.begin(), filePath.end()) << ": "
                    << FMOD_ErrorString(result) << std::endl;
            }
            else {
                std::cout << n << ") " << std::string(filePath.begin(), filePath.end()) << " loaded successfully!" << std::endl;
                sounds.push_back(newSound); // Store the new sound in the vector
            }
            n++;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind); // Close the find handle
}

void cAudioManager::unloadAssets() {
    if (sounds.empty()) {
        std::cout << "No sounds are loaded." << std::endl;
        return;
    }

    int choice;
    std::cout << "Do you want to: \n1) Unload a specific song \n2) Unload all songs\nEnter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        // Unload a specific song
        int index;
        std::cout << "Enter the index of the song to unload (1 to " << sounds.size() << "): ";
        std::cin >> index;

        // Convert user input to zero-based index
        index -= 1;

        if (index >= 0 && index < sounds.size()) {
            std::string fileName = soundFileNames[index];  // Get the corresponding file name
            sounds[index]->release();                      // Release the sound resource
            sounds.erase(sounds.begin() + index);          // Remove from the sounds vector
            soundFileNames.erase(soundFileNames.begin() + index);  // Remove from the file names vector

            std::cout << "Song '" << fileName << "' unloaded successfully." << std::endl;
        }
        else {
            std::cerr << "Invalid song index!" << std::endl;
        }
    }
    else if (choice == 2) {
        // Unload all songs
        for (size_t i = 0; i < sounds.size(); i++) {
            sounds[i]->release();  // Release each sound
            std::cout << "Song '" << soundFileNames[i] << "' unloaded successfully." << std::endl;
        }
        sounds.clear();           // Clear the sounds vector
        soundFileNames.clear();   // Clear the file names vector

        std::cout << "All songs unloaded successfully." << std::endl;
    }
    else {
        std::cerr << "Invalid choice!" << std::endl;
    }
}

void cAudioManager::play(int index) {
	result = fmodSystem->playSound(sounds[index], nullptr, false, &channel);
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