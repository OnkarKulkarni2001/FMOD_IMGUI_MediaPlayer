#include "cMediaPlayer.h"
#include "cAudioManager.h"

cAudioManager audioManager();
bool bIsPlaying = false;

void cMediaPlayer::PlayAudio(int index) {
	audioManager.play(index);
	do {
        audioManager.channel->isPlaying(&bIsPlaying);
        if (_kbhit()) {
            char key = _getch();
            if (key == 'V' || key == 'v') {
                setVolume();
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