#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>

cAudioManager audioManager;
FMOD::Channel* channel = audioManager.channel;
bool bIsPlaying = false;

void cMediaPlayer::PlayAudio(int index) {
	audioManager.play(index);
	do {
        channel->isPlaying(&bIsPlaying);
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
        audioManager.fmodSystem->update();
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