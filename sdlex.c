#include "SDL2/SDL.h" /* SDL header dosyası. Bütün SDL programları buna ihtiyaç duyar */
#include <stdio.h>

int main() {

    printf("SDL programı başlatılıyor.\n");

if(SDL_WasInit(SDL_INIT_VIDEO)!=0)
    printf("Video alt sistemi yüklü.\n");
else
    printf("Video alt sistemi yüklü değil.\n"); 


    /* SDL programı başlatılıp Video ve Ses sistemleri aktif hale getiriliyor */
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) {
        fprintf(stderr, "SDL programı başlatılamadı: %s.\n", SDL_GetError());
        exit(-1);
    }

    fprintf(stdout, "SDL programı başlatılamadı.\n");

    fprintf(stdout, "SDL programı kapatılıyor.\n");

    /* SDL programı ve bütün alt sistemleri kapatılıyor */
    SDL_Quit();

    fprintf(stdout, "Kapatılıyor....\n");

    exit(0);
}
