#pragma once
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "raylib.h"
#include "Sprite.h"
#include "types.h"

struct Extents
{
	int left;
	int top;
	int width;
	int height;
};

class MainMenu
{
public:

	enum class ReturnState
	{
		Nothing,
		Start,
		Exit
	};

	MainMenu(rect canvas);
	~MainMenu();

	void			InitSprites();
	void			Draw();
	ReturnState		Update(float elapsed_sec);

	void			Exit();
	void			EnterGame();

private:

	static constexpr int titleFontSize = 80;
	static constexpr int optionsFontSize = 60;

	Extents GetOptionTexttExtents(int optionIdx);
	static bool CheckBound(const Vector2* p, const Extents* e);

	// -1 = none
	// 0 = New Game
	int m_OptionSelected;

	int m_WindowWidth;
	int m_WindowHeight;

	float m_WorldPosition = 0.f;
	float m_WorldSpeed = 200.f;

	Sprite		m_Bird;
	Sprite		m_Background;

	Texture2D	m_BirdTexture;
	Texture2D	m_BackgroundTexture;

	rect		m_Canvas;

	static int numMMs;
};



#endif
