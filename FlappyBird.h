#pragma once
#include "types.h"
#include "raylib.h"
#include "Sprite.h"

class FlappyBird
{
public:

	enum class ReturnState
	{
		Nothing,
		Exit
	};

			FlappyBird(rect canvas);
			~FlappyBird();

	ReturnState	Update(float elapsedTime);
	void		Reset();
	void		Render();


private:

	enum class GameState
	{
		Playing,
		Pause,
		GameOver
	};

	enum class TubeColor
	{
		TUBE_GREEN,
		TUBE_YELLOW,
		TUBE_RED,
		TUBE_BLUE,
		TUBE_WHITE,
		TUBE_PURPLE,
		TUBE_BROWN,
		TUBE_ORANGE
	};

	enum class TubeType
	{
		UP,
		MID,
		DOWN
	};

	static constexpr int kTubeMapSize = 10;
	static constexpr int kTubeMinPos = 100;
	static constexpr int kTubeMaxPos = 600;

	// Init
	void		InitSprites();
	
	void		DrawTubes(int2 pos, int h, TubeColor color);
	void		DrawTubeUpside(int2 pos, TubeColor color);
	void		DrawTubeDownside(int2 pos, TubeColor color);
	void		DrawPause();
	void		DrawGameOver();

	void		ResetTubeMap(int n);

	float		m_WorldPosition;
	float		m_WorldSpeed;

	float		m_BirdSpeed;
	float		m_BirdPos;
	Color		m_BirdColor;
	Color		textColor = { 0xFF, 0xFF, 0xFF, 0xFF }; // Blanco

	GameState	m_GameState;

	int2		m_TubeSpace;
	rect		m_TubeSpriteRect[8][3];

	Sprite		m_Bird;
	Sprite		m_Background;
	Sprite		m_TubeUp;
	Sprite		m_TubeDown;
	Sprite		m_TubeMid;

	Texture2D	m_BirdTexture;
	Texture2D	m_TubeTexture;
	Texture2D	m_BackgroundTexture;

	int			m_TubesMap[2][kTubeMapSize];
	bool		m_TubeMapDirty[2];

	rect		m_Canvas;

	int			m_Score;
};