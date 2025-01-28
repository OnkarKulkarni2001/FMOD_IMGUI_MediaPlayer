#include "cMediaPlayer.h"
#include "cChannelGroupManager.h"
#include <conio.h>
#include <iostream>


using namespace std;

void cMediaPlayer::RunMediaPlayer(GLFWwindow* window) {

    bool bIsRunning = true;

    // Main loop for ImGui rendering
    while (bIsRunning) {

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(800, 600));  // Setting the window size to 800x600 pixels
        // Create a window for the media player
        ImGui::Begin("Media Player");
        ImGui::Text("Welcome to the Media Player developed by Onkar Kulkarni!");
        
        channelGroupManager.CreateChannelGroup();
        
        channelGroupManager.LoadScene();


        if (ImGui::Button("Play selected scene")) {
            FMOD_VECTOR listenerPosition = { 0.0, 0.0, 0.0 };
            FMOD_VECTOR listenerForward = { 0.0, 0.0, 1.0 };
            FMOD_VECTOR listenerUp = { 0.0, 1.0, 0.0 };

            channelGroupManager.setListenerAttributes(listenerPosition, listenerForward, listenerUp);
            for (int index = 1; index <= channelGroupManager.sounds.size(); index++) {
                PlayAudio(index);
                if (index == 2) {
                    FMOD_VECTOR soundPosition = { 5.0, 0.0, 0.0 };
                    channelGroupManager.channel->set3DAttributes(&soundPosition, nullptr);
                }
            }

            for (int i = 0; i < 10; ++i) {
                listenerPosition.x += 1.0f;
                channelGroupManager.setListenerAttributes(listenerPosition, listenerForward, listenerUp);

                channelGroupManager.Update();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        
        FMOD::ChannelGroup* channelGroup = channelGroupManager.getChannelGroup();
        channelGroupManager.PrintChannelGroupInfo();

        // Variable to store the index of the selected song
        static int selectedSongIndex = -1;

        // Listing Songs using ImGui ListBox
        if (!channelGroupManager.sounds.empty()) {
            ImGui::Text("Songs available:");
            if (ImGui::BeginListBox("##SongListBox", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing()))) {
                for (int i = 0; i < channelGroupManager.sounds.size(); i++) {
                    int userInput = i + 1;
                    char name[256];
                    if (channelGroupManager.sounds[i]) {
                        FMOD_RESULT result = channelGroupManager.sounds[i]->getName(name, sizeof(name));
                        if (result == FMOD_OK) {
                            // Making each song selectable
                            bool isSelected = (selectedSongIndex == i); // Check if this is the selected song
                            if (ImGui::Selectable(name, isSelected)) {
                                selectedSongIndex = i; // Marking the clicked song as selected
                                FMOD::Channel* channel = nullptr;
                                PlayAudio(userInput); // Playing the selected song
                            }
                            if (isSelected) {
                                ImGui::SetItemDefaultFocus(); // Ensuring the selected item remains in focus
                            }
                        }
                    }
                }
                ImGui::EndListBox();
            }
        }
        else {
            ImGui::Text("No songs loaded. Please load songs first.");
        }
        channelGroupManager.SetChannelGroupDSP();

        if (channelGroupManager.channel) {
            unsigned int position;
            channelGroupManager.channel->getPosition(&position, FMOD_TIMEUNIT_MS); // Get current position

            unsigned int length;
            channelGroupManager.sounds[selectedSongIndex]->getLength(&length, FMOD_TIMEUNIT_MS); // Get sound length

            float progress = static_cast<float>(position) / length; // Calculate progress
            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "Current Position");
            ImGui::Text("Position: %.2f / %.2f seconds", position / 1000.0f, length / 1000.0f);
        }

        // Volume Control Slider
        if (selectedSongIndex != -1) {  // Ensure a song is selected
            ImGui::Text("Volume Control:");
            if (ImGui::SliderFloat("Volume", &channelGroupManager.volumeValue, 0.0f, 10.0f)) {
                // Set volume whenever the slider is moved
                channelGroupManager.setVolume(channelGroupManager.volumeValue);
            }
        }

        // Pitch Control Slider
        if (selectedSongIndex != -1) {  // Ensure a song is selected
            ImGui::Text("Pitch Control:");
            if (ImGui::SliderFloat("Pitch", &channelGroupManager.pitchValue, 0.0f, 10.0f)) {
                // Set pitch whenever the slider is moved
                channelGroupManager.setPitch(channelGroupManager.pitchValue);
            }
        }

        // Volume Control Slider
        if (selectedSongIndex != -1) {  // Ensure a song is selected
            ImGui::Text("Pan Control:");
            if (ImGui::SliderFloat("Pan", &channelGroupManager.panValue, -1.0f, 1.0f)) {
                // Setting pan whenever the slider is moved
                channelGroupManager.setPan(channelGroupManager.panValue);
            }
        }

        // Pause, Resume, and Stop Controls
        if (ImGui::Button("Pause")) {
            PauseAudio();
        }
        if (ImGui::Button("Resume")) {
            channelGroupManager.resume();
        }
        if (ImGui::Button("Stop")) {
            StopAudio();
        }

        // Quit
        if (ImGui::Button("Quit")) {
            break;
        }
        channelGroupManager.unloadAssets();

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

void cMediaPlayer::PlayAudio(int index) {
    channelGroupManager.play(index);
}

void cMediaPlayer::PauseAudio() {
    channelGroupManager.pause();
}

void cMediaPlayer::StopAudio() {
    channelGroupManager.stop();
}

void cMediaPlayer::AdjustPitch() {
    float pitch = 0.0;
    channelGroupManager.setPitch(pitch);
}

void cMediaPlayer::AdjustVolume() {
    float volume = 0.0;
    channelGroupManager.setVolume(volume);
}

void cMediaPlayer::AdjustPan() {
    float pan = 0.0;
    channelGroupManager.setPan(pan);
}