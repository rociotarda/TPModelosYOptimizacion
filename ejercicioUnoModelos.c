#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
const int sizeTxt = 385;

int main(int argc, char *argv[])
{
    int prendasEnLavarropa[sizeTxt];
    int matrix[sizeTxt][sizeTxt];
    int tiemposLavadoPrenda[sizeTxt];
    int tiemposLavadoLavarropa[sizeTxt];
    int cantidadPrendasEnLavarropas[sizeTxt];

    int tiempoMaxDeLavado = 0;
    for (int i = sizeTxt; i > 0; i--)
    {
        for (int j = 0; j < sizeTxt; j++)
        {
            matrix[i][j] = 1;
        }
        prendasEnLavarropa[i] = 0;     //A todas las prendas las pongo como que todavia no tienen asignadas ningun lavarropas
        tiemposLavadoLavarropa[i] = 0; //A todos los lavarropas los pongo como que su tiempo de lavado es cero
        cantidadPrendasEnLavarropas[i] = 0;
    }
    char line[1000];
    FILE *laundryFile = fopen("lavanderia2.txt", "r");
    while (fgets(line, sizeof(line), laundryFile))
    {
        char caracter;
        int param1 = 0, param2 = 0;
        caracter = fgetc(laundryFile);
        if (caracter == 'e')
        { //"e": incompatibilidad: formato e n1 n2 "n1" y "n2" son los números de prenda incompatibles entre ellas
            sscanf(line, "%c %d %d", &caracter, &param1, &param2);

            matrix[param1 - 1][param2 - 1] = 0; //escribo un 0 si son incompatibles
            matrix[param2 - 1][param1 - 1] = 0; //escribo un 0 si son incompatibles

        }
        if (caracter == 'n')
        { //n n1 c1 "n1" es el número de prenda y "c1" el tiempo de lavado
            sscanf(line, "%c %d %d", &caracter, &param1, &param2);
            int tiempo = param2;
            if(tiempoMaxDeLavado < tiempo){
                tiempoMaxDeLavado = tiempo;
            }
            tiemposLavadoPrenda[param1 - 1] = tiempo;
            //printf("La prenda: %d tiene tiempo %d \n", param1-1, tiempo);
            
        }
    }
     for(tiempoMaxDeLavado = 20; tiempoMaxDeLavado >= 0; tiempoMaxDeLavado-=1){
        printf("tiempoMax: %d \n", tiempoMaxDeLavado);

        int lavarropasPosibles[sizeTxt];
        for(int prendaALavar = 0; prendaALavar < sizeTxt; prendaALavar++){
            if(prendasEnLavarropa[prendaALavar] == 0 && tiemposLavadoPrenda[prendaALavar] >= (tiempoMaxDeLavado)){
                for (int i = 0; i < sizeTxt; i++)
                {
                    lavarropasPosibles[i] = 1; //Pongo en 1 a todos los lavarropas para que esten disponibles
                }
                for (int i = 0; i < sizeTxt; i++)
                {
                    if (matrix[i][prendaALavar] == 0)
                    {
                        lavarropasPosibles[(prendasEnLavarropa[i]) - 1] = 0;
                    }
                }
                int k = 0;
                int lavadoraElegida = 0;
                while (lavadoraElegida == 0)
                {

                    lavadoraElegida = lavarropasPosibles[k];
                    k = k + 1;
                }
                prendasEnLavarropa[prendaALavar] = k;
                if(tiemposLavadoLavarropa[k-1] < tiemposLavadoPrenda[prendaALavar]){
                    //Debo sumarle el tiempo extra que le costara lavar esta prenda
                    tiemposLavadoLavarropa[k-1] += (tiemposLavadoPrenda[prendaALavar] - tiemposLavadoLavarropa[k-1]);
                }
            }
        }
    }
    int sumatoriaTiempos = 0;
    for(int i = 0; i < sizeTxt; i ++){
        sumatoriaTiempos += tiemposLavadoLavarropa[i];
    }

    FILE *out_file = fopen("prendasYLavados.txt", "w"); // write only

    // test for files not existing.
    if (out_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include
    }

    // write to file
    for (int i = 0; i < sizeTxt; i++)
    {
        printf("Prenda: %d en lavarropas: %d \n", i + 1, prendasEnLavarropa[i]);
        printf("Tiempo de lavarropas %d\n", sumatoriaTiempos);
        fprintf(out_file, "%d %d\n", i + 1, prendasEnLavarropa[i]); // write to file

    }

    return 0;
}

int solucion1(){

/*

    int lavarropasPosibles[sizeTxt];

    for (int prendaALavar = 0; prendaALavar < sizeTxt; prendaALavar++)
    {
        for (int i = 0; i < sizeTxt; i++)
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
        
        int k = 0;
        int lavadoraElegida = 0;
        while (lavadoraElegida == 0)
        {

            lavadoraElegida = lavarropasPosibles[k];
            k = k + 1;
        }
        prendasEnLavarropa[prendaALavar] = k;
        

        int tiempoMaximoDeLavado = 0;
        int lavarropasPosibleDeTiempoMaximo = -1;
        int j;
        for ( j = 0; j < sizeTxt; j++)
        {
            if (lavarropasPosibles[j] == 1)
            {
                if (tiemposLavadoLavarropa[j] >= tiemposLavadoPrenda[prendaALavar])
                {
                    //El tiempo de lavado de la prenda es menor o igual que el del lavarropas
                    // No le cuesta tiempo extra al lavarropas
                    lavarropasPosibleDeTiempoMaximo = j;
                    break;
                }
                else
                {
                    if (tiempoMaximoDeLavado < tiemposLavadoPrenda[prendaALavar])
                    {
                        tiempoMaximoDeLavado = tiemposLavadoPrenda[prendaALavar];
                        lavarropasPosibleDeTiempoMaximo = j;
                    }
                }
            }
        }
        prendasEnLavarropa[prendaALavar] = lavarropasPosibleDeTiempoMaximo + 1;
        if(tiemposLavadoLavarropa[lavarropasPosibleDeTiempoMaximo] < tiemposLavadoPrenda[prendaALavar]){
            //Debo sumarle el tiempo extra que le costara lavar esta prenda
            tiemposLavadoLavarropa[lavarropasPosibleDeTiempoMaximo] += (tiemposLavadoPrenda[prendaALavar] - tiemposLavadoLavarropa[lavarropasPosibleDeTiempoMaximo]);
        }

    }

*/

}