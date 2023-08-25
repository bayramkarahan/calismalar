#include <stdio.h>
#include <curl/curl.h>
//sudo apt-get install libcurl4-gnutls-dev
//sudo apt-get install libcurl4-openssl-dev

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://bayramkarahan.blogspot.com/2018/12/paylasim-anlk.html");

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
