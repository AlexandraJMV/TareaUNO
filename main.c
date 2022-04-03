#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "funciones.h"

void LimpiarPantalla(){
    printf("\n\n\n\n\n\n\n\n\n\n");
}

int main()
{
    char str[100];
    char *ptrStr;
    int seleccionado;
    int selec2;

    listaGlobal *L_Global;

    while(1)
    {
        char hola[100];
        system("cls");
        printf("Spotify Clone\n\n");
        printf("1. Buscar\n"); //nombre, artistra y genero
        printf("2. Agregar\n");// solo cancion
        printf("3. Eliminar\n");// solo cancion
        printf("4. Mostrar\n");//cancion, nombres, lista de reproduccion
        printf("5. Importar\n");
        printf("6. Exportar\n");
        printf("7. Salir\n\n");

        printf("Ingresa lo que deseas hacer:  ");
        scanf("%d",&seleccionado);
        getchar();

        switch(seleccionado)
        {
            case 1:
                system("cls");
                printf("1. Nombre\n");
                printf("2. Artista\n");
                printf("3. Genero\n");
                printf("Ingresa parametro de busqueda:  ");
                scanf("%d",&selec2);
                getchar();
                switch(selec2){
                    case 1:
                    system("cls");
                    printf("Ingrese nombre: ");
                    scanf("%[^\n]", hola);
                    getchar();
                    Buscar_nom (hola, L_Global);
                    break;
                    ////
                    case 2:
                    system("cls");
                    printf("Ingrese artista: ");
                    scanf("%[^\n]", hola);
                    getchar();
                    Buscar_nom (hola, L_Global);
                    break;
                    ////
                    case 3:
                    system("cls");
                    printf("Ingrese Genero: ");
                    scanf("%s",hola);
                    getchar();
                    Buscar_gen (hola, L_Global);
                    break;
                }
                break;

            case 2:
                leer_agregar_main(L_Global);
                break;

            case 3:
                elim_main_ver(L_Global);
                break;

            case 4:
                system("cls");
                printf("1. Cancion\n");
                printf("2. Listas de reproduccion\n");
                printf("3. Canciones en una lista de reproduccion\n\n");
                printf("Ingresa parametro para mostrar:  ");
                scanf("%d",&selec2);
                getchar();
                switch(selec2){
                    case 1:
                    system("cls");
                    printf("Ingrese Cancion: ");
                    fgets(str,100,stdin );
                    ptrStr=str;
                    break;
                    ////
                    case 2:
                    system("cls");
                    mostrar_nombres_listas(L_Global);
                    break;
                    ////
                    case 3:
                    system("cls");
                    printf("Ingrese el nombre de lista de repreoduccion que desea ver:\n\n");
                    scanf("%[^\n]",hola);
                    getchar();

                    mostrar_una_lista(hola, L_Global);
                    break;
                }
                break;
            case 5:
                system("cls");

                printf("Ingrese el nombre del archivo que desea importar!\n");
                printf("Ejemplo : Archivo.csv\n\n");

                scanf("%s", hola);
                getchar();

                L_Global = importar(hola);
                printf("Canciones importadas exitosamente!\n");
                printf("-->Presione enter para continuar\n");
                getchar();

                system("cls");
                break;
            case 6:
                system("cls");
                printf("Funcion no disponible\n");
                getchar();
                break;
            case 7:
                system("cls");
                printf("Saliendo del programa...\n\n");
                return 0;
                system("cls");
                break;
        }
        
    }

    return 0;
}


