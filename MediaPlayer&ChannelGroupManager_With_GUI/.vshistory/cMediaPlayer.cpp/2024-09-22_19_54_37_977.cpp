#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <iostream>
#include <conio.h>
#include "fmod.h"
#include "FMODInitialization.h"
#include <vector>
using namespace std;

FMODInitialization initializationObject;
FMOD_RESULT result;
cAudioManager audioManager;
FMOD::System* fmodSystem = initializationObject.Initialized(result);
FMOD::Channel* channel;
FMOD::Sound* sound;
std::vector<FMOD::Sound*> sounds;

void cMediaPlayer::PlayAudio() {
	int index = 0;
	cout << "Enter the index of song you want to play: " << endl;
	cin >> index;

	audioManager.play(index);
    bool bIsPlaying = false;
    cout << "Commands:\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) U: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n";

    do {
        channel->isPlaying(&bIsPlaying);
        if (_kbhit()) {
            char key = _getch();
            if (key == 'V' || key == 'v') {
                AdjustVolume();
            }
            if (key == 'I' || key == 'i') {
                setPitch();
            }
            if (key == 'A' || key == 'a') {
                setPan();
            }
            if (key == 'U' || key == 'u') {
                pause();
            }
            if (key == 'R' || key == 'r') {
                resume();
            }
            if (key == 'S' || key == 's') {
                stop();
            }
        }
        fmodSystem->update();
    } while (bIsPlaying);
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