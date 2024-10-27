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
                std::cout << n << "Sound " << std::string(filePath.begin(), filePath.end()) << " loaded successfully!" << std::endl;
                sounds.push_back(newSound); // Store the new sound in the vector
            }
        }
        n++;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind); // Close the find handle
}

void cAudioManager::unloadAssets() {
    int i = 1;
    cout << "Want to: 1) Unload Single Song\n2) Unload All Songs" << endl;
    cin >> i;
    

    if (i == 1) {
        int k = 1;
        cout << "Enter the number of song you want to unload: " << endl;
        cin >> k;
        sounds[k]->release();
        sounds.erase(sounds.begin() + k);
    }
    if (i == 2) {
        cout << "Unloading all songs..." << endl;
        for (int index = 0; index != sizeof(sounds); index++) {
            sounds[index]->release();
            sounds.erase(sounds.begin() + index);
            cout << "Unloaded " << sounds[index] << " successfully!" << endl;
        }
        cout << "Unloaded all songs from the system!" << endl;
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