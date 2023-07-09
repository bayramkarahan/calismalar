#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std; 
  
int main() 
{ 
    //ftok ile benzersiz bir anahtar oluştur:
    key_t key = ftok("shared_memory_file1",70); 
  
    // shmget paylaşılan bellek bölümü için bir tanımlayıcı döndür:
    int shmid = shmget(key,102,0777|IPC_CREAT); 
  
    //bellek bölümünü bağla:
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    cout<<"Veri yaz:"; 
    cin >> str;
  
    printf("Paylaşılan belleğe yazılan veri: %s\n",str); 
      
    //Paylaşılan bellek bölümü ile işimiz bitti.Kendini ilgili bölümden ayırır:
    shmdt(str); 
  
    return 0; 
}
