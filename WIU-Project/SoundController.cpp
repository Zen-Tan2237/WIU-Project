#include "SoundController.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//*************************************
// Made by Zen! Just using windows APIs nothing special here...
// USAGE INSTRUCTIONS!
// Call the function by doing:
// filePath is "resources\soundfile.wav" (MUST BE IN WAV FORMAT!!)
// SoundController::playSound(L"resources\\soundfile.wav");
// playSound just plays the sound file
// playSoundLoop plays the sound in a loop
// stopSound stops the sound from playing
//*************************************

void SoundController::playSound(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundController::playSoundLoop(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // just adds that loop flag
}

void SoundController::stopSound() {
    PlaySound(NULL, 0, 0); // stops everything
}

void SoundController::playSoundMP3(const std::string& filePath, bool loop) {
    std::wstring wPath(filePath.begin(), filePath.end());

    // Open the MP3
    mciSendString((L"open \"" + wPath + L"\" type mpegvideo alias mp3").c_str(), NULL, 0, NULL);

    // Play it
    if (loop) {
        mciSendString(L"play mp3 repeat", NULL, 0, NULL);
    }
    else {
        mciSendString(L"play mp3", NULL, 0, NULL);
    }
}

void SoundController::stopSoundMP3() {
    mciSendString(L"stop mp3", NULL, 0, NULL);
    mciSendString(L"close mp3", NULL, 0, NULL);
}