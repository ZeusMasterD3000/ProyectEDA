#include <stdio.h>
// argument count
// argument value 

int main(int argc, char *argv[])
{
    printf("\n");

    for (int i = 0; i < argc; i++)
        printf("%d -> %s \n", i, argv[i]);

    if (argc < 2)
    {
        printf("ERROR: Falta el segundo parametros !!!\n\n");
        return -1;
    }

    char *secondParam = argv[1];
    printf("El segundo paramerto es: %s \n\n", secondParam);

    return 0;
}