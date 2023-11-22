glibc DERLEME
=============
glibc Nedir?
------------
glibc (GNU C Kütüphane) Linux sistemlerinde kullanılan bir C kütüphanesidir. Bu kütüphane, C programlama dilinin temel işlevlerini sağlar ve Linux çekirdeğiyle etkileşimde bulunur.

glibc, birçok standart C işlevini içerir ve bu işlevler, bellek yönetimi, dosya işlemleri, dize işlemleri, ağ işlemleri ve daha fazlası gibi çeşitli görevleri yerine getirmek için kullanılabilir. Bu kütüphane, Linux sistemlerinde yazılım geliştirme sürecini kolaylaştırır ve programcılara güçlü bir araç seti sunar.

glibc, genellikle C programları için kullanılan standart bir kütüphanedir. Bir C programı yazarken, glibc işlevlerini kullanarak bellek yönetimi, dosya işlemleri, dize işlemleri ve diğer işlemleri gerçekleştirebilirsiniz. Örneğin, bir dosyayı açmak ve okumak için fopen ve fread işlevlerini kullanabilirsiniz.

Aşağıda, glibc kullanarak basit bir C programının nasıl yazılacağına dair bir örnek bulunmaktadır:

#include<stdio.h>
void main()
{
puts("Merhaba Dünya");
}

Bu örnekte, ekrana "Merhaba Dünya" yazacaktır.
glibc, Linux sistemlerinde C programlama dilini kullanarak yazılım geliştirmek için önemli bir araçtır. Bu kütüphane, Linux'ta çalışan birçok programın temelini oluşturur ve geliştiricilere güçlü bir platform sunar.

Bu programı Derleyelim.
gcc -o merhaba merhaba.c 

Derlediğimiz merhaba ikili dosyasını aşağıda glibc kütüphanemizi derleyip derlenen kütüphaneler üzerinde çalıştıracağız.

glibc Derleme
-------------

# Ev dizinine geçiyorum.
cd $HOME/

# glibc kaynak kodunu indiriyoruz.

wget https://ftp.gnu.org/gnu/libc/glibc-2.38.tar.gz

# glibc kaynak kodunu açıyoruz.

tar -xvf glibc-2.38.tar.gz

# glibc derlemek için bir derleme dizini oluşturuyoruz.
 
mkdir build-glibc && cd build-glibc

# Derleme ayarları yapılıyor
../glibc-2.38/configure --prefix=/ --disable-werror

# glibc derleyelim.
make 
#hata olursa
make -j2 CFLAGS="-U_FORTIFY_SOURCE -O2 -fno-stack-protector"

glibc Yükleme
-------------
# Ev Dizinindeki rootfs dizinine glibc yükleyelim.

make install DESTDIR=$HOME/rootfs

glibc Test Etme
---------------

gllibc kütüphanemizi **$HOME/rootfs** komununa yükledik. Şimdi bu kütüphanenin çalışıp çalışmadığını test edelim.

Aşağıdaki c kodumuzu derleyelim ve **$HOME/rootfs** konumuna kopyalayalım.

#include<stdio.h>
void main()
{
puts("Merhaba Dünya");
}

# Bu programı Derleyelim.
gcc -o merhaba merhaba.c 

# derlenen selam ikili dosyası $HOME/rootfs/ konumuna kopyalandı.
cp merhaba $HOME/rootfs/merhaba

# **$HOME/rootfs/** konumundaki glibc yüklü konuma **chroot** ile dosyamızı çalıştıralım.
Aşağıdaki gibi bir hata alacağız.

sudo chroot $HOME/rootfs/ /merhaba
chroot: failed to run command ‘/merhaba’: No such file or directory

# üstteki hatanın çözümü sembolik bağ oluşturmak.
cd $HOME/rootfs/
ln -s lib lib64

#selam dosyamızı tekrar chroot ile çalıştıralım. Aşağıda görüldüğü gibi hatasız çalışacaktır.
sudo chroot rootfs /merhaba
Merhaba Dünya



