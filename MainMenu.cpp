#include "MainMenu.h"
#include "iostream"
#include "cassert"

MainMenu::MainMenu(rect canvas)
{
	m_Canvas = canvas;
	InitSprites();

}


MainMenu::~MainMenu()
{

}

void MainMenu::InitSprites()
{
	m_BirdTexture = LoadTexture("data/Bird1-1.png");
	m_BackgroundTexture = LoadTexture("data/background1.png");

	m_Background.Load(&m_BackgroundTexture, { {0,0},{256,256} });
	m_Background.SetScale((float)m_Canvas.size.y / m_Background.GetSpriteSize().y);
	m_Background.SetPosition({ 0,0 });

	m_Bird.Load(&m_BirdTexture, { {0,0},{16,16} });
	m_Bird.SetScale(3.0f);
	m_Bird.SetPosition({ 100,100 });
}

void MainMenu::Draw()
{
	
	constexpr Color bkgColor = { 0x87, 0xCE, 0xEB, 0xFF }; // Sky Blue
	constexpr Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF }; // Blanco
	// Background
	ClearBackground(bkgColor);

	int bkgOffset = (int)(m_WorldPosition * 0.5f) % m_Background.GetSize().x;

	m_Background.SetPosition({ -bkgOffset, 0 });
	m_Background.Render();

	int endPos = m_Background.GetPosition().x + m_Background.GetSize().x;

	while (endPos < m_Canvas.size.x)
	{
		m_Background.SetPosition({ endPos, 0 });
		m_Background.Render();

		endPos = m_Background.GetPosition().x + m_Background.GetSize().x;
	}

	DrawRectangleRoundedLines(
		{ 20, 20, static_cast<float>(m_Canvas.size.x - 40), static_cast<float>(m_Canvas.size.y - 40) },
		0.2f, 50, 1.0f, textColor);

	// Title
	const int titleWidth = MeasureText("FLAPPY BIRD", titleFontSize);
	const int titleX = (m_Canvas.size.x - titleWidth) / 2;
	DrawText(TextFormat("FLAPPY BIRD"), titleX, 50, titleFontSize, textColor);
	constexpr int titleBottom = 50 + titleFontSize;

	// Options
	Extents optionExtents = GetOptionTexttExtents(0);
	DrawText("New Game", optionExtents.left, optionExtents.top, optionsFontSize, textColor);
	optionExtents = GetOptionTexttExtents(1);
	DrawText("Options", optionExtents.left, optionExtents.top, optionsFontSize, textColor);
	optionExtents = GetOptionTexttExtents(2);
	DrawText("Credits", optionExtents.left, optionExtents.top, optionsFontSize, textColor);
	optionExtents = GetOptionTexttExtents(3);
	DrawText("Exit", optionExtents.left, optionExtents.top, optionsFontSize, textColor);

	// Draw asterisc in selected option
	if (m_OptionSelected != -1)
	{
		optionExtents = GetOptionTexttExtents(m_OptionSelected);
		m_Bird.SetPosition({
	optionExtents.left - m_Bird.GetSize().x - 10,
	optionExtents.top + (optionExtents.height / 2 - m_Bird.GetSize().y / 2)
			});
		m_Bird.Render();
		//DrawText("*", optionExtents.left - MeasureText("* ", optionsFontSize), optionExtents.top, optionsFontSize, textColor);
	}
}

MainMenu::ReturnState MainMenu::Update(float elapsed_sec)
{

	m_WorldPosition += m_WorldSpeed * elapsed_sec;

	m_Background.Update();
	m_Bird.Update();

	m_OptionSelected = -1;

	Vector2 mousePos = GetMousePosition();

	// Check New Game
	if (Extents e = GetOptionTexttExtents(0); CheckBound(&mousePos, &e))
	{
		m_OptionSelected = 0;
	}

	// Check Options
	else if (Extents e = GetOptionTexttExtents(1); CheckBound(&mousePos, &e))
	{
		m_OptionSelected = 1;
	}

	// Check Credits
	else if (Extents e = GetOptionTexttExtents(2); CheckBound(&mousePos, &e))
	{
		m_OptionSelected = 2;
	}

	// Check Exit
	else if (Extents e = GetOptionTexttExtents(3); CheckBound(&mousePos, &e))
	{
		m_OptionSelected = 3;
	}

	// Check Click
	if (IsMouseButtonPressed(0))
	{
		switch (m_OptionSelected)
		{
		case 0:
			return ReturnState::Start;
		case 3:
			return ReturnState::Exit;
		}
	}

	return ReturnState::Nothing;
}

// Returns the extensts of optionIdx option
Extents MainMenu::GetOptionTexttExtents(int optionIdx)
{
	const int titleWidth = MeasureText("FLAPPY BIRD", titleFontSize);
	const int titleX = (m_Canvas.size.x - titleWidth) / 2;
	constexpr int titleBottom = 50 + titleFontSize;
	const int optionsY = ((m_Canvas.size.y - titleBottom) - (titleFontSize * 4)) / 2 + titleFontSize;

	switch (optionIdx)
	{
	case 0: // new game
		return { titleX, optionsY + (optionIdx * optionsFontSize), MeasureText("New Game", optionsFontSize), optionsFontSize };
	case 1: // options
		return { titleX, optionsY + (optionIdx * optionsFontSize), MeasureText("Options", optionsFontSize), optionsFontSize };
	case 2: // credits
		return { titleX, optionsY + (optionIdx * optionsFontSize), MeasureText("Credits", optionsFontSize), optionsFontSize };
	case 3: // Exit
		return { titleX, optionsY + (optionIdx * optionsFontSize), MeasureText("Exit", optionsFontSize), optionsFontSize };
	default:
		assert(false);
		return {};
	}
}

bool MainMenu::CheckBound(const Vector2* p, const Extents* e)
{
	return(p->x >= e->left && p->x < (e->left + e->width)) && (p->y >= e->top && p->y < (e->top + e->height));
}