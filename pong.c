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

void updateBall(Ball* ball, int wallX, int wallY);
void updatePlayer1(Player* player, int playerSpeed);
void updatePlayer2(Player* player, int playerSpeed);

int main()
{
    int buffY = 400;
    int buffX = 400;

    Ball ball = {100,100,4,2};

    int paddleHeight = 50;
    int paddleWidth = 10;

    int playerSpeed = 2;

    Player p1 = {0,0};
    Player p2 = {0,0};

    printf("Pong!");
    bun2dInit(1, buffX, buffY, 400, 400);
    while (bun2dTick())
    {
        bun2dClear();
        // Input

        // Logic
        updateBall(&ball, 400, 400);
        updatePlayer1(&p1, playerSpeed);
        updatePlayer2(&p2, playerSpeed);

        // Render ball
        bun2dCircle(ball.posX, ball.posY, 5);
        // Render players
        bun2dRect(0,p1.posY, paddleWidth, paddleHeight);
        bun2dRect(buffY - paddleWidth - 1 , p2.posY, paddleWidth, paddleHeight);
    }
}

void updatePlayer1(Player* player, int playerSpeed){
    if(bun2dKey(KEY_W) > 0){
        player->posY+=playerSpeed;
    }
    if(bun2dKey(KEY_S) > 0){
        player->posY-=playerSpeed;
    }
}

void updatePlayer2(Player* player, int playerSpeed){
    if(bun2dKey(KEY_UP) > 0){
        player->posY+=playerSpeed;
    }
    if(bun2dKey(KEY_DOWN) > 0){
        player->posY-=playerSpeed;
    }
}

void updateBall(Ball* ball, int wallX, int wallY){
    if(ball->posX >= wallX || ball->posX <= 0){
        ball->velX = -ball->velX;
    }

    if(ball->posY >= wallY || ball->posY <= 0){
        ball->velY = -ball->velY;
    }

    ball->posX += ball->velX;
    ball->posY += ball->velY;
}