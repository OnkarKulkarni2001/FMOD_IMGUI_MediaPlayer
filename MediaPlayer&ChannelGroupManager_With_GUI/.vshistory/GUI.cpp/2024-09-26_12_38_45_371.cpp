#include "imgui/imgui.h"
#include "cMediaPlayer.h"

void cMediaPlayer::StartMediaPlayer() {
    // Initialize media player
    ImGui::Text("Media Player Started");
}

void cMediaPlayer::RunMediaPlayer() {
    // Main loop for media player
    while (true) {
        // Begin new ImGui frame
        ImGui::NewFrame();

        // Create a window
        ImGui::Begin("Media Player Controls");

        // List of songs
        if (ImGui::Button("List Songs")) {
            ListSongs();
        }

        // Play audio
        if (ImGui::Button("Play")) {
            PlayAudio(0); // Assuming first song for demo purposes
        }

        // Pause audio
        if (ImGui::Button("Pause")) {
            PauseAudio();
        }

        // Stop audio
        if (ImGui::Button("Stop")) {
            StopAudio();
        }

        // Adjust pitch with a slider
        static float pitch = 1.0f;  // Default pitch
        if (ImGui::SliderFloat("Pitch", &pitch, 0.5f, 2.0f)) {
            AdjustPitch();  // Adjust pitch based on slider
        }

        // Adjust volume with a slider
        static float volume = 1.0f; // Default volume
        if (ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f)) {
            AdjustVolume();  // Adjust volume based on slider
        }

        // Adjust pan with a slider
        static float pan = 0.0f; // Default center pan
        if (ImGui::SliderFloat("Pan", &pan, -1.0f, 1.0f)) {
            AdjustPan(p);  // Adjust pan based on slider
        }

        // Exit button
        if (ImGui::Button("Exit")) {
            StopMediaPlayer();
            break;  // Break the loop to stop the player
        }

        ImGui::End();

        // Render ImGui frame
        ImGui::Render();
        // Swap buffers, etc. (depending on your rendering system)
    }
}

void cMediaPlayer::StopMediaPlayer() {
    // Clean up and exit media player
    ImGui::Text("Media Player Stopped");
}

// These functions are placeholders for actual media player logic
void cMediaPlayer::ListSongs() { ImGui::Text("Listing Songs..."); }
void cMediaPlayer::PlayAudio(int index) { ImGui::Text("Playing Song..."); }
void cMediaPlayer::PauseAudio() { ImGui::Text("Pausing Song..."); }
void cMediaPlayer::StopAudio() { ImGui::Text("Stopping Song..."); }
void AdjustPitch(float pitch) { ImGui::Text("Adjusting Pitch..."); }
void AdjustVolume(float volume) { ImGui::Text("Adjusting Volume..."); }
void AdjustPan(float pan) { ImGui::Text("Adjusting Pan..."); }

int main() {
    cMediaPlayer mediaPlayer;
    mediaPlayer.StartMediaPlayer();
    mediaPlayer.RunMediaPlayer();
    mediaPlayer.StopMediaPlayer();
    return 0;
}

