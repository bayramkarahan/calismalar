Bash
====

Bash Nedir?
-----------
Bash, "Bourne Again SHell" kelimelerinin kısaltmasıdır ve Linux ve diğer Unix tabanlı işletim sistemlerinde kullanılan bir kabuk (shell) programıdır. Kabuk, kullanıcının işletim sistemine komutlar vermesini ve bu komutların çalıştırılmasını sağlayan bir arayüzdür.

Bash, diğer kabuk programlarına göre daha gelişmiş bir dildir ve birçok özelliği içerir. Örneğin, döngüler, koşullu ifadeler, değişkenler ve fonksiyonlar gibi programlama yapılarını destekler. Bu sayede, kullanıcılar karmaşık işlemleri otomatikleştirebilir ve daha verimli bir şekilde çalışabilir.

bash Derleme
------------

cd $HOME
wget https://ftp.gnu.org/gnu/bash/bash-5.2.21.tar.gz

tar -xvf bash-5.2.21.tar.gz
cd bash-5.2.21
configure --prefix=/
make
make install DESTDIR=$HOME/rootfs


