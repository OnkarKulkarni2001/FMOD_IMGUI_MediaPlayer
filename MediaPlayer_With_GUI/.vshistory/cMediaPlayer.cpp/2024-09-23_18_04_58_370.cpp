#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>
#include <iostream>
using namespace std;

cAudioManager audioManager;
//bool bIsPlaying = false;

void cMediaPlayer::RunMediaPlayer() {
    cout << "Welcome to the Media Player developed by Onkar Kulkarni!\n\n" << endl;
    cout << "You need to load songs first to listen them. I'll do that for you but you just need to specify the folder name.\n\n" << endl;
    audioManager.loadAssets();
    cout << "Enjoy listening!\n\n" << endl;
}

void cMediaPlayer::StopMediaPlayer() {
    string decision;
    cout << "You want to quit? Are you sure? YES = Y, NO = N " << endl;
    cin >> decision;
    if (decision == "Y" || decision == "y") {
        audioManager.stop();
        audioManager.unloadAssets();
    }
    if (decision == "N" || decision == "n") {
        cout << "Continue listening...\n\n" << endl;
    }
    else {
        cout << "Enter valid choice!" << endl;
        StopMediaPlayer();
    }
}

void cMediaPlayer::PlayAudio() {
    int indexOfSong = 1;
    cout << "Enter number of song you wanna play: " << endl;
    cin >> indexOfSong;
	audioManager.play(indexOfSong);

    cout << "Commands:\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) U: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n";
	do {
        if (_kbhit()) {
            char key = _getch();
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
            }
            if (key == 'R' || key == 'r') {
                audioManager.resume();
            }
            if (key == 'S' || key == 's') {
                StopAudio();
            }
        }
        //audioManager.fmodSystem.update();
	} while (audioManager.bIsPlaying);
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