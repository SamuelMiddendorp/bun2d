#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit();
    int x = 0;
    int y = 0;
    while (bun2dTick())
    {
        bun2dClear();
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

        bun2dText("iiiiil l \\l        l \\ l iiii", x,y);
    }
}
