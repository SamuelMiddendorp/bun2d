#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    int width = 20;
    bun2dInit(1,width,width,400,400);
    Pixel color = {255,0,0,255};
    int saveTimer = 0;
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
            if(saveTimer > 10){
                FILE* file;
                file = fopen("model.csv", "w");
            for(int x = 0; x<width ; x++){
            for(int y = 0; y<width ; y++){
                Pixel p = bun2dGetPixel(x,y);
                if(p.a == 255){
                    fprintf(file,
                    "%hhu,%hhu,%hhu,%hhu,%d,%d\n",
                    p.r,
                    p.g,
                    p.b,
                    p.a,
                    x,
                    y
                    );
                }
            }
            }
            fclose(file);
            }
        }
    saveTimer++;
    }
}