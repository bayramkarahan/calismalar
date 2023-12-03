Live Boot
=========

SquashFS
++++++++

SquashFS Nedir?
---------------

SquashFS, Linux işletim sistemlerinde sıkıştırılmış bir dosya sistemidir. Bu dosya sistemi, sıkıştırma algoritması kullanarak dosyaları sıkıştırır ve ardından salt okunur bir dosya sistemine dönüştürür. SquashFS, özellikle gömülü sistemlerde ve Linux dağıtımlarında kullanılan bir dosya sistemidir.

SquashFS Oluşturma
------------------

#mksquashfs input_source output/filesystem.squashfs -comp xz -wildcards 
mksquashfs initrd $HOME/distro/filesystem.squashfs -comp xz -wildcards


Cdrom Erişimi
+++++++++++++

/dev/sr0, Linux işletim sistemlerinde bir CD veya DVD sürücüsünü temsil eden bir aygıt dosyasıdır. Bu dosya, CD veya DVD sürücüsünün fiziksel cihazını temsil eder ve kullanıcıların bu sürücüye erişmesini sağlar.

/dev/sr0 dosyası, Linux'un aygıt dosyası sistemi olan /dev dizininde bulunur. Bu dosya, Linux çekirdeği tarafından otomatik olarak oluşturulur ve sürücüye bağlı olarak farklı bir isim alabilir. Örneğin, ikinci bir CD veya DVD sürücüsü /dev/sr1 olarak adlandırılabilir.

Bu aygıt dosyası, kullanıcıların CD veya DVD'leri okumasına veya yazmasına olanak tanır. Örneğin, bir CD'yi okumak için aşağıdaki gibi bir komut kullanabilirsiniz:

$ cat /dev/sr0

Cdrom Bağlama
-------------

mkdir cdrom
mount /dev/sr0 /cdrom

Bu işlem sonucunda cdrom bağlanmış olacaktır. iso dosyamızın içerisine erişebiliriz.

squashfs Dosyasını Bulma
--------------------------

Genellikle isoların içine squashfs dosyası oluşturlur. Bu sayede live yükleme yapılabilir. 
Örneğin /live/filesystem.squashfs benim imajlarımda böyle konumlandırıyorum.

squashfs Bağlama
----------------

squashfs dosyasını bağlamadan önce loop modülünün yüklü olması gerekmektedir. eğer yüklemediyseniz

modprobe loop #loop modülü yüklenir.

mkdir canli
mount -t squashfs -o loop cdrom/live/filesystem.squashfs /canli

squashfs Sistemine Geçiş
++++++++++++++++++++++++

Yukarıdaki adımlarda squashfs doayamızı /canli adında dizine bağlamış olduk. Bu aşamadan sonra sistemimizin bir kopyası olan squashfs canlıdan erişebilir veya sistemi buradan başlatabiliriz.

squashfs dosya sistemimize bağlanmak için;

chroot canli /bin/bash

Buişlemin yerine exec komutuyla bağlanırsak sistemimiz id "1" değeriyle çalıştıracaktır. 
Eğer sistemin bu dosya sistemiyle açılmasını istiyorsak exec ile çalıştırıp id=1 olmasına dikkat etmeliyiz.


