#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    char* filePath = "farm-poc.c";
    
    struct stat sb;
    stat(filePath, &sb);

    while(1){
        sleep(1);
        struct stat sb_new;
        stat(filePath, &sb_new);
        if(sb_new.st_mtime != sb.st_mtime){
            printf("Modified! %ld", sb.st_mtime);
            sb.st_mtime = sb_new.st_mtime;
        }
    }
}