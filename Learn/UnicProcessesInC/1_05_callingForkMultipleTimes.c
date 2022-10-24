#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int id1 = fork();
    int id2 = fork();
    if(id1==0){
        if(id2==0) {
            printf("we are process y\n");
        } else {
            printf("We are process x\n");
        }
    } else {
        if (id2==0) {
            printf("We are process z\n");
        }else {
            printf("We are the parent process!\n");
        }
    }
    while(wait(NULL)!=-1 || errno != ECHILD){
        printf("Wainted for a child to finish\n");
    }
    return 0;
}
