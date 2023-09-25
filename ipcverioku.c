#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std;int main() 
{ 
 //ftok ile benzersiz bir anahtar oluştur:
 key_t key = ftok("shared_memory_file",60);// shmget paylaşılan bellek bölümü için bir tanımlayıcı döndür:
 int shmid = shmget(key,102,0666|IPC_CREAT);//bellek bölümünü bağla:
 char *str = (char*) shmat(shmid,(void*)0,0);printf("Bellekten veri oku: %s\n",str); 
 
 //Paylaşılan bellek bölümü ile işimiz bitti.Kendini ilgili bölümden ayırır:
 shmdt(str); 
 
 //Paylaşılan bellek bölümünü yok et:
 shmctl(shmid,IPC_RMID,NULL); 
 
 return 0; 
}
