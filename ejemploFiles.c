#include <stdio.h>

int main()
{
    char *pais[5];
    int noCasos[5];
    unsigned char nivel[5];

    pais[0] = "Mexico";
    noCasos[0] = 100;
    nivel[0] = 5;

    pais[1] = "España";
    noCasos[1] = 21312;
    nivel[1] = 240;

    pais[2] = "Italia";
    noCasos[2] = 294;
    nivel[2] = 234;

    pais[3] = "EUA";
    noCasos[3] = 12394;
    nivel[3] = 76;

    pais[4] = "Alemania";
    noCasos[4] = 123;
    nivel[4] = 89;

    // Making CSV file
    // FILE *fp = fopen("output/file.csv", "w+"); // <- Cuidado si no existe la carpate
    FILE *fp = fopen("file.csv", "w+");

    // Header
    fprintf(fp, "%s,%s,%s \n", "Pais", "NoCasos", "Nivel");

    // Data
    for (int i = 0; i < 5; i++)
        fprintf(fp, "%s,%i,%u\n", pais[i], noCasos[i], nivel[i]);
    
    // DONT FORGET TO CLOSE THE FILEEEEE
    fclose(fp);
}