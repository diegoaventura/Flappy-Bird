#include "FlappyBird.h"
#include <ctime>
#include <cstdlib>

FlappyBird::FlappyBird(rect canvas)
{
	m_Canvas = canvas;
	InitSprites();
	m_Bird.SetPosition({ m_Canvas.size.x / 10 ,m_Canvas.size.y / 2 });

	m_WorldPosition = 0.f;
	m_WorldSpeed = 1280.f / 4;
	m_BirdSpeed = 0;
	m_BirdPos = m_Canvas.size.y / 2;
	m_TubeSpace.x = 400;
	m_TubeSpace.y = 200;
	m_Score = 0;
	m_TubeMapDirty[0] = true;
	m_TubeMapDirty[1] = true;

	ResetTubeMap(0);
	m_TubeMapDirty[0] = false;
}

FlappyBird::~FlappyBird()
{
	UnloadTexture(m_BirdTexture);
	UnloadTexture(m_BackgroundTexture);
	UnloadTexture(m_TubeTexture);
}

void FlappyBird::Reset()
{
	m_GameState = GameState::Playing;

	m_Bird.SetPosition({ m_Canvas.size.x / 10, m_Canvas.size.y / 2 });

	m_WorldPosition = 0.0f;
	m_WorldSpeed = 1280.0f / 4.0f;

	m_BirdSpeed = 0.0f;
	m_BirdPos = m_Canvas.size.y / 2;

	m_Score = 0;

	m_BirdColor = WHITE;

	m_TubeMapDirty[0] = true;
	m_TubeMapDirty[1] = true;

	ResetTubeMap(0);

	m_TubeMapDirty[0] = false;

}

void FlappyBird::InitSprites()
{
	m_BirdTexture = LoadTexture("data/Bird1-1.png");
	m_BackgroundTexture = LoadTexture("data/background1.png");
	m_TubeTexture = LoadTexture("data/PipeStyle1.png");
	
	// Load and set the scale of the sprites
	m_Background.Load(&m_BackgroundTexture, { {0, 0},{256, 256} });
	m_Background.SetScale(static_cast<float>(m_Canvas.size.y) / m_Background.GetSpriteSize().y);

	// Init sprite rect
	m_TubeSpriteRect[(int)TubeColor::TUBE_GREEN][(int)TubeType::UP] = { {0, 0},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_GREEN][(int)TubeType::MID] = { {0, 26},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_GREEN][(int)TubeType::DOWN] = { {0, 54},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_YELLOW][(int)TubeType::UP] = { {32, 0},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_YELLOW][(int)TubeType::MID] = { {32, 26},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_YELLOW][(int)TubeType::DOWN] = { {32, 54},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_RED][(int)TubeType::UP] = { {64, 0},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_RED][(int)TubeType::MID] = { {64, 26},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_RED][(int)TubeType::DOWN] = { {64, 54},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_BLUE][(int)TubeType::UP] = { {96, 0},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_BLUE][(int)TubeType::MID] = { {96, 26},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_BLUE][(int)TubeType::DOWN] = { {96, 54},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_WHITE][(int)TubeType::UP] = { {0, 80},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_WHITE][(int)TubeType::MID] = { {0, 106},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_WHITE][(int)TubeType::DOWN] = { {0, 134},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_PURPLE][(int)TubeType::UP] = { {32, 80},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_PURPLE][(int)TubeType::MID] = { {32, 106},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_PURPLE][(int)TubeType::DOWN] = { {32, 134},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_BROWN][(int)TubeType::UP] = { {64, 80},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_BROWN][(int)TubeType::MID] = { {64, 106},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_BROWN][(int)TubeType::DOWN] = { {64, 134},{32, 26} };

	m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::UP] = { {96, 80},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::MID] = { {96, 106},{32, 26} };
	m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::DOWN] = { {96, 134},{32, 26} };


	m_TubeUp.Load(&m_TubeTexture, m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::UP]);
	m_TubeUp.SetScale(3.0f);
	m_TubeMid.Load(&m_TubeTexture, m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::MID]);
	m_TubeMid.SetScale(3.0f);
	m_TubeDown.Load(&m_TubeTexture, m_TubeSpriteRect[(int)TubeColor::TUBE_ORANGE][(int)TubeType::DOWN]);
	m_TubeDown.SetScale(3.0f);

	m_Bird.Load(&m_BirdTexture, { {0,0}, {16,16} });
	m_Bird.SetScale(3.0f);
}

FlappyBird::ReturnState FlappyBird::Update(float elapsedTime) 
{
	ReturnState retState = ReturnState::Nothing;

	if (m_GameState == GameState::GameOver)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			Reset();
		}
		if (IsKeyPressed(KEY_M))
			retState = ReturnState::Exit;

		return retState;
	}

	if (m_GameState == GameState::Pause)
	{
		if (IsKeyPressed(KEY_P))
			m_GameState = GameState::Playing;

		if (IsKeyPressed(KEY_M))
			retState = ReturnState::Exit;

		return retState;
	}

	if (IsKeyPressed(KEY_P))
	{
		m_GameState = GameState::Pause;
	}

	// Check if the space is pressed and making the bird fly
	if (IsKeyPressed(KEY_SPACE))
	{
		if (m_BirdSpeed > 0)
		{
			m_BirdSpeed = -400;
		}
		else
		{
			m_BirdSpeed += -400;
			if (m_BirdSpeed < -800)
			{
				m_BirdSpeed = -800;
			}
		}
	}

	if (IsKeyPressed(KEY_KP_ADD))
	{
		m_WorldSpeed += 10;
	}
	if (IsKeyPressed(KEY_KP_SUBTRACT))
	{
		m_WorldSpeed -= 10;
	}


	// Update all the sprites
	m_Background.Update();
	m_TubeUp.Update();
	m_TubeMid.Update();
	m_TubeDown.Update();
	m_Bird.Update();

	// Changing the world position with the speed and the elapsedtime
	m_WorldPosition += m_WorldSpeed * elapsedTime;

	// Changing the speed and the pos of the bird to make that he is falling
	m_BirdSpeed += 800 * elapsedTime;
	m_BirdPos = m_BirdPos + m_BirdSpeed * elapsedTime;
	m_Bird.SetPosition(int2{ m_Bird.GetPosition().x, static_cast<int>(m_BirdPos) });
	if (m_BirdPos < 0 || m_BirdPos > m_Canvas.size.y)
	{
		m_GameState = GameState::GameOver;
	}

	m_BirdColor = WHITE;
	
	m_Score = (m_WorldPosition + (m_Canvas.size.x / 10) ) / m_TubeSpace.x;


	return retState;
}

void FlappyBird::Render()
{
	int bkgOffset = static_cast<int>(m_WorldPosition * 0.5f) % m_Background.GetSize().x;
	m_Background.SetPosition({ -bkgOffset, 0 });
	m_Background.Render();
	
	int endPos = m_Background.GetPosition().x + m_Background.GetSize().x;
	while (endPos < m_Canvas.size.x)
	{
		m_Background.SetPosition({ endPos, 0 });
		m_Background.Render();

		endPos = m_Background.GetPosition().x + m_Background.GetSize().x;
	}

	const int halfTubeSpace = m_TubeSpace.x / 2;
	const int startIdx = static_cast<int>((m_WorldPosition - halfTubeSpace) / m_TubeSpace.x) % kTubeMapSize; // Checking what tube we need to render first
	int endIdx = static_cast<int>((m_WorldPosition + m_Canvas.size.x + halfTubeSpace) / m_TubeSpace.x) % kTubeMapSize; // Checking what tube we need to render last
	const int loopCount = (m_WorldPosition - halfTubeSpace) / (m_TubeSpace.x * kTubeMapSize); // Checking in what loop we are
	const int tubeMapArrayIdx = loopCount % 2;
	const int nextTubeMapArrayIdx = (loopCount + 1) % 2;

	// Checking if we are in the transition of + loop
	if (endIdx < startIdx)
	{
		for (int i = 0; i <= endIdx; i++)
		{
			if (m_TubeMapDirty[nextTubeMapArrayIdx])
			{
				ResetTubeMap(nextTubeMapArrayIdx);
				m_TubeMapDirty[nextTubeMapArrayIdx] = false;
				m_TubeMapDirty[tubeMapArrayIdx] = true;
			}

 			const int posx = (m_TubeSpace.x * i) - static_cast<int>(m_WorldPosition) +
				((loopCount + 1) * kTubeMapSize * m_TubeSpace.x);
			DrawTubes({ posx , m_TubesMap[nextTubeMapArrayIdx][i] }, m_TubeSpace.y, 
				(FlappyBird::TubeColor)((loopCount + 1) % 8));
		}
		endIdx = kTubeMapSize - 1;
	}

	for (int i = startIdx; i < kTubeMapSize; i++)
	{
		const int posx = (m_TubeSpace.x * i) - static_cast<int>(m_WorldPosition) +
			(loopCount * kTubeMapSize * m_TubeSpace.x);
		DrawTubes({ posx , m_TubesMap[tubeMapArrayIdx][i] }, m_TubeSpace.y,
				(FlappyBird::TubeColor)(loopCount % 8));
	}
	
	m_Bird.Render(m_BirdColor);

	DrawText(TextFormat("Score: %02i", m_Score), 5, 5, 55, BLACK);

	switch (m_GameState)
	{
	case GameState::Pause:
		DrawPause();
		break;
	case GameState::GameOver:
		DrawGameOver();
		break;
	}
	 
}

void FlappyBird::DrawTubeUpside(int2 pos, TubeColor color)
{
	m_TubeUp.SetPosition({ pos.x - (m_TubeUp.GetSize().x / 2), pos.y });
	m_TubeUp.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][0]);
	m_TubeUp.Render();

	if (Overlaps(m_Bird.GetRect(), m_TubeUp.GetRect()))
	{
		m_BirdColor = RED;
		m_GameState = GameState::GameOver;
	}

	m_TubeMid.SetPosition({ m_TubeUp.GetPosition().x, m_TubeUp.GetPosition().y + m_TubeUp.GetSize().y });
	m_TubeMid.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][1]);
	m_TubeMid.Render();

	if (Overlaps(m_Bird.GetRect(), m_TubeMid.GetRect()))
	{
		m_BirdColor = RED;
		m_GameState = GameState::GameOver;
	}

	while (m_TubeMid.GetPosition().y + m_TubeMid.GetSize().y <= m_Canvas.size.y)
	{
		int2 tubemidPos = m_TubeMid.GetPosition();
		tubemidPos.y += m_TubeMid.GetSize().y;
		m_TubeMid.SetPosition(tubemidPos);
		m_TubeMid.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][1]);
		m_TubeMid.Render();
		if (Overlaps(m_Bird.GetRect(), m_TubeMid.GetRect()))
		{
			m_BirdColor = RED;
			m_GameState = GameState::GameOver;
		}
	}
}

void FlappyBird::DrawTubeDownside(int2 pos, TubeColor color)
{
	m_TubeDown.SetPosition({ pos.x - (m_TubeDown.GetSize().x / 2), pos.y - m_TubeDown.GetSize().y});
	m_TubeDown.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][2]);
	m_TubeDown.Render();

	if (Overlaps(m_Bird.GetRect(), m_TubeDown.GetRect()))
	{
		m_BirdColor = RED;
		m_GameState = GameState::GameOver;
	}

	m_TubeMid.SetPosition({ m_TubeDown.GetPosition().x, m_TubeDown.GetPosition().y - m_TubeMid.GetSize().y });
	m_TubeMid.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][1]);
	m_TubeMid.Render();

	if (Overlaps(m_Bird.GetRect(), m_TubeMid.GetRect()))
	{
		m_BirdColor = RED;
		m_GameState = GameState::GameOver;
	}

	while (m_TubeMid.GetPosition().y > 0)
	{
		int2 tubemidPos = m_TubeMid.GetPosition();
		tubemidPos.y -= m_TubeMid.GetSize().y;
		m_TubeMid.SetPosition(tubemidPos);
		m_TubeMid.SetSpriteSrcRect(m_TubeSpriteRect[(int)color][1]);
		m_TubeMid.Render();
		if (Overlaps(m_Bird.GetRect(), m_TubeMid.GetRect()))
		{
			m_BirdColor = RED;
			m_GameState = GameState::GameOver;
		}
	}
}

void FlappyBird::DrawTubes(int2 pos, int h, TubeColor color)
{
	DrawTubeUpside({ pos.x, pos.y + h / 2 }, color);
	DrawTubeDownside({ pos.x, pos.y - h / 2 }, color);
}

void FlappyBird::DrawPause()
{
	constexpr int textFontSize = 80;
	constexpr int smallFontSize = textFontSize - 20;

	const int textWidth = MeasureText("Pause", textFontSize);
	const int textX = (m_Canvas.size.x - textWidth) / 2;
	DrawText("Pause", textX, 50, textFontSize, textColor);


	const int menuWidth = MeasureText("Main Menu", smallFontSize);
	const int menuX = (m_Canvas.size.x / 4) - (menuWidth / 2);
	DrawText("Main Menu", menuX, 300, smallFontSize, textColor);
	DrawText("(M)", menuX, 300 + textFontSize, smallFontSize, textColor);

	const int resumeWidth = MeasureText("Resume", smallFontSize);
	const int resumeX = (m_Canvas.size.x * 3 / 4) - (resumeWidth / 2);
	DrawText("Resume", resumeX, 300, smallFontSize, textColor);
	DrawText("(Space)", resumeX, 300 + textFontSize, smallFontSize, textColor);
}

void FlappyBird::DrawGameOver()
{
	constexpr int textFontSize = 80;
	const int textWidth = MeasureText("Game Over", textFontSize);
	const int textX = (m_Canvas.size.x - textWidth) / 2;
	DrawText("Game Over", textX, 50, textFontSize, textColor);

	const int scoreWidth = MeasureText(TextFormat("Score: %02i", m_Score), 40);
	DrawText(TextFormat("Score: %02i", m_Score), (m_Canvas.size.x - scoreWidth) / 2, 150, 40, textColor);

	DrawText("(Space) Retry", textX, 300, 40, textColor);
	DrawText("(M) Main Menu", textX, 350, 40, textColor);
}

void FlappyBird::ResetTubeMap(int n)
{
	for (int i = 0; i < kTubeMapSize; i++)
	{
		m_TubesMap[n][i] = std::rand() % (kTubeMaxPos - kTubeMinPos) + kTubeMinPos;
	}
}