#include <stdio.h>
#include <stdlib.h>
void pwn(){
	FILE *fp = fopen("flag","r");
        char flag[100];
        if(fp == NULL){
                printf("File not exist\n");
        }else{
                fgets(flag, 100, fp);
        }
        printf("%s\n",flag);
        fclose(fp);

}

void Func(){
        char buff[32];
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

