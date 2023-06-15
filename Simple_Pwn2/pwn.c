#include <stdio.h>
#include <stdlib.h>
void backdoor(){
	system("/bin/sh");
}

void Func(){
        char buff[52];
        printf("What's your name?\n");
	gets(buff);
        printf("Hello %s\n", buff);
}

int main(){
        setvbuf(stdin, NULL, _IONBF, 0);
        setvbuf(stdout, NULL, _IONBF, 0);
        int x;
        Func();
        return 0;
}

