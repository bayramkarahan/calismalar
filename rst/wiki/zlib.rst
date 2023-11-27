ncurses
=======

zlib Nedir?
--------------

zlib, sıkıştırma ve açma işlemleri için kullanılan bir kütüphanedir. Linux sistemlerinde sıkıştırma ve açma işlemlerini gerçekleştirmek için sıklıkla kullanılır. zlib, verileri sıkıştırarak daha az yer kaplamasını sağlar ve aynı zamanda sıkıştırılmış verileri orijinal haline geri dönüştürmek için kullanılır.

zlib, genellikle dosya sıkıştırma, ağ iletişimi ve veritabanı yönetimi gibi alanlarda kullanılır. Örneğin, bir dosyayı sıkıştırmak ve daha az depolama alanı kullanmak istediğinizde zlib'i kullanabilirsiniz. Ayrıca, ağ üzerinden veri iletişimi yaparken veri boyutunu azaltmak için de zlib kullanabilirsiniz.

Linux sistemlerinde zlib kütüphanesi genellikle C dilinde kullanılır. Aşağıda basit bir örnek verilmiştir:

language-c

#include <stdio.h>
#include <zlib.h>

int main() {
    char source[] = "Bu bir örnek metindir.";
    char compressed[1024];
    char decompressed[1024];
    uLong sourceLen = strlen(source);
    uLong compressedLen = sizeof(compressed);
    uLong decompressedLen = sizeof(decompressed);

    compress((Bytef *)compressed, &compressedLen, (const Bytef *)source, sourceLen);
    uncompress((Bytef *)decompressed, &decompressedLen, (const Bytef *)compressed, compressedLen);

    printf("Orjinal Metin: %s\n", source);
    printf("Sıkıştırılmış Metin: %s\n", compressed);
    printf("Açılmış Metin: %s\n", decompressed);

    return 0;
}

Bu örnekte, compress fonksiyonu ile source metni sıkıştırılır ve compressed dizisine kaydedilir. Ardından, uncompress fonksiyonu ile compressed dizisi açılır ve decompressed dizisine kaydedilir. Sonuç olarak, orijinal metin, sıkıştırılmış metin ve açılmış metin ekrana yazdırılır.

zlib, Linux sistemlerinde sıkıştırma ve açma işlemleri için güvenilir ve yaygın olarak kullanılan bir kütüphanedir.

zlib Derleme
---------------

cd $HOME
wget https://zlib.net/current/zlib.tar.gz

tar -xvf zlib.tar.gz
cd zlib-1.3
#https://www.linuxfromscratch.org/~thomas/multilib/chapter08/zlib.html

./configure --prefix=/

make
make install DESTDIR=$HOME/rootfs


