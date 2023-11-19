#define BUN2D_IMPLEMENTATION 
#include <main2.h>
int main()
{
    bun2dInit();

    while (bun2dTick())
    {
        bun2dClear();
        bun2dText("iiiiil l \\l", 20,20);
    }
}
