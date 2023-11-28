#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(0);

    int x = 0;
    int y = 0;

    int rectangleY = 100;
    int rectangleX = rand() % 120;
    
    Pixel color = {140,255,255,255};
    Pixel color2 = {255,0,0,255};

    while (bun2dTick())
    {
        bun2dColor(color);
        bun2dClear();
        // Input
        if(bun2dKey(KEY_D) == BUN2D_PRESS){
            x++;
        }

        if(bun2dKey(KEY_A) == BUN2D_PRESS){
            x--;
        }

        if(bun2dKey(KEY_S) == BUN2D_PRESS){
            y--;
        }

        if(bun2dKey(KEY_W) == BUN2D_PRESS){
            y++;
        }
        // Rest of the game logic
        rectangleY--;

        if(rectangleY < 0){
            
            rectangleY = 300;
            rectangleX = rand() % 120;
        }
        // Rendering
        bun2dPixel(20,30, color);
        bun2dText("lll", x,y);
        bun2dColor(color2);
        bun2dRect(rectangleX, rectangleY,20,10,0);

    }
}
