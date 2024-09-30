#include "cAudioManager.h"
#include "cMediaPlayer.h"
#include "FMODInitialization.h"
#include <fstream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <thread>

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

        unsigned int soundLength = 0;
        unsigned int currentPosition = 0;

        // Get the length of the sound and check for errors
        result = sounds[userInput]->getLength(&soundLength, FMOD_TIMEUNIT_MS);
        if (result != FMOD_OK || soundLength == 0) {
            std::cerr << "Error getting sound length or invalid length!" << std::endl;
            return;
        }

        // Loop to update the progress bar until the sound finishes
        while (true) {
            // Get the current position of the playing sound and check for errors
            result = channel->getPosition(&currentPosition, FMOD_TIMEUNIT_MS);
            if (result != FMOD_OK) {
                std::cerr << "Error getting current position!" << std::endl;
                break;
            }

            // Calculate the progress as a float between 0.0 and 1.0
            progress = static_cast<float>(currentPosition) / static_cast<float>(soundLength);

            // Display the progress bar
            DisplayProgressBar(progress);

            // Break the loop when the sound finishes
            if (progress >= 1.0f)
                break;

            // Sleep for 100ms before updating the progress bar again
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        do {
            fmodSystem->update();
        } while (bIsPlaying);
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cAudioManager::DisplayProgressBar(float progress, int barWidth) {
    int pos = static_cast<int>(barWidth * progress); // Calculate the current position in the bar
    std::cout << "(";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << "=";  // Filled part of the bar
        else
            std::cout << " ";  // Empty part of the bar
    }
    std::cout << ") " << int(progress * 100.0f) << " %\r";  // Show progress percentage
    std::cout.flush();  // Ensure the bar is displayed and updated properly
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
            cout << "Original pitch value = " << pitchValue << endl;
            while (true) {
                if (_kbhit()) {
                    int key = _getch();

                    if (key == 'q') {
                        pitchValue += 0.1;
                        result = channel->setPitch(pitchValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }
                        
                        cout << "New Pitch: " << pitchValue  << endl;
                    }
                    if (key == 'e') {
                        pitchValue -= 0.1;
                        if (pitchValue <= 0.1) {
                            pitchValue = 0.1;
                            result = channel->setPitch(pitchValue);

                            if (result != FMOD_OK) {
                                FMODCheckError(result);
                                return;
                            }

                            cout << "New Pitch: " << pitchValue << endl;
                            cout << "Pitch set to minimum value of 0.1! Exiting pitch controls..." << endl;
                            return;
                        }
                        result = channel->setPitch(pitchValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }

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
            cout << "Press up arrow key to increase volume by 0.1 and down arrow key to decrease volume by 0.1. and Esc to exit volume controls." << endl;
            volumeValue = channel->getVolume(&volumeValue) + 1 ;
            cout << "Original volume value = " << volumeValue << endl;
            while (true) {
                if (_kbhit()) {
                    int key = _getch();

                    if (key == 72) {
                        volumeValue += 0.1;
                        if (volumeValue >= 10.0) {
                            volumeValue = 10.0;
                            cout << "New Volume: " << volumeValue << endl;
                            result = channel->setVolume(volumeValue);

                            if (result != FMOD_OK) {
                                FMODCheckError(result);
                                return;
                            }

                            cout << "Volume set to maximum value of 10! Exiting volume controls..." << endl;
                            return;
                        }
                        result = channel->setVolume(volumeValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }

                        cout << "New Volume: " << volumeValue << endl;
                    }
                    if (key == 80) {
                        volumeValue -= 0.1;
                        if (volumeValue <= 0.1) {
                            volumeValue = 0;
                            result = channel->setVolume(volumeValue);

                            if (result != FMOD_OK) {
                                FMODCheckError(result);
                                return;
                            }

                            cout << "New Volume: " << volumeValue << endl;
                            cout << "Volume set to minimum value of 0! Exiting volume controls..." << endl;
                            return;
                        }
                        result = channel->setVolume(volumeValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }

                        cout << "New Volume: " << volumeValue << endl;
                    }
                    if (key == 27) {
                        cout << "Volume set successfull! Exiting volume controls..." << endl;
                        return;
                    }
                }
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
            cout << "Press left arrow key to pan sound to left by 0.1 and right arrow key to pan sound to right by 0.1. and Esc to exit pan controls." << endl;
            cout << "Original pan value = " << panValue << endl;
            while (true) {
                if (_kbhit()) {
                    int key = _getch();

                    if (key == 77) {
                        panValue += 0.1;
                        if (panValue >= 1.0) {
                            panValue = 1.0;
                            cout << "New Pan: " << panValue << endl;
                            result = channel->setPan(panValue);

                            if (result != FMOD_OK) {
                                FMODCheckError(result);
                                return;
                            }

                            cout << "Pan set to maximum value of 1! Exiting pan controls..." << endl;
                            return;
                        }
                        result = channel->setPan(panValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }

                        cout << "New Pan: " << panValue << endl;
                    }
                    if (key == 75) {
                        panValue -= 0.1;
                        if (panValue <= -1.0) {
                            panValue = -1.0;
                            result = channel->setPan(panValue);

                            if (result != FMOD_OK) {
                                FMODCheckError(result);
                                return;
                            }

                            cout << "New Pan: " << panValue << endl;
                            cout << "Pan set to minimum value of -1.0! Exiting pan controls..." << endl;
                            return;
                        }
                        result = channel->setPan(panValue);

                        if (result != FMOD_OK) {
                            FMODCheckError(result);
                            return;
                        }

                        cout << "New Pan: " << panValue << endl;
                    }
                    if (key == 27) {
                        cout << "Pan set successfull! Exiting pan controls..." << endl;
                        return;
                    }
                }
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


