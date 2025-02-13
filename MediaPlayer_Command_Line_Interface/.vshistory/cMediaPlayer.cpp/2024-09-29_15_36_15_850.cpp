﻿#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>
#include <iostream>
#include <thread>
using namespace std;

cAudioManager audioManager;

void cMediaPlayer::StartMediaPlayer() {
    cout << "Welcome to the Media Player developed by Onkar Kulkarni!" << endl;
    cout << "You need to load songs first to listen them. I'll do that for you but you just need to specify the folder name." << endl;
    audioManager.loadAssets();
    cout << "Enjoy listening!" << endl;
}

void cMediaPlayer::RunMediaPlayer() {
    cout << "Commands:\n0) P: Play Song\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) Spacebar: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n7) B: To Show Progress Bar\n8) Esc: Quit Media Player\n";
    bool bIsRunning = true;
    do {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'P' || key == 'p' ) {
                int indexOfSong = 1;
                ListSongs();
                cout << "Enter number of song you wanna play: " << endl;
                cin >> indexOfSong;
                if (indexOfSong >= 0 && indexOfSong < audioManager.sounds.size()) {
                    audioManager.channel->isPlaying(&audioManager.bIsPlaying);
                    PlayAudio(indexOfSong);
                }
                else {
                    cout << "Enter valid choice!" << endl;
                    cin >> indexOfSong;
                    audioManager.channel->isPlaying(&audioManager.bIsPlaying);
                    PlayAudio(indexOfSong);
                }
            }
            if (key == 'V' || key == 'v') {
                AdjustVolume();
            }
            if (key == 'I' || key == 'i') {
                AdjustPitch();
            }
            if (key == 'A' || key == 'a') {
                AdjustPan();
            }
            if (key == 32) {
                PauseAudio();
            }
            if (key == 'R' || key == 'r') {
                audioManager.resume();
            }
            if (key == 'S' || key == 's') {
                StopAudio();
            }
            if (key == 27) {
                StopMediaPlayer();
                bIsRunning = false;
            }
            if (key == 'B' || key == 'b') {
                DisplayProgressBar();
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
        cout << "\n----------------------------------------------Unloading Songs!--------------------------------------------" << endl;
        audioManager.unloadAssets();
        ListSongs();
        cout << "\n----------------------------------------------BYE for now!--------------------------------------------" << endl;
    }
    else if (decision == "N" || decision == "n") {
        cout << "Continue listening..." << endl;
        RunMediaPlayer();
    }
    else {
        cout << "Enter valid choice!" << endl;
        StopMediaPlayer();
    }
}

void cMediaPlayer::ListSongs() {
    char name[256];
    cout << "\n----------------------------------------------List of Songs!--------------------------------------------" << endl;
    for (int index = 0; index < audioManager.sounds.size(); index++) {
        if (audioManager.sounds[index]) {
            // Get the name of the sound
            FMOD_RESULT result = audioManager.sounds[index]->getName(name, sizeof(name));

            if (result == FMOD_OK) {
                // Print the name of the sound
                std::cout << "Song " << index + 1 << ": " << name << std::endl;
            }
            else {
                // Handle errors (e.g., if sound name could not be retrieved)
                std::cout << "Error retrieving the name of sound " << index + 1 << std::endl;
            }
        }
        else {
            std::cout << "Sound " << index + 1 << " is null." << std::endl;
        }
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
    ListSongs();
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

void cMediaPlayer::DisplayProgressBar() {
    unsigned int soundLength = 0;
    unsigned int currentPosition = 0;
    unsigned int barWidth = 100;
    int currentSoundIndex = audioManager.channel->getCurrentSound(&audioManager.sound);
    audioManager.sounds[currentSoundIndex]->getLength(&soundLength, FMOD_TIMEUNIT_MS);
    cout << "------------------------------------------Progress Bar------------------------------------------" << endl;
    cout << "Press any key to hide progress bar" << endl;
    while (true) {
        audioManager.channel->getPosition(&currentPosition, FMOD_TIMEUNIT_MS);
        float progress = float(currentPosition) / float(soundLength);

        int pos = barWidth * progress;
        std::cout << "(";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else std::cout << " ";
        }
        std::cout << ") " << int(progress * 100.0) << " %\r";

        if (_kbhit()) {
            int key = _getch();
            if (key == 27) {
                cout << "Hiding progress bar..." << "%\r"endl;
                break;
            }
            else {
                cout << "Hiding progress bar..." << endl;
                break;
            }
        }
        std::cout.flush();
        // Exit the loop if the sound is done
        if (progress >= 1.0f)
            break;

        // Update every 100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
}
