#pragma once
class cMediaPlayer {
public:
	void StartMediaPlayer();
	void RunMediaPlayer(GLFWwindow* window);
	void StopMediaPlayer();
	void ListSongs();
	void PlayAudio(int index);
	void PauseAudio();
	void StopAudio();
	void AdjustPitch();
	void AdjustVolume();
	void AdjustPan();
};

