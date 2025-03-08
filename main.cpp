#include "raylib.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "FlappyBird.h"

constexpr int window_width = 1280;
constexpr int window_height = 720;

int main(void)
{
	std::srand(std::time(nullptr));
	InitWindow(window_width, window_height, "FlappyBird");

    rect canvas;
    canvas.pos.x = 0;
    canvas.pos.y = 0;
    canvas.size.x = window_width;
    canvas.size.y = window_height;

    FlappyBird game(canvas);
    

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

            game.Update(elapsedTime);
            BeginDrawing();
            game.Render();
            EndDrawing();
            lastTime = currentTime;

        }
    }

    CloseWindow();
    return 0;
};