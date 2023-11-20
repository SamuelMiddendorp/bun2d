#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit();

    while (bun2dTick())
    {
        bun2dClear();
        bun2dText("iiiiil l \\l        l \\ l iiii", 20,20);
    }
}
