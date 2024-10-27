#pragma once
class cAudioManager {
public:
	FMOD::Channel* channel;
	//FMOD::System* fmodSystem;
	FMOD::System* fmodSystem = initializationObject.Initialized(result);

	bool bIsPlaying = false;
	bool bIsPaused = false;
	float pitchValue = 0;
	float panValue = 0;
	float volumeValue = 0;
	void loadAssets();
	void unloadAssets();

	void play(int index);
	void pause();
	void resume();
	void stop();
	void setPitch();
	void setVolume();
	void setPan();
};