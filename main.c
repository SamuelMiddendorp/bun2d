#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit();

    int x = 0;
    int y = 0;

    int rectangleY = 100;
    int rectangleX = rand() % 120;
    
    Pixel color = {255,255,255,255};

    while (bun2dTick())
    {
        bun2dClear();
        // Input
        if(keys[KEY_D] == BUN2D_PRESS){
            x++;
        }

        if(keys[KEY_A] == BUN2D_PRESS){
            x--;
        }

        if(keys[KEY_S] == BUN2D_PRESS){
            y--;
        }

        if(keys[KEY_W] == BUN2D_PRESS){
            y++;
        }
        // Rest of the game logic
        rectangleY--;

        if(rectangleY < 0){
            
            rectangleY = 300;
            rectangleX = rand() % 120;
        }
        // Rendering
        bun2dText("iiiiil l \\l        l \\ l iiii", x,y);
        bun2dRect(rectangleX, rectangleY,20,10,0,color);
    }
}
