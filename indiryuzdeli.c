#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>

int progressCallback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    // İndirme yüzdesini hesapla
    double progress = (double)dlnow / (double)dltotal * 100.0;
    
    // İndirme yüzdesini ekrana yazdır
   //printf("İndirme Yüzdesi: %i\r", progress);
    
    return 0;
}

int main()
{
CURL* curl = curl_easy_init();

// İlerleme işlevini ayarla
curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
//curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);


// İndirilecek dosyanın URL'sini belirtin
curl_easy_setopt(curl, CURLOPT_URL, "https://download.onlyoffice.com/install/desktop/editors/linux/onlyoffice-desktopeditors_amd64.deb");

// İndirme işlemini başlat
CURLcode res = curl_easy_perform(curl);

// İndirme işlemi başarılıysa
if (res == CURLE_OK) {
    printf("Dosya indirme tamamlandı.\n");
}

// curl kolay tutamacını temizle
curl_easy_cleanup(curl);

return 0;
}
