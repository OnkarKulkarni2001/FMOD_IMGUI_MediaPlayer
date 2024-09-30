#include "cMediaPlayer.h"
#include "cAudioManager.h"

cAudioManager audioManager;

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