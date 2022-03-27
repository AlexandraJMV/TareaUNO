#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "list.h"

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

// Importacion de la informacion sobre canciones.
listaGlobal * importar (char * nombre_archivo)
{
    // Variables a utilizar
    FILE * arc_canciones;
    listaGlobal * gl_canciones;
    cancion * aux_song;
    char aux_cadena[150];

    // Abrir archivo
    arc_canciones = fopen(nombre_archivo, "rt");
    if (arc_canciones == NULL)
    {
        perror("No se pudo abrir el archivo de canciones en modo lectura");
        exit(1);
    }

    // Reservar memoria cancion auxiliar
    aux_song = (cancion *) malloc( sizeof(cancion) );
    if (aux_song == NULL)
    {
        perror("Error al reservar memoria para auxiliar");
        exit(1);
    }

    // Reservar memoria lista global
    gl_canciones = (listaGlobal *) malloc( sizeof(listaGlobal) );
    if (gl_canciones == NULL)
    {
        perror("Error al reservar memoria para auxiliar");
        exit(1);
    }

    // Inicializar variables pertinentes
    gl_canciones->CantCanciones = 0;
    gl_canciones->canciones = createList();
    gl_canciones->listasExistentes = createList();
    aux_song->anyo = 0;

    // Lectura detalles y rellenado de campos a traves de funcion
    while(fscanf(arc_canciones,"%150[^\n]", aux_cadena) != EOF)
    {
        rellenar_cancion(aux_song, aux_cadena);
        gl_canciones->CantCanciones ++;
        pushFront(gl_canciones->canciones, aux_song);

        //printf("%s\n", aux_song->nombre);
        getc(arc_canciones);
    }
    return gl_canciones;
}

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (150*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}


void rellenar_cancion(cancion * song, char * aux_cadena)
{
    //printf("%s\n", aux_cadena);
    for(int i = 0 ; i<5 ; i++)
    {
        char *aux  = get_csv_field(aux_cadena, i);
        //printf("AUXILIAR = %s  ", aux);
        switch(i)
        {
            case 0:
                strcpy(song->nombre, aux);
                break;
            case 1:
                strcpy(song->artista, aux);
                break;
            case 2:
                //agregar_genero();
                break;
            case 3:
                song->anyo = atoi(aux);
                break;
            case 4:
                //printf("REVISION FORMATO  LISTA: %s\n", aux);
                break;
        }
}
}
