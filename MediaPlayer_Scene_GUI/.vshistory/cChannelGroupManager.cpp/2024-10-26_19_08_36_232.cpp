#include "cChannelGroupManager.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "AudioUtils.hpp"
#include "fmod_errors.h"
#include "FMODInitialization.h"

FMODInitialization initializationObject;
bool m_Initialized;
FMOD_RESULT result;
FMOD::System* fmodSystem = initializationObject.Initialized(result, m_Initialized);


void cChannelGroupManager::CreateChannelGroup()
{
}

void cChannelGroupManager::Add3DSoundListener()
{
}

void cChannelGroupManager::ShowAvailableChannelGroups()
{
	FMOD_RESULT result;
	char name[256];

	for (int channelGroupIndex = 0; channelGroupIndex != pChannelGroups.size(); channelGroupIndex++) {
		result = pChannelGroups[channelGroupIndex]->getGroup(channelGroupIndex, &m_ChannelGroup);
		
		if (result != FMOD_OK) {
			FMODCheckError(result);
			return;
		}

		result = m_ChannelGroup->getName(name, sizeof(name));
		
		if (result != FMOD_OK) {
			FMODCheckError(result);
			return;
		}
		else {
			std::cout << result << std::endl;
		}
	}
}

void cChannelGroupManager::PrintChannelGroupInfo()
{
	char name[256];
	m_ChannelGroup->getName(name, sizeof(name));

	float volume = 0.0f;
	m_ChannelGroup->getVolume(&volume);

	float pitch = 0.0f;
	m_ChannelGroup->getPitch(&pitch);

	std::cout << name << " channel group has a volume of " << volume << std::endl;
	std::cout << name << " channel group has a pitch of " << pitch << std::endl;
}

void cChannelGroupManager::LoadAssets()
{
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
        LoadAssets();
        return;
    }

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    do {
        // Check if the found entry is a file
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::wstring filePath = wideFolderPath + L"\\" + findFileData.cFileName;
            FMOD::Sound* newSound;
            FMOD_RESULT result = fmodSystem->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &newSound);

            if (result != FMOD_OK) {
                std::cerr << "Sound creation unsuccessful for file " << std::string(filePath.begin(), filePath.end()) << ": "
                    << FMOD_ErrorString(result) << std::endl;
            }
            else {
                std::cout << "Sound " << std::string(filePath.begin(), filePath.end()) << " loaded successfully!" << std::endl;
                pSounds.push_back(newSound); // Storing the new sound in the vector
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    if (result != FMOD_OK) {
        FMODCheckError(result);
        return;
    }

    FindClose(hFind); // Closing the find handle
}

void cChannelGroupManager::UnloadAssets()
{
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


        index -= 1;     // Converting user input to zero-based index

        if (index >= 0 && index < sounds.size()) {
            sounds[index]->release(); // Releasing the sound resource
            sounds.erase(sounds.begin() + index); // Removing from the vector
            std::cout << "Song at index " << (index + 1) << " unloaded successfully." << std::endl;
        }
        else {
            std::cerr << "Invalid song index!" << std::endl;
        }
    }
    else if (choice == 2) {
        // Unload all songs
        for (auto& sound : sounds) {
            sound->release(); // Releasing each sound
        }
        sounds.clear(); // Clearing the vector
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

void cChannelGroupManager::ApplyDSP()
{
}

void cChannelGroupManager::ApplyDSPToSound()
{
}

void cChannelGroupManager::PlayAudio()
{
}

void cChannelGroupManager::StopAudio()
{
}

void cChannelGroupManager::AdjustVolume()
{
}

void cChannelGroupManager::PlayIndividualAudio()
{
}

void cChannelGroupManager::StopIndividualAudio()
{
}

void cChannelGroupManager::AdjustIndividualAudioVolume()
{
}
