libreadline Derleme
===================

libreadline, Linux işletim sistemi için geliştirilmiş bir kütüphanedir. Bu kütüphane, kullanıcıların komut satırında girdi almasını ve düzenlemesini sağlar. Bir programcı olarak, libreadline'i kullanarak kullanıcı girdilerini okuyabilir, düzenleyebilir ve işleyebilirsiniz.

Aşağıda, libreadline'i kullanarak basit bir örnek göstereceğim:
Bu örneğin çalışması için;
sudo apt install libreadline-dev paketi sistemde kurulu olması gerekmektedir.

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;

    while ((input = readline("Komut girin: ")) != NULL) {
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        printf("Girilen komut: %s\n", input);
        add_history(input);
        free(input);
    }

    return 0;
}

Bu örnekte, kullanıcıdan komut girmesini istiyoruz ve libreadline'i kullanarak girdiyi okuyoruz. Kullanıcı "exit" komutunu girdiğinde program sonlanır. Ayrıca, kullanıcının daha önce girdiği komutları hatırlamak için add_history fonksiyonunu kullanıyoruz.

libreadline, Linux programlama dünyasında oldukça yaygın olarak kullanılan bir kütüphanedir. Kullanıcı dostu bir komut satırı deneyimi sağlamak için libreadline'i kullanabilirsiniz.

libreadline Derleme
-------------------
cd $HOME
wget https://ftp.gnu.org/pub/gnu/readline/readline-8.2.tar.gz

tar -xvf readline-8.2.tar.gz
cd readline-8.2
./configure --prefix=/ --enable-shared --enable-multibyte
for mfile in $(find "$PWD" -name 'Makefile'); do
    sed -i 's|SHLIB_LIBS =|SHLIB_LIBS = -ltinfo|g' "$mfile"
done
make
make install DESTDIR=$HOME/rootfs

libreadline Test Etme
---------------------

# merhaba.c doayası

#include<stdio.h>
#include<readline/readline.h>
void main()
{
char* msg=readline("Adını Yaz:");
puts(msg);
}

Dosya Derleme
-------------
gcc -o merhaba merhaba.c -lreadline
cp merhaba $HOME/rootfs/merhaba

Test
----
sudo chroot $HOME/rootfs /merhaba
/merhaba: error while loading shared libraries: libreadline.so.8: cannot open shared object file: No such file or directory

# Hata Çözümü
-------------
cd $HOME/rootfs/lib
ln -s libncurses.so.6 libtinfo.so.6

# önceki konuma dönülüyor
cd -

# Tekrar test ediyoruz.
sudo chroot $HOME/rootfs /merhaba
