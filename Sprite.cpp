#include "Sprite.h"
#include <ctime>
#include <cstdlib>

Sprite::Sprite()
{
	m_SpritePos = { 0, 0 };
	m_SpriteScale = 1.0f;
}

Sprite::~Sprite()
{
}

void Sprite::Load(Texture2D* pTexture, rect spriteLocation)
{
	m_pSpriteTexture = pTexture;
	m_SpriteRect = spriteLocation;
}

void Sprite::Update()
{

}

void Sprite::Render(Color color)
{
	Rectangle srcRect;
	srcRect.x = m_SpriteRect.pos.x;
	srcRect.y = m_SpriteRect.pos.y;
	srcRect.width = m_SpriteRect.size.x;
	srcRect.height = m_SpriteRect.size.y;

	Rectangle dstRect;
	dstRect.x = m_SpritePos.x;
	dstRect.y = m_SpritePos.y;
	dstRect.width = m_SpriteRect.size.x * m_SpriteScale;
	dstRect.height = m_SpriteRect.size.y * m_SpriteScale;

	// Draw a part of a texture defined by a rectangle with 'pro' parameters
	DrawTexturePro(*m_pSpriteTexture, srcRect, dstRect, { 0.0f, 0.0f }, 0.f, color);
}
