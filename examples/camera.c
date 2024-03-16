#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 100, 100, 400, 400, "camera");
    Pixel textColor = { 255,
                        255,
                        255,
                        255 };
    Vec2 cameraPos = {0,0};
    float timer;
    while (bun2dTick())
    {
        bun2dClear();
        cameraPos.x += (bun2dGetFrameTime() / 1000);
        bun2dText("0123456789", 20 - cameraPos.x, 20 - cameraPos.y, textColor);
    }
}