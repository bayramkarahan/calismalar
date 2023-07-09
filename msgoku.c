#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
  
    //mesaj al-kuyruktan mesaj al:
    msgrcv(msgid, &message, sizeof(message), 1, 0);
  
    // display the message
    printf("Gelen Veri: %s \n", message.msg_text);
  
    // mesaj kuyruğunu yok et:
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}
