#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

typedef struct{
    int posY;
    int score;
} Player;

int main()
{
    int buffY = 400;
    int buffX = 400;
    int paddleHeight = 50;
    int paddleWidth = 10;

    printf("Pong!");

    Player p1 = {100,0};
    Player p2 = {100,0};
    bun2dInit(1, buffX, buffY, 400, 400);
    while (bun2dTick())
    {
        bun2dClear();
        bun2dRect(0,p1.posY, paddleWidth, paddleHeight);
        bun2dRect(buffY - paddleWidth - 1 , p2.posY, paddleWidth, paddleHeight);
    }
}