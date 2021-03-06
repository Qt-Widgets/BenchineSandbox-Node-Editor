#include "BenchinePCH.h"
#include "Resources/ResourceManager.h"
#include "Resources/Loaders.h"
//std::string ResourceManager::m_DataPath = std::string{};
std::map<std::type_index, BaseLoader*> ResourceManager::m_Loaders = std::map<std::type_index, BaseLoader*>();

ResourceManager::~ResourceManager()
{
	for (auto [type, pLoader] : m_Loaders)
	{
		pLoader->ReleaseResources();
		SafeDelete(pLoader);
	}
}

void ResourceManager::Initialize(const std::string& dataPath)
{
	// Set datapath for all the resource loaders
	BaseLoader::SetDataPath(dataPath);
	// Set datapath for external use
	m_DataPath = dataPath;
	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LOG(LEVEL_ERROR, "Failed to load support for pngs: {0}", IMG_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		LOG(LEVEL_ERROR, "Failed to load support for jpgs: {0}", IMG_GetError());
	}

	if (TTF_Init() != 0)
	{
		LOG(LEVEL_ERROR, "Failed to load support for fonts: {0}", TTF_GetError());
	}

	// load SDL_Mixer support
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG(LEVEL_ERROR, "Failed to load support for sound: {0}", Mix_GetError());
	}


	// Initialize Loaders
	AddLoader<Font>(new FontLoader());
	AddLoader<Texture2D>(new TextureLoader());
	AddLoader<SoundByte>(new SoundByteLoader());
	AddLoader<SoundStream>(new SoundStreamLoader());

}
