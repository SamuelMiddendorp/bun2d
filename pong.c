#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

typedef struct{
    int posY;
    int score;
} Player;

typedef struct{
    int posX;
    int posY;
    int velX;
    int velY;
} Ball;

int main()
{
    int buffY = 400;
    int buffX = 400;

    Ball ball = {100,100,2,2};

    int paddleHeight = 50;
    int paddleWidth = 10;

    Player p1 = {100,0};
    Player p2 = {100,0};

    printf("Pong!");
    bun2dInit(1, buffX, buffY, 400, 400);
    while (bun2dTick())
    {
        bun2dClear();
        // Input


        // Render ball
        bun2dCircle(ball.posX, ball.posY, 5);
        // Render players
        bun2dRect(0,p1.posY, paddleWidth, paddleHeight);
        bun2dRect(buffY - paddleWidth - 1 , p2.posY, paddleWidth, paddleHeight);
    }
}