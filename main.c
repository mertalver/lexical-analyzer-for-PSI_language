#include <stdio.h>
#include <stdlib.h>
#define sinavSayisi 3

int main()
{
    int i=0;
    double sinavNotu[sinavSayisi],ort,total = 0;

    while (i != sinavSayisi){
        printf("%d sinav notunuzu giriniz: ", i+1);
        scanf("%lf", &sinavNotu[i]);

        if(sinavNotu[i] <= 100 && sinavNotu[i] >= 0) {
            total = total+sinavNotu[i];
            i++;
        }
        else
            printf("Sinav notunuzu yanlis girdiniz.\n");
    }

    ort = total /sinavSayisi;

    if (ort >= 60) {
        printf("Ortalamaniz %.2f - Gectiniz",ort);
    }
    else if (ort>=0) {
        printf("Ortalamaniz %.2f - Kaldiniz",ort);
    }
    else {
        printf("Notlarýnýzý dogru giriniz");
    }

}
