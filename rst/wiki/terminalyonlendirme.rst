
# Terminal Yönlendirmesi

**İlk terminalde :**

 $ tty
 /dev/pts/0
 $ <no need to run any command here, just see the output>

**İkinci terminalde :**

$ ls > /dev/pts/0

Artık çıktıyı ilk terminalde alıyorsunuz

**Başka Yol:**
$ tty
/dev/pts/0

$ tty
/dev/pts/1

Bu TTY'leri varsayarak, birincinin stdout'unu ikinciye yönlendirmek için bunu ilk terminalde çalıştırın:

exec 1>/dev/pts/1

    Not: Artık her komut çıktısı pts/1'de gösterilecektir.

pts/0'ın varsayılan davranış stdout'unu geri yüklemek için:

exec 1>/dev/pts/0

**Gerçek Zamanlı Terminal Yansıtma**

terminal 1'de:

$ tty 
/dev/pts/0

terminal 2'de:

$ tty
/dev/pts/1

**terminal 2'de:**

$ exec &> >(tee >(cat >&/dev/pts/0))
ls 

Çıktı, siz yazarken bile her iki terminalde de gerçek zamanlı olarak gösterilecektir. 