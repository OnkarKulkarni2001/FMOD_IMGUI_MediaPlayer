#include "cChannelGroupManager.h"
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
std::string folderPath;  // Storing folder path from user input

void cChannelGroupManager::CreateChannelGroup() {
    if (!m_Initialized) {
        return;
    }

    // Create an ImGui window or section
    ImGui::Begin("Channel Group Manager");
    char* channel_name[256] = "";
    // Create an input text box for the channel name
    ImGui::InputText("Channel Name", channel_name, IM_ARRAYSIZE(channel_name));

    // Create a button to trigger the channel group creation
    if (ImGui::Button("Create Channel Group")) {
        // Only create the channel group if a name is provided
        if (strlen(channel_name) > 0) {
            FMOD_RESULT result;
            result = fmodSystem->createChannelGroup(channel_name, &m_ChannelGroup);

            if (result != FMOD_OK) {
                // Display error message using ImGui
                snprintf(message, IM_ARRAYSIZE(message), "Error: %s", FMOD_ErrorString(result));
            }
            else {
                // Display success message using ImGui
                snprintf(message, IM_ARRAYSIZE(message), "Channel group '%s' has been created!", channel_name);
            }
        }
        else {
            // Display warning message if no channel name is entered
            snprintf(message, IM_ARRAYSIZE(message), "Please enter a valid channel name.");
        }
    }

    // Display the message (either success or error)
    if (strlen(message) > 0) {
        ImGui::Text("%s", message);
    }

    ImGui::End();
}

void cChannelGroupManager::SetChannelGroupDSP() {
    if (!m_Initialized)
        return;

    FMOD_RESULT result;

    FMOD::DSP* distortionDSP;

    result = fmodSystem->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &distortionDSP);

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    result = distortionDSP->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.0f);

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    m_ChannelGroup->addDSP(0, distortionDSP);

    std::cout << "Distortion DSP has been set!\n" << std::endl;
}

void cChannelGroupManager::PrintChannelGroupInfo() {
    if (!m_Initialized || !m_ChannelGroup) {
        return;
    }

    // Buffer to hold the channel group name
    char name[256];
    m_ChannelGroup->getName(name, sizeof(name));

    // Variables to hold volume and pitch
    float volume = 0.0f;
    m_ChannelGroup->getVolume(&volume);

    float pitch = 0.0f;
    m_ChannelGroup->getPitch(&pitch);

    // Begin an ImGui window/section
    ImGui::Begin("Channel Group Info");

    // Display the channel group name, volume, and pitch using ImGui
    ImGui::Text("Channel Group Name: %s", name);
    ImGui::Text("Volume: %.2f", volume);
    ImGui::Text("Pitch: %.2f", pitch);

    // Optionally add sliders or other controls to modify the values
    // ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);
    // ImGui::SliderFloat("Pitch", &pitch, 0.5f, 2.0f);

    ImGui::End();
}


FMOD::ChannelGroup* cChannelGroupManager::getChannelGroup()
{
    return m_ChannelGroup;
}

void cChannelGroupManager::loadAssets() {
    if (!m_Initialized) {
        ImGui::Text("FMOD not initialized");
        return;
    }
    ImGui::Text("Enter the folder path containing the songs:");

    static char folderPathInput[256] = "";  // Buffer for storing input folder path
    ImGui::InputText("Folder Path", folderPathInput, sizeof(folderPathInput));  // Taking Input for folder path

    ImGui::Text("Please wait for songs to load if your directory is bigger than usual...");
    // Button to trigger loading of assets
    if (ImGui::Button("Load Songs")) {

        std::string folderPath = std::string(folderPathInput);  // Converting input to std::string

        std::wstring wideFolderPath(folderPath.begin(), folderPath.end());
        std::wstring searchPath = wideFolderPath + L"\\*";  // Search all files

        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            ImGui::Text("Could not open directory: %s", folderPath.c_str());
            ImGui::End(); 
            return;
        }

        FMOD_RESULT result;

        do {
            // Check if the found entry is a file
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring filePath = wideFolderPath + L"\\" + findFileData.cFileName;  // Converting to full file path

                FMOD::Sound* newSound;
                result = fmodSystem->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &newSound);

                if (result != FMOD_OK) {
                    ImGui::Text("Error: Sound creation unsuccessful for file %s", std::string(filePath.begin(), filePath.end()).c_str());
                }
                else {
                    ImGui::Text("Sound %s loaded successfully!", std::string(filePath.begin(), filePath.end()).c_str());
                    sounds.push_back(newSound);  // Storing the new sound
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);  // Closing the find handle
    }
}

void cChannelGroupManager::unloadAssets() {
    
    bool bWindowShouldShow = true;
    if (!m_Initialized) {
        ImGui::Text("FMOD not initialized.");
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    if (sounds.empty()) {
        ImGui::Text("No sounds are loaded.");
        return;
    }


    static int choice = 0;
    ImGui::Text("Do you want to:");
    if (ImGui::RadioButton("Unload a specific song", choice == 1)) {
        choice = 1;
    }
    if (ImGui::RadioButton("Unload all songs", choice == 2)) {
        choice = 2;
    }

    if (choice == 1) {
        static int index = 0;
        ImGui::InputInt("Enter the song index", &index);

        // Ensuring the index is within bounds
        if (index >= 1 && index <= sounds.size()) {
            if (ImGui::Button("Unload Song")) {
                // Converting user input to zero-based index
                int zeroBasedIndex = index - 1;

                if (zeroBasedIndex >= 0 && zeroBasedIndex < sounds.size()) {
                    sounds[zeroBasedIndex]->release(); // Releasing the sound resource
                    sounds.erase(sounds.begin() + zeroBasedIndex); // Removing from the vector
                    ImGui::Text("Song at index %d unloaded successfully.", index);
                    bWindowShouldShow = false;
                }
            }
        }
        else {
            ImGui::Text("Invalid song index!");
        }
    }
    else if (choice == 2) {
        if (ImGui::Button("Unload All Songs")) {
            // Unloading all songs
            for (auto& sound : sounds) {
                sound->release(); // Releasing each sound
            }
            sounds.clear(); // Clearing the vector
            ImGui::Text("All songs unloaded successfully.");
            bWindowShouldShow = false;
        }
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
}

void cChannelGroupManager::play(int index) {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
    channel->isPlaying(&bIsPlaying);
    if (bIsPlaying) {
        stop();
        play(index);
    }
    else {
        result = channel->isPlaying(&bIsPlaying);
        int userInput = index - 1;
        result = fmodSystem->playSound(sounds[userInput], nullptr, false, &channel);    // Playing sound
        do {
            fmodSystem->update();
        } while (bIsPlaying);
    }
}

void cChannelGroupManager::pause() {
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
                channel->setPaused(true);   // Pausing sound
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

void cChannelGroupManager::resume() {
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
                channel->setPaused(false);      // Resuming sound
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

void cChannelGroupManager::stop() {
    if (!m_Initialized) {
        cout << "FMOD not initialized" << endl;
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }
    channel->isPlaying(&bIsPlaying);
    if (bIsPlaying) {
        channel->stop();        // Stopping sound
    }
}

void cChannelGroupManager::setPitch(float pitchValue) {
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
            channel->setPitch(pitchValue);      // Setting pitch
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

void cChannelGroupManager::setVolume(float volumeValue) {
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
            channel->setVolume(volumeValue);        // Setting Volume
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

void cChannelGroupManager::setPan(float panValue) {
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
            channel->setPan(panValue);      // Setting pan
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