#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#define MAX_BUNS 100000

int main()
{
    int boundX = 1000;
    int boundY = 1000;
    bun2dInit(0, boundX, boundY, 1000, 1000, "benchmark");
    Model *bun = bun2dLoadModel("bun.csv");
    int *buns = malloc(sizeof(int) * 2 * MAX_BUNS);
    int breakTimer = 0;
    for (int i = 0; i < MAX_BUNS * 2; i += 2)
    {
        buns[i] = 5 + rand() % boundX - 5;
        buns[i + 1] = 5 + rand() % boundY - 5;
    }

    int frameTimer = 0;
    while (bun2dTick())
    {
        bun2dClear();
        bun2dDrawModelBulk(bun, MAX_BUNS, buns);
        if (bun2dKey(KEY_SPACE) == BUN2D_PRESS && breakTimer > 150){
            breakTimer++;
            breakTimer = 0;
            break;
        }
        if (frameTimer > 100)
        {
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        breakTimer++;
        frameTimer++;
    }
    Pixel p = {0, 0, 0, 255};
    while (bun2dTick())
    {
        bun2dClear();
        if (bun2dKey(KEY_SPACE) == BUN2D_PRESS && breakTimer > 150){
            breakTimer++;
            breakTimer = 0;
            break;
        }
        for (int i = 0; i < boundX / 100; i++)
        {
            for (int j = 0; j < boundY / 100; j++)
            {
                bun2dFillRectEXP(i,j,20,20, RED);
            }
        }
        if (frameTimer > 1)   
        {
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        breakTimer++;
        frameTimer++;
    }
}