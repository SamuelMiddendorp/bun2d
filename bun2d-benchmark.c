#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#define MAX_BUNS 100000

int main()
{
    int boundX = 1000;
    int boundY = 1000;
    bun2dInit(0, boundX, boundY, 1000, 1000);
    Model *bun = bun2dLoadModel("bun.csv");
    int *buns = malloc(sizeof(int) * 2 * MAX_BUNS);
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
        if (frameTimer > 100)
        {
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
            break;
        }
        frameTimer++;
    }
    Pixel p = {0, 0, 0, 255};
    while (bun2dTick())
    {
        bun2dClear();
        for (int i = 0; i < boundX; i++)
        {
            p.r = ((float)255/boundX) * i;
            for (int j = 0; j < boundY; j++)
            {
                p.b = ((float)255/boundX) * j;
                bun2dPixel(i, j, p);
            }
        }
        p.r = 0;
        p.b = 0;
        if (frameTimer > 100)
        {
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        frameTimer++;
    }
}