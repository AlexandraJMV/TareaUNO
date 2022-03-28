#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "list.h"

typedef struct cancion{ //Estructura de las canciones del archivo con su: nombre,artista,genero,año y a la lista que pertenece.
    char nombre[31];
    char artista[31];
    List* generos;
    int anyo;
    listaC * lista;
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
    List* generos;
}listaGlobal;

typedef struct generoC{
    size_t cantidadCan;
    List* canciones;
    char NomGenero[31];
}generoC;

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
    gl_canciones->generos = createList();
    aux_song->anyo = 0;

    // Lectura detalles y rellenado de campos a traves de funcion
    while(fscanf(arc_canciones,"%150[^\n]", aux_cadena) != EOF)
    {
        rellenar_cancion(aux_song, aux_cadena, gl_canciones);
        gl_canciones->CantCanciones ++;
        pushFront(gl_canciones->canciones, aux_song);

        //printf("%s\n", aux_song->nombre);
        getc(arc_canciones);
    }
    fclose(arc_canciones);
    free(aux_song);
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

        i = i-1;
        for (i ; tmp[i]!=  '\0' ; i++)
        {
            ret[i-ini_i] =  tmp[i];
        }
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

const char *get_csv_fieldV2 (char * tmp, int k) {
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
            if(tmp[i]== ' ')
            {
                ini_i++;
                i++;
                continue;
            }
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ',' ){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {

        i = i-1;
        for (i ; tmp[i]!=  '\0' ; i++)
        {
            ret[i-ini_i] =  tmp[i];
        }
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}


listaC* existe_Lista(listaGlobal * list_gl, const char *str_lista)
{
    listaC * aux_lista = (listaC *) firstList(list_gl->listasExistentes);

    if (aux_lista == NULL) return NULL;

    for (int i = 0 ; aux_lista != NULL ; i++)
    {
        if (strcmp(aux_lista->NomLista, str_lista) == 0)
        {
            return aux_lista;
        }
        aux_lista = (listaC *) nextList(list_gl->listasExistentes);
    }
    return NULL;
}

void agregar_lista(const char * str_lista,  cancion * song, listaGlobal * list_gl)
{
    // existe_Lista mueve el current a la posicion de la lista en caso de que exista, devuelve un entero (0 o 1)
    //SOLUCION = EXISTE LISTA DEVULEVE DATO DEL CURRENT
    listaC * aux_existe = existe_Lista(list_gl, str_lista);
    if (aux_existe != NULL )
    {
        song->lista = aux_existe;
        pushBack(song->lista->canciones, song);
        song->lista->cantidadCan ++;
    }
    else
    {
        song->lista = (listaC *) malloc (sizeof(listaC));
        if (song->lista == NULL)
        {
            perror("No se pudo guardar memoria para la lista");
            exit(1);
        }

        listaC * aux = (listaC *) malloc (sizeof(listaC));
        if (aux == NULL)
        {
            perror("No se pudo guardar memoria para la lista auxiliar");
            exit(1);
        }

        strcpy(aux->NomLista, str_lista);
        aux->cantidadCan = 1;
        aux->canciones = createList();
        pushFront(aux->canciones, song);

        song->lista = aux;
        pushFront(list_gl->listasExistentes, aux);
        firstList(list_gl->listasExistentes);
    }
}

generoC * existe_genero(char *genero, List *lista_gen)
{
    generoC * aux_genero= (generoC *) firstList(lista_gen);

    if (aux_genero == NULL)
    {
        return NULL;
    }
    while(aux_genero != NULL)
    {
        if(strcmp(aux_genero->NomGenero, genero) == 0)
        {
            return aux_genero;
        }
        aux_genero = (generoC *) nextList(lista_gen);
    }
    return NULL;
}

void agregar_genero(cancion * song, char * cad_generos, listaGlobal * list_gl)
{
    int i = 0;
    const char * aux_gen = get_csv_fieldV2(cad_generos, i);

    do
    {
        if (aux_gen == NULL ) break;

        generoC * aux_existe = existe_genero((char *)aux_gen, list_gl->generos);
        if (aux_existe != NULL)
        {
            pushFront(song->generos , aux_existe);
            aux_existe->cantidadCan++;
            pushFront(aux_existe->canciones, song);
        }
        else if (aux_existe == NULL)
        {
            generoC *aux = (generoC *) malloc (sizeof(generoC));
            if (aux == NULL)
            {
                perror("No se pudo guardar memoria para genero auxiliar");
                exit(1);
            }

            strcpy(aux->NomGenero, aux_gen);
            aux->cantidadCan = 1;
            aux->canciones = createList();
            pushFront(aux->canciones, song);

            song->generos = createList();
            pushFront(song->generos, aux);
            pushFront(list_gl->generos, aux);
            firstList(list_gl->generos);
            firstList(song->generos);
        }
        i++;
        aux_gen = get_csv_fieldV2(cad_generos, i);
    }while(1);
}


void rellenar_cancion(cancion * song, char * aux_cadena, listaGlobal * list_gl)
{
    //printf("%s\n", aux_cadena);
    for(int i = 0 ; i<5 ; i++)
    {
        const  char *aux  = get_csv_field(aux_cadena, i);
        switch(i)
        {
            case 0:
                strcpy(song->nombre, aux);
                break;
            case 1:
                strcpy(song->artista, aux);
                break;
            case 2:
                agregar_genero(song, (char *) aux, list_gl);
                break;
            case 3:
                song->anyo = atoi(aux);
                break;
            case 4:
                agregar_lista(aux, song, list_gl);
                break;
        }
    }
}

