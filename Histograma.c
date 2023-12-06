#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define L 10 //256
#define prints 1

int *Histograma_sec(int **imagen, int ren, int col){
    int histograma[L];
    for(size_t i = 0; i < L; i++){
        histograma[i] = 0;
    }
    for(size_t i = 0; i < ren; i++){
        for(size_t j = 0; j < col; j++){
            histograma[imagen[i][j]] += 1;
        }
    }
    for(size_t i = 0; i < L; i++){
        printf("%d: %d\n",i, histograma[i]);
    }
    return histograma;
}
int **RandomImage(int ren, int col){
    // Imagen
    int **imagen = malloc(ren * sizeof(int *));
    
    for(size_t i = 0; i < ren; i++){
        imagen[i] = malloc(col * sizeof(int));
    }
    for(size_t i = 0; i < ren; i++){
        for(size_t j = 0; j < col; j++){
            imagen[i][j] = rand() % L;
        }
    }
    if(prints != 0){
        for(size_t i = 0; i < ren; i++){
            for(size_t j = 0; j < col; j++){
                printf("%d\t",imagen[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return imagen;
}

int main(){
    int ren = 5;
    int col = 5;

    int **ima = RandomImage(ren,col);
    int *his = Histograma_sec(ima,ren,col);
    //TODO: HAcer free
}
// Luego le avanzo