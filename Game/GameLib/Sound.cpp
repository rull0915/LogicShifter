#include "Sound.h"

namespace Sound
{
	int standardVolume		= 8;
	int standardSeVolume	= 10;

	std::map<Type, SoundInfo> m_soundInfo;

	void Load()
	{
		// ファイルの読み込み
		m_soundInfo[Type::TitleBgm].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/Classic_Circle.mp3").c_str());
		m_soundInfo[Type::GamePlayBgm].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/はてなパズル.mp3").c_str());
		m_soundInfo[Type::SelectBgm].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/夜汽車の行く先.mp3").c_str());

		m_soundInfo[Type::Decide].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/決定ボタンを押す50.mp3").c_str());
		m_soundInfo[Type::Put].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/カーソル移動9.mp3").c_str());
		m_soundInfo[Type::Clear].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/maou_se_onepoint23.mp3").c_str());
		m_soundInfo[Type::Delete].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/カーソル移動12.mp3").c_str());
		m_soundInfo[Type::Crush].handle = LoadSoundMem(GetAbsolutePath(L"Resources/Sounds/maou_se_onepoint03.mp3").c_str());

		for (auto& sound : m_soundInfo) sound.second.volume = 0xff;

		ChangeVolumeAll();
	}

	void Play(Type type, int playType)
	{
		PlaySoundMem(m_soundInfo[type].handle, playType);
	}

	void Stop(Type type)
	{
		StopSoundMem(m_soundInfo[type].handle);
	}

	void Update(float elapsedTime)
	{
		// 全ての音のチェック
		for(auto& info : m_soundInfo)
		{
			// もしmodeがnoneじゃなかったら
			if(info.second.mode != 0)
			{
				info.second.sumElapsedTime += elapsedTime;

				// 割合
				float ratio = info.second.sumElapsedTime / info.second.fadeTime;
				if (ratio > 1) ratio = 1;

				if (info.second.mode == 1) 
				{
					ChangeVolume(info.first, ratio * 0xff);
				}
				if (info.second.mode == 2)
				{
					ChangeVolume(info.first, (1 - ratio) * 0xff);
				}

				// 1を超えたら
				if(ratio >= 1)
				{
					if (info.second.mode == 2)
					{
						// 音の停止
						Stop(info.first);
					}

					ChangeVolume(info.first, 0xff);

					info.second.mode = 0;

					info.second.sumElapsedTime = 0;
				}
			}
		}
	}

	bool CheckPlay(Type type)
	{
		return CheckSoundMem(m_soundInfo[type].handle);

		return false;
	}
	void ChangeVolumeAll()
	{
		for(auto sound : m_soundInfo)
		{
			if (static_cast<int>(sound.first) < static_cast<int>(Type::BgmCount))
			{
				ChangeVolumeSoundMem(sound.second.volume * static_cast<float>(standardVolume) / 10, sound.second.handle);
			}
			else
			{
				ChangeVolumeSoundMem(sound.second.volume * static_cast<float>(standardSeVolume) / 10, sound.second.handle);
			}
		}
	}

	void ChangeVolumeAllBGM(int val)
	{
		standardVolume = val;
		ChangeVolumeAll();
	}

	void ChangeVolumeAllSE(int val)
	{
		standardSeVolume = val;
		ChangeVolumeAll();
	}

	void ChangeVolume(Type type, int vol)
	{
		m_soundInfo[type].volume = vol;

		ChangeVolumeAll();
	}

	void FadeIn(Type type, float time)
	{
		if (!CheckPlay(type))
		{
			Play(type, DX_PLAYTYPE_LOOP);
		}

		m_soundInfo[type].fadeTime = time;
		m_soundInfo[type].mode = 1;
		m_soundInfo[type].sumElapsedTime = 0;
	}

	void FadeOut(Type type, float time)
	{
		m_soundInfo[type].fadeTime = time;
		m_soundInfo[type].mode = 2;
		m_soundInfo[type].sumElapsedTime = 0;
	}
}