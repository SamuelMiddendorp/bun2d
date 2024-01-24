#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(0, 5,5,400,400);
    Pixel color = {255,0,0,255};
    while (bun2dTick())
    {
        if(bun2dKey(KEY_W) == 1 || bun2dKey(KEY_W) == 2){
            Point foo = bun2dGetMouse();
            bun2dPixel(foo.x, foo.y, color);
        }
        if(bun2dKey(KEY_D) == 1 || bun2dKey(KEY_D) == 2){
            Point foo = bun2dGetMouse();
            bun2dClearPixel(foo.x, foo.y);
        }
        if(bun2dKey(KEY_S) == 1){
            for(int x = 0; x<5 ; x++){
            for(int y = 0; y<5 ; y++){
                if(bun2dGetPixel(x,y).a == 255){
                    printf("%i,%i,", x,y);
                }
            }
            }
            printf("\n");
        }
    }
}

