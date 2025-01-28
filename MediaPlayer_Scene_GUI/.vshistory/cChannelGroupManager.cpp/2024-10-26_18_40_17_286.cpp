#include "cChannelGroupManager.h"
#include <string>
#include <Windows.h>

void cChannelGroupManager::LoadScenes()
{
    void findFoldersInDirectory(const std::string & directoryPath) {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind;

        std::string searchPath = directoryPath + "\\*"; // Add wildcard to search in directory

        // Start searching for files and folders in the directory
        hFind = FindFirstFile(searchPath.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Could not open directory " << directoryPath << std::endl;
            return;
        }

        do {
            // Check if it's a directory and ignore "." and ".." entries
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                (strcmp(findFileData.cFileName, ".") != 0) &&
                (strcmp(findFileData.cFileName, "..") != 0)) {
                std::cout << "Folder found: " << findFileData.cFileName << std::endl;
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
}

void cChannelGroupManager::CreateChannelGroup()
{
}

void cChannelGroupManager::Add3DSoundListener()
{
}

void cChannelGroupManager::ShowAvailableChannelGroups()
{
}

void cChannelGroupManager::PrintChannelGroupInfo()
{
}

void cChannelGroupManager::LoadAssets()
{
}

void cChannelGroupManager::UnloadAssets()
{
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
