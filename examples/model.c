#define BUN2D_IMPLEMENTATION 
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <bun2d.h>

int main()
{
    bun2dInit(1, 200, 200, 800, 800);
    char* filePath = "bun.png";
    
    struct stat sb;
    stat(filePath, &sb);

    Voxel p = {255,10,100,255,0,0};
    Voxel i = {255,10,100,255,1,1};

    Voxel data[2];

    data[0] = p;
    data[1] = i;

    Model* fooInternal = bun2dMakeModel(data, 2);
    Model* fooCsv = bun2dLoadModel("bun.csv");
    Model* fooPng = bun2dLoadPngModel(filePath);
    bun2dDrawModel(fooPng, 0,0 ,1);
    while (bun2dTick())
    {
        bun2dClear();
        struct stat sb_new;
        stat(filePath, &sb_new);
        if(sb_new.st_mtime != sb.st_mtime){
            printf("Modified! %ld", sb.st_mtime);
            sb.st_mtime = sb_new.st_mtime;
            fooPng = bun2dLoadPngModel(filePath);
        }
        bun2dDrawModel(fooInternal, 40,20,1);
        bun2dDrawModel(fooCsv, 0,10,1);
        bun2dDrawModel(fooPng, 10,10,1);
    }
}

