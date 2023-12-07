#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(0);


    int rectangleY = 100;
    int rectangleX = rand() % 50;
    
    while (bun2dTick())
    {
        bun2dColor(red);
        bun2dClear();
        bun2dRect(rectangleX, rectangleY,20,10);
    }
}
