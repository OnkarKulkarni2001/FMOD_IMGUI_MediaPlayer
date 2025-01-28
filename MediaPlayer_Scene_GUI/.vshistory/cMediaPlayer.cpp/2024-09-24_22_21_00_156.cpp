#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>
#include <iostream>
using namespace std;

cAudioManager audioManager;

void cMediaPlayer::StartMediaPlayer() {
    cout << "Welcome to the Media Player developed by Onkar Kulkarni!" << endl;
    cout << "You need to load songs first to listen them. I'll do that for you but you just need to specify the folder name." << endl;
    audioManager.loadAssets();
    cout << "Enjoy listening!" << endl;
}

void cMediaPlayer::RunMediaPlayer() {
    ListSongs();

    cout << "Commands:\n0) P: Play Song\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) U: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n7) Esc: Quit Media Player\n";
    bool bIsRunning = true;
    do {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'P' || key == 'p' ) {
                int indexOfSong = 1;
                cout << "Enter number of song you wanna play: " << endl;
                cin >> indexOfSong;
                audioManager.channel->isPlaying(&audioManager.bIsPlaying);
                PlayAudio(indexOfSong);
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
            if (key == 'U' || key == 'u') {
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
    while (sizeof(audioManager.sounds)) {
        int index = 0;
        int indexOfSongForUser = index + 1;
        cout << indexOfSongForUser << audioManager.sounds[indexOfSongForUser] << endl;
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