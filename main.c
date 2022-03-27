#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "funciones.h"
typedef struct cancion{ //Estructura de las canciones del archivo con su: nombre,artista,genero,año y a la lista que pertenece.
    char nombre[31];
    char artista[31];
    char genero[31];
    int anyo;
    listaC* lista;
}cancion;

typedef struct listaC{ //Estructura de las listas de canciones indica: Cantidad de canciones, las canciones , y nombre de la lista (segun archivo).
    size_t cantidadCan;
    List* canciones;
    char NomLista[31];
}listaC;

typedef struct listaGlobal{ //Estructura de la lista "Global" que almacena todas las canciones del archivo.
    size_t CantCanciones;
    List* canciones;
    List* listasExistentes;
}listaGlobal;

int main()
{
    printf("Spotify Clone\n\n");
    char str[100];
    char *ptrStr;
    int seleccionado;
    int selec2;
    void LimpiarPantalla(){
        printf("\n\n\n\n\n\n\n\n\n\n");
    }

    listaGlobal *L_Global = (listaGlobal *) malloc (sizeof(listaGlobal));
    L_Global = importar("Canciones.csv");
    printf("fin importacion\n\n");

    while(1)
    {
        printf("1. Buscar\n"); //nombre, artistra y genero
        printf("2. Agregar\n");// solo cancion
        printf("3. Eliminar\n");// solo cancion
        printf("4. Mostrar\n");//cancion, nombres, lista de reproduccion
        printf("5. Salir\n\n");
        printf("Ingresa lo que deseas hacer:  ");
        scanf("%d",&seleccionado);

        switch(seleccionado)
        {
            case 1:
                LimpiarPantalla();
                printf("1. Nombre\n");
                printf("2. Artista\n");
                printf("3. Genero\n");
                printf("Ingresa parametro de busqueda:  ");
                scanf("%d",&selec2);
                switch(selec2){
                    case 1:
                    LimpiarPantalla();
                    printf("Ingrese Nombre: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                    ////
                    case 2:
                    LimpiarPantalla();
                     printf("Ingrese Artista: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                    ////
                    case 3:
                    LimpiarPantalla();
                    printf("Ingrese Genero: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                }

                break;

            case 2:
                LimpiarPantalla();
                printf("Esta funcion no esta disponible:\n");

                break;
            case 3:
                LimpiarPantalla();
                printf("Esta funcion no esta disponible:\n");

                break;
            case 4:
               LimpiarPantalla();
                printf("1. Cancion\n");
                printf("2. Nombres\n");
                printf("3. Lista de reproduccion\n");
                printf("Ingresa parametro para mostrar:  ");
                scanf("%d",&selec2);
                switch(selec2){
                    case 1:
                    LimpiarPantalla();
                    printf("Ingrese Cancion: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                    ////
                    case 2:
                    LimpiarPantalla();
                     printf("Ingrese Nombre: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                    ////
                    case 3:
                    LimpiarPantalla();
                    printf("Ingrese Lista de rep: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                }
                break;
            case 5:
                LimpiarPantalla();
                printf("Saliendo del programa");
                exit(0);
                break;
        }
    }

    return 0;
}
