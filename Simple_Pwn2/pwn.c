#include <stdio.h>
#include <stdlib.h>
void pwn(){
	printf("nothing here hahaha\n");
}

void Func(){
        char buff[32];
        printf("What's your name?\n");
	gets(buff);
        printf("Hello %s\n", buff);
}

int main(){
        int x;
        Func();
        return 0;
}

