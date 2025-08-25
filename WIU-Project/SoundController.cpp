#include "SoundController.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void SoundController::playSound(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundController::playSoundLoop(const std::wstring& filePath) {
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void SoundController::stopSound() {
    PlaySound(NULL, 0, 0); // stops everything
}
