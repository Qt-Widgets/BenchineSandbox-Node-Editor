#pragma once
#include "Helpers/Singleton.hpp"
#include "Helpers/GeneralHelpers.hpp"

struct SDL_Window;
class GLTextureWrapper;
class Renderer final : public Singleton<Renderer>
{
public:
	explicit Renderer(Token) {}
	virtual ~Renderer();

	void Initialize(const WindowSettings& windowSettings);
	void SetupRender() const;
	void PresentRender() const;

	[[nodiscard]] constexpr auto GetWindowSettings() const noexcept-> const WindowSettings& { return m_WindowSettings; }


	void RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos, const glm::vec2& scale) const;

private:

	void Cleanup();

	WindowSettings m_WindowSettings;
	SDL_GLContext m_pContext;
	SDL_Window* m_pWindow;

	std::array<VertexUV, 4> CreateRenderParams(GLTextureWrapper* pTexture) const;
};

