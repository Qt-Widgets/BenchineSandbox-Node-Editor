#include "BenchinePCH.h"
#include "Resources/SoundStream.h"

SoundStream::SoundStream(const std::string& fullPath)
	: m_pMixMusic(Mix_LoadMUS(fullPath.c_str()))
{
	if (m_pMixMusic == nullptr)
	{
		LOG(LEVEL_ERROR, "Failed to load soundstream: {0}", Mix_GetError());
	}
}

SoundStream::~SoundStream()
{
	Mix_FreeMusic(m_pMixMusic);
	m_pMixMusic = nullptr;
}

void SoundStream::Play(bool shouldRepeat) const noexcept
{
	if (m_pMixMusic != nullptr)
	{
		if (Mix_PlayMusic(m_pMixMusic, shouldRepeat ? -1 : 1))
		{
			LOG(LEVEL_WARNING, "Couldn't play music");
		}
	}
	else
	{
		LOG(LEVEL_WARNING, "SoundStream is nullptr");
	}
}

void SoundStream::Stop() noexcept
{
	Mix_HaltMusic();
}
void SoundStream::Pause() noexcept
{
	Mix_PauseMusic();
}
void SoundStream::Resume() noexcept
{
	Mix_ResumeMusic();
}
void SoundStream::SetVolume(uint32_t volume) noexcept
{
	Mix_VolumeMusic(volume);
}
auto SoundStream::GetVolume() noexcept -> int
{
	return Mix_VolumeMusic(-1);
}
