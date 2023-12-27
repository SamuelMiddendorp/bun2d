#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

typedef struct{
    int posY;
    int width;
    int height;
    int score;
} Player;

typedef struct{
    int posX;
    int posY;
    int velX;
    int velY;
    int size;
} Ball;

void updateBall(Ball* ball, int wallY);
void updatePlayer1(Player* player, int playerSpeed);
void updatePlayer2(Player* player, int playerSpeed);
void updateGameState(Ball* ball, Player* p1, Player* p2);

int main()
{
    int buffY = 400;
    int buffX = 400;

    Ball ball = {100,100,2,1,10};

    int doSimul = 0;

    int paddleHeight = 50;
    int paddleWidth = 10;

    int playerSpeed = 2;

    Player p1 = {0, paddleWidth, paddleHeight, 0};
    Player p2 = {0, paddleWidth, paddleHeight, 0};

    printf("Pong!");
    bun2dInit(1, buffX, buffY, 800, 800);
    while (bun2dTick())
    {
        if(bun2dKey(KEY_SPACE) == BUN2D_PRESS){
            doSimul = true;
        }

        if(doSimul)
        {
        bun2dClear();
        // Input

        // Logic
        updateBall(&ball, 400);
        updatePlayer1(&p1, playerSpeed);
        updatePlayer2(&p2, playerSpeed);
        updateGameState(&ball, &p1, &p2);
        }
        // Render ball
        bun2dCircle(ball.posX, ball.posY, ball.size);
        // Render players
        bun2dRect(0,p1.posY, paddleWidth, paddleHeight);
        bun2dRect(buffX - paddleWidth - 1 , p2.posY, paddleWidth, paddleHeight);
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

void updateBall(Ball* ball, int wallY){
    if(ball->posY >= wallY || ball->posY <= 0){
        ball->velY = -ball->velY;
    }

    ball->posX += ball->velX;
    ball->posY += ball->velY;
}

void updateGameState(Ball* ball, Player* p1, Player* p2){
    if(ball->posX - ball->size < 0 + p1->width
        && (ball->posY + ball->size > p1->posY
            && (ball->posY + ball->size < p1->posY + p1->height
            )))
    {
        ball->velX = -ball->velX;
    }

    if(ball->posX + ball->size > 400 - p2->width
        && (ball->posY + ball->size > p2->posY
            && (ball->posY + ball->size < p2->posY + p2->height
            )))
    {
        ball->velX = -ball->velX;
    }

    if(ball->posX + ball->size > 400){

        ball->posX = 350;
        ball->posY = 100;
        ball->velX = -2;
        ball->velY = 1;
        p1->score++;
        printf("Point! p1 now has %i points", p1->score);
    }

    if(ball->posX - ball->size < 0){
        ball->posX = 50;
        ball->posY = 100;
        ball->velX = 2;
        ball->velY = 1;
        p2->score++;
        printf("Point! p2 now has %i points", p2->score);
    }
}
