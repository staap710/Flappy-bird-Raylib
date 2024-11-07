#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Square Game");
    SetTargetFPS(60);

    // Game variables
    Vector2 squarePosition = { 100, SCREEN_HEIGHT / 2 };
    float squareSize = 20.0f;
    float gravity = 0.5f;
    float jumpForce = -10.0f;
    float velocityY = 0;

    // Obstacle variables
    float obstacleWidth = 50;
    float obstacleGap = 200;
    float obstacleX = SCREEN_WIDTH;
    float obstacleHeight = GetRandomValue(100, SCREEN_HEIGHT - 100);

    // Score variable
    int score = 0;

    while (!WindowShouldClose()) {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            velocityY = jumpForce; // Jump
        }

        velocityY += gravity; // Apply gravity
        squarePosition.y += velocityY; // Move square

        // Update obstacle position
        obstacleX -= 5; // Move obstacle left
        if (obstacleX < -obstacleWidth) {
            obstacleX = SCREEN_WIDTH;
            obstacleHeight = GetRandomValue(100, SCREEN_HEIGHT - 100);
            score++;  // Increase score when the player successfully passes an obstacle
        }

        // Collision detection
        if (squarePosition.y + squareSize > SCREEN_HEIGHT || squarePosition.y < 0) {
            // Reset game if square hits the ground or goes out of bounds
            squarePosition.y = SCREEN_HEIGHT / 2;
            velocityY = 0;
            obstacleX = SCREEN_WIDTH;
            score = 0; // Reset score on game over
        }

        // Check collision with the obstacle
        if (obstacleX < squarePosition.x + squareSize && obstacleX + obstacleWidth > squarePosition.x) {
            if (squarePosition.y < obstacleHeight || squarePosition.y + squareSize > obstacleHeight + obstacleGap) {
                // Reset game on collision
                squarePosition.y    = SCREEN_HEIGHT / 2;
                velocityY = 0;
                obstacleX = SCREEN_WIDTH;
                score = 0; // Reset score on collision
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the square
        DrawRectangle(squarePosition.x, squarePosition.y, squareSize, squareSize, BLUE);

        // Draw the obstacle
        DrawRectangle(obstacleX, 0, obstacleWidth, obstacleHeight, GREEN);
        DrawRectangle(obstacleX, obstacleHeight + obstacleGap, obstacleWidth, SCREEN_HEIGHT, GREEN);

        // Draw the score
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}