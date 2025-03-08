#pragma once
#include "types.h"
#include "raylib.h"

class Sprite
{
public:
			Sprite();
			~Sprite();

	// Init
	void	Load(Texture2D* pTexture, rect spriteLocation);

	//
	void	Update();
	void	Render(Color color = WHITE);

	// Accessors
	void	SetPosition(int2 pos)			{ m_SpritePos = pos; }
	int2	GetPosition() const				{ return m_SpritePos; }

	void	SetScale(float scale)			{ m_SpriteScale = scale; };
	float	GetScale() const				{ return m_SpriteScale; }

	// Returns the size of the sprite in pixels multiplied by the scale
	inline int2	GetSize() const;
	inline rect GetRect() const;

	// Returns the size of the sprite in pixels
	int2 GetSpriteSize() const				{ return int2{ m_SpriteRect.size.x, m_SpriteRect.size.y }; };
	
	void SetSpriteSrcRect(rect r)			{ m_SpriteRect = r; }

private:

	int2 m_SpritePos;
	float m_SpriteScale;

	Texture2D* m_pSpriteTexture;
	rect m_SpriteRect; // location in the src texture
};

// Inlines

inline int2 Sprite::GetSize() const 
{
	return int2 {
		static_cast<int>(m_SpriteRect.size.x * m_SpriteScale),
		static_cast<int>(m_SpriteRect.size.y * m_SpriteScale) };
};

inline rect Sprite::GetRect() const
{
	return rect{ GetPosition(), GetSize() };
};