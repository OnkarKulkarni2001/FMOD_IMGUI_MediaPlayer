#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>
#include <iostream>
#include <thread>
using namespace std;
std::thread audioThread;

cAudioManager audioManager;
bool bIsPlaying = false;

void cMediaPlayer::StartMediaPlayer() {
    cout << "Welcome to the Media Player developed by Onkar Kulkarni!" << endl;
    cout << "You need to load songs first to listen them. I'll do that for you but you just need to specify the folder name." << endl;
    audioManager.loadAssets();
    cout << "Enjoy listening!" << endl;
}

void cMediaPlayer::RunMediaPlayer() {
    cout << "Commands:\n0) P: Play Song\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) U: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n7) Esc: Quit Media Player\n";

    bool bIsRunning = true;
    bool bIsPaused = false;   // Variable to check if a song is paused

    do {
        if (_kbhit()) {
            char key = _getch();

            if (key == 'P' || key == 'p') {
                int indexOfSong;
                cout << "Enter number of song you want to play: " << endl;
                cin >> indexOfSong;
                PlayAudio(indexOfSong);  // Play audio in parallel
                bIsPlaying = true;  // A song is playing
                bIsPaused = false;  // Not paused
            }

            if (bIsPlaying && !bIsPaused) {  // Only allow these commands when a song is playing and not paused
                if (key == 'V' || key == 'v') {
                    AdjustVolume();
                }
                if (key == 'I' || key == 'i') {
                    AdjustPitch();
                }
                if (key == 'A' || key == 'a') {
                    AdjustPan();
                }
                if (key == 'U' || key == 'u') {
                    PauseAudio();
                    bIsPaused = true;  // The song is paused
                }
                if (key == 'S' || key == 's') {
                    StopAudio();
                    bIsPlaying = false;  // The song is stopped, nothing is playing now
                    bIsPaused = false;   // Reset paused state
                }
            }

            if (bIsPaused) {  // Allow resume only if the song was paused
                if (key == 'R' || key == 'r') {
                    audioManager.resume();
                    bIsPaused = false;  // Resuming means it's playing again
                }
            }

            if (key == 27) {  // Escape key to quit the media player
                StopMediaPlayer();
                bIsRunning = false;  // Exit the loop after stopping the media player
            }
        }
    } while (bIsRunning);
}

void cMediaPlayer::StopMediaPlayer() {
    string decision;
    cout << "You want to quit? Are you sure? YES = Y, NO = N " << endl;
    cin >> decision;
    if (decision == "Y" || decision == "y") {
        StopAudio();
        audioManager.unloadAssets();
    }
    if (decision == "N" || decision == "n") {
        cout << "Continue listening..." << endl;
        RunMediaPlayer();
    }
    else {
        cout << "Enter valid choice!" << endl;
        StopMediaPlayer();
    }
}

void cMediaPlayer::PlayAudio(int index) {
	audioManager.play(index);
}

void cMediaPlayer::PauseAudio() {
	audioManager.pause();
}

void cMediaPlayer::StopAudio() {
	audioManager.stop();

}

void cMediaPlayer::AdjustPitch() {
	audioManager.setPitch();
}

void cMediaPlayer::AdjustVolume() {
	audioManager.setVolume();
}

void cMediaPlayer::AdjustPan() {
	audioManager.setPan();
}