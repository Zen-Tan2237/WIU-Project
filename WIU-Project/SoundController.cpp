#include "SoundController.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//*************************************
// USAGE INSTRUCTIONS!
// Call the function by doing:
// filePath is 'resources\soundfile.wav' (MUST BE IN WAV FORMAT!!)
// SoundController::playSound(filePath)
// playSound just plays the sound file
// playSoundLoop plays the sound in a loop
// stopSound stops the sound from playing
//*************************************

void SoundController::playSound(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundController::playSoundLoop(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void SoundController::stopSound() {
    PlaySound(NULL, 0, 0); // stops everything
}
