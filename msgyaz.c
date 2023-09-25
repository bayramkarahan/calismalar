#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 20 //mesaj uzunluğu

// Mesaj kuyruğu yapısı
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;
  
    // benzersiz bir key oluştur:
    key = ftok("prog_file", 44);
  
    //bir mesaj kuyruğu oluştur ve tanımlayıcısını döndür.
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
  
    printf("Veri yaz: ");
    fgets(message.msg_text,MAX,stdin);
  
    //mesaj gönder-mesaj kuyruğuna mesaj gönder:
    msgsnd(msgid, &message, sizeof(message), 0);
  
    // gönderilen mesajı ekrana yazdır:
    printf("Gönderilen veri : %s \n", message.msg_text);
  
    return 0;
}
