#include "curl/curl.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<iostream>
#include <curl/curl.h>
static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
    return written;
} /* write_data */

/*int progressCallback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    // İndirme yüzdesini hesapla
    double progress = (double)dlnow / (double)dltotal * 100.0;
     // İndirme yüzdesini ekrana yazdır
   
    // İndirme yüzdesini ekrana yazdır
   // printf("İndirme Yüzdesi: %.2f%%\n", progress);
     printf("İndirme Yüzdesi: %i %i %i %i %.2f%\n",dlnow,dltotal,ultotal ,ulnow,progress);
 
    return 0;
}*/
int progressCallback(void* clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
int progress = dlnow / dltotal*100;
int deger=(int)progress;
    // İlerleme bilgilerini burada işleyebilirsiniz
    //std::cout << "İndirilen: " << dlnow << " / " << dltotal<<"--"<<ultotal<<"--"<<ulnow << std::endl;
    printf("indir:%i\r", progress);
    return 0;
}

bool DownloadFile() {
    bool retval = false;
   // static const char FileURL[] ="https://github.com/bayramkarahan/okularpdfreaderplugin/raw/master/okularpdfreader.deb";
     static const char FileURL[] ="https://download.onlyoffice.com/install/desktop/editors/linux/onlyoffice-desktopeditors_amd64.deb";
 
    static char TargetCURL[] = "test.deb";

    // Download the file using curl library into DownloadCURL folder
    if(CURL* curl = curl_easy_init()) {
        if(FILE* fp = fopen(TargetCURL, "wb")) {
            curl_easy_setopt(curl, CURLOPT_URL, FileURL);
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
            curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L); // corp. proxies etc.


// İlerleme işlevini ayarla
curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            /* Perform the request, res will get the return code */
            CURLcode res = curl_easy_perform(curl);
            if(!res) retval = true;

            fclose(fp);
        }
        curl_easy_cleanup(curl);
    } /* if (auto curl = curl_easy_init ()) */

    return retval;

} /* Download */

int main() {
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if(res) return 1;
    DownloadFile();
    curl_global_cleanup();
}
