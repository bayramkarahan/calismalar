glibc DERLEME
=============

# Making a folder to hold source code

cd $HOME/Downloads
mkdir glibc-build
cd glibc-build

# Downloading glibc
wget https://ftp.gnu.org/gnu/libc/glibc-2.38.tar.gz

# Extracting glibc
tar -xvf glibc-2.38.tar.gz

# Creating folder to hold generate config files
mkdir configs_glibc && cd configs_glibc 

# Run configure script
../glibc-2.27/configure --prefix=$HOME/Downloads/glibc-build/configs_glibc --disable-werror

#../glibc/configure --enable-kernel=4.4 --disable-shared --enable-static --enable-static-nss --prefix=/usr

For the compilation and installation, you continue inside the configs_glibc and run:

# Compiling
make 
#hata olursa
make -j2 CFLAGS="-U_FORTIFY_SOURCE -O2 -fno-stack-protector"
# Installing
make install

