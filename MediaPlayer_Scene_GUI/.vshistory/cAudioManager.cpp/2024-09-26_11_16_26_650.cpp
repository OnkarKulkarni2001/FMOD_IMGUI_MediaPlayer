#include "cAudioManager.h"
#include "cMediaPlayer.h"
#include "FMODInitialization.h"
#include <fstream>
#include <vector>
#include <Windows.h>
#include <conio.h>

FMODInitialization initializationObject;
bool m_Initialized;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result, m_Initialized);
FMOD::Sound* sound;

void cAudioManager::loadAssets() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    std::string folderPath;
    std::cout << "Enter the folder path containing the songs: ";
    std::cin >> folderPath;
    cout << "\n----------------------------------------------loading Songs!--------------------------------------------" << endl;

    // Convert std::string to std::wstring
    std::wstring wideFolderPath(folderPath.begin(), folderPath.end());
    std::wstring searchPath = wideFolderPath + L"\\*"; // Use wide string for search path

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Could not open directory: " << folderPath << std::endl;
        cout << "Enter correct folderpath: " << endl;
        loadAssets();
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

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
                std::cout << "Sound " << std::string(filePath.begin(), filePath.end()) << " loaded successfully!" << std::endl;
                sounds.push_back(newSound); // Store the new sound in the vector
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    FindClose(hFind); // Close the find handle
}

void cAudioManager::unloadAssets() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

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
            sounds[index]->release(); // Release the sound resource
            sounds.erase(sounds.begin() + index); // Remove from the vector
            std::cout << "Song at index " << (index + 1) << " unloaded successfully." << std::endl;
        }
        else {
            std::cerr << "Invalid song index!" << std::endl;
        }
    }
    else if (choice == 2) {
        // Unload all songs
        for (auto& sound : sounds) {
            sound->release(); // Release each sound
        }
        sounds.clear(); // Clear the vector
        std::cout << "All songs unloaded successfully." << std::endl;
    }
    else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::play(int index) {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (bIsPlaying) {
        pause();
        cout << "Current song will stop if you want to play another song. Are you sure you want to stop this song? Y/N" << endl;
        char decision = 'Y';
        cin >> decision;
        if (decision == 'Y' || decision == 'y') {
            stop();
            bIsPlaying = false;
            play(index);
            cout << "Enjoy listening..." << endl;
        }
        else if (decision == 'N' || decision == 'n') {
            cout << "Continue listening..." << endl;
            resume();
        }
        else {
            cout << "Not a valid choice! The song will resume!" << endl;
            resume();
        }
    }

    else {
        result = channel->isPlaying(&bIsPlaying);
        int userInput = index - 1;
        result = fmodSystem->playSound(sounds[userInput], nullptr, false, &channel);
        do {
            fmodSystem->update();
        } while (bIsPlaying);
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::pause() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            channel->getPaused(&bIsPaused);
            if (!bIsPaused) {
                channel->setPaused(true);
                cout << "Sound paused!" << endl;
            }
            else {
                cout << "Sound is already paused!" << endl;
            }
        }
        else {
            cout << "No sound is playing to pause." << endl;
        }
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::resume() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            channel->getPaused(&bIsPaused);
            if (bIsPaused) {
                channel->setPaused(false);
                cout << "Sound resumed!" << endl;
            }
            else {
                cout << "Sound is already playing" << endl;
            }
        }
        else {
            cout << "No sound is paused to play." << endl;
        }
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::stop() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            result = channel->stop();
            if (result == FMOD_OK) {
                cout << "Sound stopped successfully!" << endl;
            }
            else {
                cerr << "Error occured while stopping sound: " << FMOD_ErrorString(result) << endl;
            }
        }
        else {
            cout << "No sound is currently playing to stop." << endl;
        }
    }
    else {
        cout << "No active channel found to stop sound." << endl;
    }
    
    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::setPitch() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }


    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            cout << "Press q to increase pitch by 0.1 and e to decrease pitch by 0.1. and Esc to exit pitch controls." << endl;
            pitchValue = channel->getPitch(&pitchValue);

            while (true) {
                if (_kbhit()) {
                    int key = _getch();

                    if (key == 'q') {
                        pitchValue += 0.1;
                        /*if (pitchValue > 1.0) {
                            pitchValue = 1.0;
                        }*/
                        result = channel->setPitch(pitchValue);
                        cout << "New Pitch: " << pitchValue  << endl;
                    }
                    if (key == 'e') {
                        pitchValue -= 0.1;
                        if (pitchValue < 0.0) {
                            pitchValue = 0.0000001;
                        }
                        result = channel->setPitch(pitchValue);
                        cout << "New Pitch: " << pitchValue << endl;
                    }
                    if (key == 27) {
                        cout << "Pitch set successfull! Exiting pitch controls..." << endl;
                        return;
                    }
                }
            }
        }
        else {
            cout << "No sound is currently playing to set pitch." << endl;
        }
    }
    else {
        cout << "No active channel found to set sound pitch." << endl;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::setVolume() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            cout << "Enter value between 0 and 1 to adjust volume." << endl;
            cin >> volumeValue;
            result = channel->setVolume(volumeValue);
            if (result == FMOD_OK) {
                cout << "Volume set successfull." << endl;
            }
            else {
                cerr << "Error occured while setting volume: " << FMOD_ErrorString(result) << endl;
            }
        }
        else {
            cout << "No sound is currently playing to set volume." << endl;
        }
    }
    else {
        cout << "No active channel found to set sound volume." << endl;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::setPan() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (channel) {
        channel->isPlaying(&bIsPlaying);
        if (bIsPlaying) {
            cout << "Enter value between 0 and 1 to adjust pan." << endl;
            cin >> panValue;
            result = channel->setPan(panValue);
            if (result == FMOD_OK) {
                cout << "Pan set successfull." << endl;
            }
            else {
                cerr << "Error occured while setting pan: " << FMOD_ErrorString(result) << endl;
            }
        }
        else {
            cout << "No sound is currently playing to set pan." << endl;
        }
    }
    else {
        cout << "No active channel found to set sound pan." << endl;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}