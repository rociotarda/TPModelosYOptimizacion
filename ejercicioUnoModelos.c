#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int prendasEnLavarropa[20];
    int matrix[20][20];
    int tiemposLavado[20];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = 1;
        }
        prendasEnLavarropa[i] = 0; //A todas las prendas las pongo como que todavia no tienen asignadas ningun lavarropas
    }
    char line[1000];
    FILE *laundryFile = fopen("lavanderia.txt", "r");
    while (fgets(line, sizeof(line), laundryFile))
    {
        char caracter;
        int param1 = 0, param2 = 0;
        caracter = fgetc(laundryFile);
        //printf("caracter: %c\n", caracter);
        if (caracter == 'e')
        { //"e": incompatibilidad: formato e n1 n2 "n1" y "n2" son los números de prenda incompatibles entre ellas
            sscanf(line, "%c %d %d", &caracter, &param1, &param2);

            matrix[param1 - 1][param2 - 1] = 0; //escribo un 0 si son incompatibles
            //printf("matrix[param1-1][param2-1]: %d %d %d \n", matrix[param1-1][param2-1],param1,param2);
        }
        if (caracter == 'n')
        { //n n1 c1 "n1" es el número de prenda y "c1" el tiempo de lavado
            sscanf(line, "%c %d %d", &caracter, &param1, &param2);
            //printf("caracter n parametro1: %d y parametro2: %d\n", param1, param2);
            tiemposLavado[param1 - 1] = param2;
        }
    }

    int lavarropasPosibles[20];

    for (int prendaALavar = 0; prendaALavar < 20; prendaALavar++)
    {
        //printf("prendaALavar=:%d \n", prendaALavar);
        for (int i = 0; i < 20; i++)
        {
            lavarropasPosibles[i] = 1; //Pongo en 1 a todos los lavarropas para que esten disponibles
            //printf("lavarropasPosibles[%d]=:%d \n", i,lavarropasPosibles[i]);
        }

        for (int prendaYaLavada = 0; prendaYaLavada < prendaALavar; prendaYaLavada++)
        {
            //printf("prendaYaLavada= %d \n", prendaYaLavada);
            //printf("matriz: %d \n", matrix[prendaYaLavada][prendaALavar]);
            if (matrix[prendaYaLavada][prendaALavar] == 0)
            {
                lavarropasPosibles[(prendasEnLavarropa[prendaYaLavada]) - 1] = 0;
                //printf("lavarropasPosibles[%d]=:%d \n",prendasEnLavarropa[prendaYaLavada], lavarropasPosibles[prendasEnLavarropa[prendaYaLavada]]);
            }
        }
        int k = 0;
        int lavadoraElegida = 0;
        //printf("lavadoraElegida:%d y k:%d \n", lavadoraElegida,k);
        while (lavadoraElegida == 0)
        {
            //printf("K: %d \n",k);
            //printf("lavarropasPosibles[%d]:%d \n",k, lavarropasPosibles[k]);
            for(int lavarropas = 0; lavarropas < 20; )
            lavadoraElegida = lavarropasPosibles[k];
            //printf("lavadoraElegida:%d  \n", lavadoraElegida);
            k = k + 1;
            //printf(" k:%d \n",k);
        }
        //printf("K: %d \n",k);
        prendasEnLavarropa[prendaALavar] = k;
        //printf("prendasEnLavarropa[%d] =%d y k:%d \n", prendaALavar,prendasEnLavarropa[prendaALavar] ,k);
    }

    FILE *out_file = fopen("prendasYLavados.txt", "w"); // write only

    // test for files not existing.
    if (out_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include
    }

    // write to file vs write to screen
    for (int i = 0; i < 20; i++)
    {
        //printf("Prenda: %d en lavarropas: %d \n", i+1, prendasEnLavarropa[i]);
        fprintf(out_file, "%d %d\n", i + 1, prendasEnLavarropa[i]); // write to file
    }

    return 0;
}