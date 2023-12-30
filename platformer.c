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
    
void makePlatform(int posX, int posY, int width, int height);

Platform* platforms;
int currentPlatAmount = 0;

int main()
{
    platforms = calloc(10, sizeof(Platform));
    bun2dInit(1, 20, 20, 400, 400);
    while (bun2dTick())
    {
        bun2dClear();
        makePlatform(2,2,2,2);
        makePlatform(2,8,2,2);
        // Render platforms;
        for(int i = 0; i < currentPlatAmount; i++)
        {
            Platform p = platforms[i];
            bun2dFillRect(p.position.x, p.position.y, p.dims.x, p.dims.y, RED);
        }
    }
}

void makePlatform(int posX, int posY, int width, int height)
{
    Platform p = {{posX, posY}, {width, height}};
    platforms[currentPlatAmount++] = p;
}
