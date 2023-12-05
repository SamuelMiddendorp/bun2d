#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(0);


    int rectangleY = 100;
    int rectangleX = rand() % 50;
    
    Pixel color = {140,255,255,255};

    while (bun2dTick())
    {
        bun2dColor(color);
        bun2dClear();
        bun2dRect(rectangleX, rectangleY,20,10);
    }
}
