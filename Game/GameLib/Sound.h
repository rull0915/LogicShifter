#pragma once
#include "DxLib.h"

namespace Sound {

	static constexpr int MAX_VOLUME = 10;
	static constexpr int MIN_VOLUME = 0;

	static constexpr int VOLUME_GAMECLEAR = 200;

	extern int standardVolume;
	extern int standardSeVolume;

	extern int volume_hat;
	extern int volume_kick;
	extern int volume_snare;
	extern int volume_cymbal;

	extern int hatSoundMem;
	extern int kickSoundMem;
	extern int snareSoundMem;
	extern int cymbalSoundMem;

	enum class Type
	{
		Hihat,
		Kick,
		Snare,
		Cymbal,
	};

	void Load();

	void Play(Type type);

	void Stop(Type type);

	bool CheckPlay(Type type);

	void ChangeVolumeAll();
	void ChangeVolume(Type type, int vol);
}