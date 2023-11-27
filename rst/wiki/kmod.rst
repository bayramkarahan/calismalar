kmod
====

kmod Nedir?
--------------
Linux çekirdeği ile donanım arasındaki haberleşmeyi sağlayan kod parçalarıdır. Bu kod parçalarını kernele eklediğimizde kerneli tekrardan derlememiz gerekmektedir. Her eklenen koddan sonra kernel derleme, kod çıkarttığımzda kernel derlemek ciddi bir iş yükü ve karmaşa yaratacaktır.

Bu sorunların çözümü için modul vardır. moduller kernele istediğimiz kod parpalarını ekleme ya da çıkartma yapabiliyoruz. Bu işlemleri yaparken kenel derleme işlemi yapmamıza gerek yok.

kmod Derleme
------------
#https://www.linuxfromscratch.org/~thomas/multilib/chapter08/kmod.html
cd $HOME
wget https://mirrors.edge.kernel.org/pub/linux/utils/kernel/kmod/kmod-31.tar.xz

tar -xvf kmod-31.tar.xz
cd kmod-31
# skip building gtk doc
touch libkmod/docs/gtk-doc.make

Kmod'u derleme için hazırlayın:
-------------------------------
./configure --prefix=/usr          \
            --sysconfdir=/etc      \
            --with-openssl         \
            --with-xz              \
            --with-zstd            \
            --with-zlib


İsteğe bağlı bağımlılıklar: - ZLIB kütüphanesi - LZMA kütüphanesi -ZSTD kütüphanesi - OPENSSL kütüphanesi (modinfo'da imza yönetimi) 
--with-openssl
Bu seçenek Kmod'un PKCS7 imzalarını işlemesini sağlar. çekirdek modülleri.
--with-xz, --with-zlib, Ve --with-zstd
Bu seçenekler Kmod'un sıkıştırılmış çekirdeği işlemesini sağlar modüller.

Ben aşağıdaki şekilde yapılandıracağım;

./configure --prefix=/ \
        --libdir=/lib/ \
        --bindir=/sbin

# remove xsltproc dependency
   rm -f man/Makefile
   echo -e "all:\ninstall:" > man/Makefile
make
make install DESTDIR=$HOME/rootfs

kmod Araçlarını Oluşturma
-------------------------

for target in depmod insmod modinfo modprobe rmmod; do
  ln -sfv sbin/kmod sbin/$target
done

ln -sfv sbin/kmod bin/lsmod

veya 
Kernele modul yükleme kaldırma için kmod aracı kullanılmaktadır. kmod aracı;

.. code-block:: shell

ln -s sbin/kmod sbin/depmod
ln -s sbin/kmod sbin/insmod
ln -s sbin/kmod sbin/lsmod
ln -s sbin/kmod sbin/modinfo
ln -s sbin/kmod sbin/modprobe
ln -s sbin/kmod sbin/rmmod

şeklinde sembolik bağlarla yeni araçlar oluşturulmuştur.

**lsmod :** yüklü modulleri listeler

**insmod:** tek bir modul yükler

**rmmod:** tek bir modul siler

**modinfo:** modul hakkında bilgi alınır 

**modprobe:** insmod komutunun aynısı fakat daha işlevseldir. module ait bağımlı olduğu modülleride yüklemektedir. modprobe  modülü /lib/modules/ dizini altında aramaktadır.

**depmod:** /lib/modules dizinindeki modüllerin listesini günceller. Fakat başka bir dizinde ise basedir=konum şeklinde belirtmek gerekir. konum dizininde /lib/modules/** şeklinde kalsörler olmalıdır.

kmod Test Edilmesi
++++++++++++++++++


modul.c dosyamız
----------------

.. code-block:: shell

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
MODULE_DESCRIPTION("Hello World examples");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bayram");
static int __init hello_init(void)
{
printk(KERN_INFO "Hello world!\n");
return 0;
}
static void __exit hello_cleanup(void)
{
printk(KERN_INFO "remove module.\n");
}
module_init(hello_init);
module_exit(hello_cleanup);


Makefile dosyamız
-----------------

.. code-block:: shell

obj-m+=my_module.o
all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

modülün derlenmesi ve eklenip kaldırılması
------------------------------------------

.. code-block:: shell

make

insmod my_modul.ko // modül kernele eklendi.

lsmod | grep my_modul //modül yüklendi mi kontrol ediliyor.

rmmod my_modul // modül kernelden çıkartılıyor.

Not:
---
dmesg ile log kısmında eklendiğinde Hello Word yazısını ve  kaldırıldığında modul ismini görebiliriz.

