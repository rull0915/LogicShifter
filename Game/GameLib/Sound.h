#pragma once
#include "DxLib.h"

struct SoundInfo
{
	int handle;
	int volume;

	// 0: None
	// 1: In
	// 2: Out
	int mode;

	float fadeTime;

	float sumElapsedTime;
};

namespace Sound {

	static constexpr int MAX_VOLUME = 10;
	static constexpr int MIN_VOLUME = 0;

	extern int standardVolume;
	extern int standardSeVolume;

	enum class Type
	{
		None = 0,
		TitleBgm,
		GamePlayBgm,
		SelectBgm,
		ResultBgm,

		// bgmÉnÉìÉhÉãÇÃêî
		BgmCount,

		// à»â∫SE
		Decide,
		Put,
		Delete,
		Clear,
		Crush,
	};

	extern std::map<Type, SoundInfo>m_soundInfo;

	void Load();

	void Play(Type type, int playType);

	void Stop(Type type);

	void Update(float elapsedTime);

	bool CheckPlay(Type type);

	void ChangeVolumeAll();
	void ChangeVolumeAllBGM(int val);
	void ChangeVolumeAllSE(int val);
	void ChangeVolume(Type type, int vol);

	void FadeIn(Type type, float time);
	void FadeOut(Type type, float time);
}