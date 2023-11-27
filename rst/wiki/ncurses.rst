ncurses
=======

ncurses Nedir?
--------------
ncurses, Linux işletim sistemi için bir programlama kütüphanesidir. Bu kütüphane, terminal tabanlı kullanıcı arayüzleri oluşturmak için kullanılır. ncurses, terminal ekranını kontrol etmek, metin tabanlı menüler oluşturmak, renkleri ve stil özelliklerini ayarlamak gibi işlevlere sahiptir.

ncurses, kullanıcıya metin tabanlı bir arayüz sağlar ve terminal penceresinde çeşitli işlemler gerçekleştirmek için kullanılabilir. Örneğin, bir metin düzenleyici, dosya tarayıcısı veya metin tabanlı bir oyun gibi uygulamalar ncurses kullanarak geliştirilebilir.

ncurses Derleme
---------------

cd $HOME
wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.4.tar.gz

tar -xvf ncurses-6.4.tar.gz
cd ncurses-6.4
./configure --prefix=/
#./configure --prefix=/ --with-shared --disable-tic-depends --with-versioned-syms

make
make install DESTDIR=$HOME/rootfs


