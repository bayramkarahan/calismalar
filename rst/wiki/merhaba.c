#include<stdio.h>
#include<readline/readline.h>
//gcc -o merhaba merhaba.c $(pkgconf --cflags --libs readline) -lncurses
void main()
{
char* msg=readline("Adını Yaz:");
puts(msg);
puts("hehe");
}
