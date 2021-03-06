#include "BenchinePCH.h"
#include "Resources/Font.h"
#include "Graphics/GLTextureWrapper.h"
Font::Font(const std::string& fullPath, uint32_t size)
	: m_pFont(TTF_OpenFont(fullPath.c_str(), static_cast<int>(size)))
	, m_pTexture(nullptr)
{
	if (m_pFont == nullptr) 
	{
		LOG(LEVEL_ERROR, "Failed to load font: {0}", TTF_GetError());
	}
}

Font::~Font()
{
	SafeDelete(m_pTexture);
	TTF_CloseFont(m_pFont);
}


GLTextureWrapper* Font::GenerateFontTexture(const std::string& text, const SDL_Color& color)
{
	SafeDelete(m_pTexture);
	const auto pSurface = TTF_RenderText_Blended(m_pFont, text.c_str(), color);

	if (pSurface == nullptr)
	{
		LOG(LEVEL_ERROR, "Surface Invalid: {0}", TTF_GetError());
	}
	
	m_pTexture = new GLTextureWrapper(pSurface);

	SDL_FreeSurface(pSurface);

	return m_pTexture;
}
