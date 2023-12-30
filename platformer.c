#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

typedef struct
{
    Vec2 position;
    Vec2 dims;
} Platform;

typedef struct
{
    Vec2 position;
    Vec2 velocity;
    Vec2 dims;
} Player;
    
Platform platforms[100];
int currentPlatAmount;

void makePlatform(int posX, int posY, int width, int height);

int main()
{
    bun2dInit(1, 100, 100, 400, 400);

    Player player = {{5,1},{0,0},{1,2}};
    makePlatform(2,2,2,1);

    while (bun2dTick())
    {
        if(bun2dKey(KEY_D) == BUN2D_PRESS){
            player.position.x++;
        }

        if(bun2dKey(KEY_A) == BUN2D_PRESS){
            player.position.x--;
        }

        bun2dClear();

        // Render platforms;
        for(int i = 0; i < currentPlatAmount; i++)
        {
            Platform p = platforms[i];
            bun2dFillRect(p.position.x, p.position.y, p.dims.x, p.dims.y, RED);
        }
        bun2dFillRect(player.position.x, player.position.y, player.dims.x, player.dims.y, BLUE);
    }
}

void makePlatform(int posX, int posY, int width, int height)
{
    Platform p = {{posX, posY}, {width, height}};
    platforms[currentPlatAmount++] = p;
}
