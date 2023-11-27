Kernel Nedir?
++++++++++++


https://gonullu.pardus.org.tr/kendi-dagitiminizi-olusturmak-bolum-1/
https://gonullu.pardus.org.tr/kendi-dagitiminizi-olusturmak-bolum-2/
https://gonullu.pardus.org.tr/kendi-dagitiminizi-olusturmak-bolum-3/
https://ahmetnumancoskun.medium.com/linux-kernel-derleme-ve-kurulum-2-62b805f33f28
https://ahmetnumancoskun.medium.com/gnu-yaz%C4%B1l%C4%B1mc%C4%B1-5f0eecdc2b85
https://medium.com/@ThyCrow/compiling-the-linux-kernel-and-creating-a-bootable-iso-from-it-6afb8d23ba22
Kernel Derleme
--------------
# Linux çekirdeğinin kaynak kodunu https://kernel.org üzerinden indirin.

wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.2.tar.xz
tar -xvf linux-6.6.2.tar.xz
cd linux-6.6.2
make defconfig
make bzImage

Derleme tamamlandığında Kernel: arch/x86/boot/bzImage is ready (#1) şeklinde bir satır yazmalıdır. Kernelimizin düzgün derlenip derlenmediğini anlamak için aşağıdaki komutu kullanabilirsiniz.

file arch/x86/boot/bzImage 
arch/x86/boot/bzImage: Linux kernel x86 boot executable bzImage, version 6.6.2 (etapadmin@etahta) #1 SMP PREEMPT_DYNAMIC Sat Nov 25 19:53:19 +03 2023, RO-rootFS, swap_dev 0XC, Normal VGA


