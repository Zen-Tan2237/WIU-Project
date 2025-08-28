#pragma once
#include <iostream>
#include <string>

class SoundController {
public:
	static void playSound(const std::wstring& filepath);
	static void playSoundLoop(const std::wstring& filepath);
	static void stopSound();

	static void playSoundMP3(const std::string& filepath, bool loop);
	static void stopSoundMP3();
};