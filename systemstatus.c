#include <stdio.h>
#include <ctype.h>
 #include <cstdlib>
int main(void)
{

int a;
a=system("mkdir bayram");
if(a==0){
printf("İşlem hatasız oldu: %i\n",a);
}else{
printf("işlem sırasında hata oldu: %i\n", a);
}
return 0;
}

