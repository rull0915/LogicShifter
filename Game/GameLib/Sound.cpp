#include "Sound.h"

namespace Sound
{
	int standardVolume		= 5;
	int standardSeVolume	= 5;

	int volume_hat			= 0xff;
	int volume_kick			= 0xff;
	int volume_snare		= 0xff;
	int volume_cymbal		= 0xff;

	int hatSoundMem			= -1;
	int kickSoundMem		= -1;
	int snareSoundMem		= -1;
	int cymbalSoundMem		= -1;

	void Load()
	{
		// ÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
		hatSoundMem			= LoadSoundMem(L"Resources/Sounds/hat.wav");
		kickSoundMem		= LoadSoundMem(L"Resources/Sounds/kick.wav");
		snareSoundMem		= LoadSoundMem(L"Resources/Sounds/snare.wav");
		cymbalSoundMem		= LoadSoundMem(L"Resources/Sounds/cymbal.wav");
	}

	void Play(Type type)
	{
		switch (type)
		{
		case Type::Hihat:		PlaySoundMem(hatSoundMem, DX_PLAYTYPE_BACK);		break;
		case Type::Kick:		PlaySoundMem(kickSoundMem, DX_PLAYTYPE_BACK);		break;
		case Type::Snare:		PlaySoundMem(snareSoundMem, DX_PLAYTYPE_BACK);		break;
		case Type::Cymbal:		PlaySoundMem(cymbalSoundMem, DX_PLAYTYPE_BACK);		break;
		}
	}

	void Stop(Type type)
	{
		switch (type)
		{
		case Type::Hihat:		StopSoundMem(hatSoundMem);			break;
		case Type::Kick:		StopSoundMem(kickSoundMem);			break;
		case Type::Snare:		StopSoundMem(snareSoundMem);		break;
		case Type::Cymbal:		StopSoundMem(cymbalSoundMem);		break;
		}
	}

	bool CheckPlay(Type type)
	{
		switch (type)
		{
		case Type::Hihat:		return CheckSoundMem(hatSoundMem);			break;
		case Type::Kick:		return CheckSoundMem(kickSoundMem);			break;
		case Type::Snare:		return CheckSoundMem(snareSoundMem);		break;
		case Type::Cymbal:		return CheckSoundMem(cymbalSoundMem);		break;
		}
		return false;
	}
	void ChangeVolumeAll()
	{
		ChangeVolumeSoundMem(volume_hat		* static_cast<float>(standardSeVolume) / 10,hatSoundMem);
	}

	void ChangeVolume(Type type, int vol)
	{
		switch (type)
		{
		case Type::Hihat:		volume_hat = vol;		break;
		case Type::Kick:		volume_kick = vol;		break;
		case Type::Snare:		volume_snare = vol;		break;
		case Type::Cymbal:		volume_cymbal = vol;	break;
		}
		ChangeVolumeAll();
	}
}