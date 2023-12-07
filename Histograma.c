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
    for(int i = 1; i < L; i++){
        D_Acumulada[i] = D_Acumulada[i - 1] + histo_og[i];
    }
    return D_Acumulada;
}

int *histograma_sec(unsigned char *pixeles, int ancho, int alto, int canal){
    int *histograma = malloc(L * sizeof(int));

    // parallel for
    for(int i = 0; i < L; i++){
        histograma[i] = 0;
    }

    // Iterar sobre todos los píxeles de la imagen
    for(int i = 0; i < ancho*alto*canal; i += canal){
        histograma[pixeles[i]] += 1;
    }
    return histograma;
}

unsigned char *funcion_eq_sec(unsigned char *pixeles, int *cdf, int ancho, int alto, int canal){
    int *funcion_eq = malloc(L * sizeof(int));
    int cdf_min;

    for(int i = 0; i < L; i++){
        if(cdf[i] != 0){
            cdf_min = cdf[i];
            break;
        }
    }    
    int tam = ancho * alto;

    for(int i = 0; i < L; i++){
        funcion_eq[i] = round(((cdf[i] - cdf_min) / ((double)(ancho * alto)) * 254)) + 1;
    }

    unsigned char *new_pixeles = malloc(ancho * alto * sizeof(unsigned char));

    for(int i = 0; i < ancho*alto; i++){
        new_pixeles[i] = funcion_eq[pixeles[i * canal]];
    }
    return new_pixeles;
}

int main(int argc, char *argv[]){

    char *dicIma = "nature.jpeg";
    int ancho, alto, canales;
    unsigned char *pixeles = stbi_load(dicIma, &ancho, &alto, &canales, 0);

    if(pixeles == NULL){
        printf("La imagen no pudo ser cargada correctamente %s", dicIma);
        exit(1);
    }else{
        printf("\nImagen cargada correctamente\n\n");
    }

    int *histo_original = histograma_sec(pixeles,ancho,alto,canales);
    int *f_acumulada = FDA(histo_original);

    unsigned char *pixeles_new = funcion_eq_sec(pixeles,f_acumulada,ancho,alto,canales);
    int *histo_modificado = histograma_sec(pixeles_new,ancho,alto,1);

    stbi_write_jpg("New_1.jpg", ancho, alto, 1, pixeles_new, 100);
    stbi_image_free(pixeles_new);

    
}

