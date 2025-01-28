#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>

using namespace std;

int main()
{
	cAudioManager audioManager;
	cMediaPlayer mediaPlayer;
	int key = 0;
	mediaPlayer.RunMediaPlayer();
    // Key detection loop to stop media player
    cout << "Press 'Q' to stop the Media Player at any time." << endl;

    // Constantly check for a key press after starting the media player
    while (true) {
        if (_kbhit()) { // Check if a key was pressed
            char key = _getch(); // Get the pressed key
            if (key == 'Q' || key == 'q') { // If 'Q' or 'q' is pressed
                mediaPlayer.StopMediaPlayer(); // Call the stop function
                break; // Exit the loop and end the program
            }
        }
    }
	return 0;
}