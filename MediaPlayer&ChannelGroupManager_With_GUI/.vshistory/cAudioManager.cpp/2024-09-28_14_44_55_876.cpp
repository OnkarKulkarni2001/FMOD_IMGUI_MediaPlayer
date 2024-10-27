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
std::string folderPath;  // Store folder path from user input

void cAudioManager::loadAssets() {
    if (!m_Initialized) {
        ImGui::Text("FMOD not initialized");
        return;
    }
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("Load Songs Window");

    ImGui::Text("Enter the folder path containing the songs:");

    static char folderPathInput[256] = "";  // Buffer to store input folder path
    ImGui::InputText("Folder Path", folderPathInput, sizeof(folderPathInput));  // Input for folder path

    // Button to trigger loading of assets
    if (ImGui::Button("Load Songs")) {
        folderPath = std::string(folderPathInput);  // Convert input to std::string

        std::wstring wideFolderPath(folderPath.begin(), folderPath.end());
        std::wstring searchPath = wideFolderPath + L"\\*";  // Use wildcard to search all files

        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            ImGui::Text("Could not open directory: %s", folderPath.c_str());
            return;
        }

        FMOD_RESULT result;

        do {
            // Check if the found entry is a file
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring filePath = wideFolderPath + L"\\" + findFileData.cFileName;  // Construct full file path

                FMOD::Sound* newSound;
                result = fmodSystem->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &newSound);

                if (result != FMOD_OK) {
                    ImGui::Text("Error: Sound creation unsuccessful for file %s", std::string(filePath.begin(), filePath.end()).c_str());
                }
                else {
                    ImGui::Text("Sound %s loaded successfully!", std::string(filePath.begin(), filePath.end()).c_str());
                    sounds.push_back(newSound);  // Store the new sound
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);  // Close the find handle
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
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

void cAudioManager::setPitch(float pitchValue) {
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
            channel->setPitch(pitchValue);

            /*cout << "Press q to increase pitch by 0.1 and e to decrease pitch by 0.1. and Esc to exit pitch controls." << endl;
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
            }*/
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

void cAudioManager::setVolume(float volumeValue) {
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
            channel->setVolume(volumeValue);
            /*cout << "Press up arrow key to increase volume by 0.1 and down arrow key to decrease volume by 0.1. and Esc to exit volume controls." << endl;
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
            }*/
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

void cAudioManager::setPan(float panValue) {
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
            channel->setPan(panValue);

            /*cout << "Press left arrow key to pan sound to left by 0.1 and right arrow key to pan sound to right by 0.1. and Esc to exit pan controls." << endl;
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
            }*/
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