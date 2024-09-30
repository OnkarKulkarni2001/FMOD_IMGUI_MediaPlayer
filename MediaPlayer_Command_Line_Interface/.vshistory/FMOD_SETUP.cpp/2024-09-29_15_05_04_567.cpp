#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>
#include <thread>

using namespace std;

int main()
{
	cMediaPlayer mediaPlayer;
    cAudioManager audioManager;
	mediaPlayer.StartMediaPlayer();
	mediaPlayer.RunMediaPlayer();
    int indexOfSong = 1;
    bool bIsRunning = true;
    unsigned int soundLength = 0;
    unsigned int currentPosition = 0;

    // Get the length of the sound in milliseconds
    audioManager.sounds[indexOfSong]->getLength(&soundLength, FMOD_TIMEUNIT_MS);

    // Continuously update the progress bar until the sound is finished
    while (bIsRunning) {
        // Get the current position of the playing sound
        audioManager.channel->getPosition(&currentPosition, FMOD_TIMEUNIT_MS);

        // Calculate the progress as a float between 0.0 and 1.0
        float progress = float(currentPosition) / float(soundLength);

        // Display the progress bar
        mediaPlayer.displayProgressBar(progress, 100);

        // Break the loop when the sound reaches the end
        if (progress >= 1.0f)
            break;

        // Sleep for 100ms before updating the progress bar again
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
	return 0;
}