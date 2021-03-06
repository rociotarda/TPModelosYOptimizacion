#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int prendasEnLavarropa[20];
    int tiemposLavarropas[20];
    int matrix[20][20];
    int tiemposLavado[20];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = 1;
        }
        tiemposLavarropas[i] = 0; // Inicio el tiempo maximo de lavarropas en 0
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
        }
        if (caracter == 'n')
        { //n n1 c1 "n1" es el número de prenda y "c1" el tiempo de lavado
            sscanf(line, "%c %d %d", &caracter, &param1, &param2);
            tiemposLavado[param1 - 1] = param2;
        }
    }

    int lavarropasPosibles[20];

    for (int prendaALavar = 0; prendaALavar < 20; prendaALavar++)
    {
        for (int i = 0; i < 20; i++)
        {
            lavarropasPosibles[i] = 1; //Pongo en 1 a todos los lavarropas para que esten disponibles
        }

        for (int prendaYaLavada = 0; prendaYaLavada < prendaALavar; prendaYaLavada++)
        {
            if (matrix[prendaYaLavada][prendaALavar] == 0)
            {
                lavarropasPosibles[(prendasEnLavarropa[prendaYaLavada]) - 1] = 0;
            }
        }

        int lavadoraElegida = 0;
        int lavadoraPosibleBackUp = 0;
        for(int lavadoraAEvaluar = 0; lavadoraAEvaluar < 20 ; lavadoraAEvaluar++){
            if(lavarropasPosibles[lavadoraAEvaluar] == 1){//es una lavadora posible
                lavadoraPosibleBackUp = lavadoraAEvaluar;
                if(tiemposLavarropas[prendaALavar] < tiemposLavarropas[lavadoraAEvaluar] || tiemposLavarropas[lavadoraAEvaluar] == 0){
                    lavadoraElegida = lavadoraAEvaluar;
                    if(tiemposLavarropas[lavadoraAEvaluar] == 0){
                        tiemposLavarropas[lavadoraAEvaluar]= tiemposLavarropas[prendaALavar];
                    }
                }

            }

        }
        if(lavadoraElegida == 0){
            lavadoraElegida = lavadoraPosibleBackUp;
            tiemposLavarropas[lavadoraPosibleBackUp]= tiemposLavarropas[prendaALavar];
        }
        prendasEnLavarropa[prendaALavar] = lavadoraElegida +1;
    }

    FILE *out_file = fopen("prendasYLavados.txt", "w"); // write only

    // test for files not existing.
    if (out_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); 
    }

    // write to file 
    for (int i = 0; i < 20; i++)
    {
        fprintf(out_file, "%d %d\n", i + 1, prendasEnLavarropa[i]); // write to file
    }

    return 0;
}