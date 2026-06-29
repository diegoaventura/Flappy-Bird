    #include "raylib.h"
    #include <cassert>
    #include <cstdlib>
    #include <ctime>
#include "FlappyBird.h"
#include "MainMenu.h"

constexpr int window_width = 1280;
constexpr int window_height = 720;

enum class AppState
{
    MainMenu,
    Game
};

int main(void)
{
	std::srand(std::time(nullptr));
	InitWindow(window_width, window_height, "FlappyBird");

    rect canvas;
    canvas.pos.x = 0;
    canvas.pos.y = 0;
    canvas.size.x = window_width;
    canvas.size.y = window_height;

    MainMenu menu(canvas);
    FlappyBird game(canvas);

    AppState appState = AppState::MainMenu;    

    double lastTime = GetTime();
    bool shouldExit = false;
    while (!WindowShouldClose() && !shouldExit)
    {
        double currentTime = GetTime();
        double elapsedTime = currentTime - lastTime;

        if (elapsedTime > 1.0 / 60)
        {
            if (elapsedTime > 0.1f)
                elapsedTime = 0.1f;

            lastTime = currentTime;

            switch (appState)
            {
            case AppState::MainMenu:
            {
                MainMenu::ReturnState state = menu.Update(elapsedTime);

                if (state == MainMenu::ReturnState::Start)
                {
                    appState = AppState::Game;
                    // Reiniciar el juego si tienes una función Reset()
                }
                else if (state == MainMenu::ReturnState::Exit)
                {
                    shouldExit = true;
                }
            }
            break;

            case AppState::Game:
            {
                game.Update(elapsedTime);

                // Si tu juego tiene Game Over y quieres volver al menú:
                // if (game.GameOver())
                //     appState = AppState::MainMenu;
            }
            break;
        }
        BeginDrawing();

        switch (appState)
        {
        case AppState::MainMenu:
            menu.Draw();
            break;

        case AppState::Game:
            game.Render();
            break;
        }

        EndDrawing();
        

        }
    }

    CloseWindow();
    return 0;
};