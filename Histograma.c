#include <stdio.h>
#include<math.h>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

#define L 256

int *FDA(int *histo_og){
    int *D_Acumulada = malloc(L * sizeof(int));

    D_Acumulada[0] = histo_og[0];
    for(size_t i = 1; i < L; i++){
        D_Acumulada[i] = D_Acumulada[i - 1] + histo_og[i];
    }

    return D_Acumulada;
}

int *histograma_sec(unsigned char *pixeles, int ancho, int alto, int canal){
    int *histograma = malloc(L * sizeof(int));

    // parallel for
    for(size_t i = 0; i < L; i++){
        histograma[i] = 0;
    }

    int i = 0;
    while (i < ancho*alto*canal){
        histograma[pixeles[i]] += 1;
        i += canal;
    }

    return histograma;
}

unsigned char *funcion_eq_sec(unsigned char *pixeles, int *f_acu, int ancho, int alto, int canal){
    int *funcion_eq = malloc(L * sizeof(int));

    int cdf_min = f_acu[0];
    int tam = ancho * alto;

    for(size_t i = 0; i < L; i++){
        int cdf = f_acu[i];
        funcion_eq[i] = round(((cdf - cdf_min) / (tam - cdf_min)) * 255);
    }

    unsigned char *new_pixeles = malloc(ancho * alto * sizeof(unsigned char));

    for(size_t i = 0; i < ancho*alto; i++){
        new_pixeles[i] = funcion_eq[pixeles[i * canal]];
    }

    return new_pixeles;
}

int main(int argc, char *argv[]){

    char *dicIma = "Imagenes_Gris/imaColor1.jpg";
    int ancho, alto, canales;
    unsigned char *pixeles = stbi_load(dicIma, &ancho, &alto, &canales, 0);

    if(pixeles == NULL){
        printf("La imagen no pudo ser cargada correctamente %s", dicIma);
        exit(1);
    }else{
        printf("Imagen cargada correctamente");
    }

    int *histo_original = histograma_sec(pixeles,ancho,alto,canales);
    int *f_acumulada = FDA(histo_original);

    unsigned char *pixeles_new = funcion_eq_sec(pixeles,f_acumulada,ancho,alto,canales);

    stbi_write_jpg("New.jpg", ancho, alto, 3, pixeles_new, 90);
    stbi_image_free(pixeles_new);
}

