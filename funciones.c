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

listaC* existe_Lista(listaGlobal * list_gl, const char *str_lista){
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

void agregar_lista(const char * str_lista,  cancion * song, listaGlobal * list_gl){
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
        pushBack(aux->canciones, song);

        song->lista = aux;
        pushBack(list_gl->listasExistentes, aux);
    }
}

generoC * existe_genero(char *genero, List *lista_gen){
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

void agregar_genero(cancion * song, char * cad_generos, listaGlobal * list_gl){
    int i = 0;
    const char * aux_gen = get_csv_fieldV2(cad_generos, i);
    song->generos = createList();

    do
    {
        if (aux_gen == NULL ) break;

        generoC * aux_existe = existe_genero((char *)aux_gen, list_gl->generos);
        if (aux_existe != NULL)
        {
            pushFront(song->generos , aux_existe);
            aux_existe->cantidadCan++;
            pushBack(aux_existe->canciones, song);
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
            pushBack(aux->canciones, song);
            pushBack(song->generos, aux);
            pushBack(list_gl->generos, aux);
        }
        i++;
        aux_gen = get_csv_fieldV2(cad_generos, i);
    }while(1);
}

void rellenar_cancion(cancion * song, char * aux_cadena, listaGlobal * list_gl){
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

/*Eliminar cancion (char* Nombre, char* artista, int año): El usuario ingresa el nombre de
una canción y la aplicación elimina la canción correspondiente de todas las listas de reproducción correspondientes.
De no existir la canción se debe mostrar un aviso por pantalla.*/

cancion * existe_cancion(char *song, char * artista, int anyo, List *lista_can){

    cancion * aux_cancion = (cancion *) firstList(lista_can);

    printf("Primera cancion en lista = %s, %s, %d\n\n", aux_cancion->nombre, aux_cancion->artista, aux_cancion->anyo);
    if (aux_cancion == NULL)
    {
        return NULL;
    }
    while(aux_cancion != NULL)
    {
        //printf("Comparando %s y %s\n\n", aux_cancion->nombre, song);
        if(strcmp(aux_cancion->nombre, song) == 0){
            printf("Existe el nombre!\n");
            if (strcmp(aux_cancion->artista, artista) == 0){
                printf("Existe el artista!\n");
                if(aux_cancion->anyo ==  anyo){
                    printf("Existe el  anyo!\n");
                     return aux_cancion;
                }
            }
        }
        else
            aux_cancion = (cancion *) nextList(lista_can);
    }
    return NULL;
}

void borrar_de_lista(cancion * song){
    cancion * aux_song = (cancion *) firstList(song->lista->canciones);

    while (aux_song != NULL)
    {
        if (aux_song == song)
        {
            popCurrent(song->lista->canciones);
            song->lista->cantidadCan--;
            break;
        }
        else
            aux_song = (cancion *)  nextList(song->lista->canciones);
    }
}

void borrar_de_genero(cancion * song){
    generoC * rec_generos = firstList(song->generos);

    while (rec_generos != NULL)
    {
        cancion * aux_song = firstList(rec_generos->canciones);
        while (aux_song != NULL)
        {
            if(aux_song == song)
            {
                popCurrent(rec_generos->canciones);
                rec_generos->cantidadCan--;
                break;
            }
            else
                aux_song =  (cancion *)  nextList(rec_generos->canciones);
        }
        rec_generos =  (generoC *) nextList(song->generos);
    }
}

void borrar_de_global(cancion * song, listaGlobal * l_gl){
    cancion  * aux_song = (cancion *) firstList (l_gl->canciones);

    while (aux_song != NULL)
    {
        if (song == aux_song)
        {
            popCurrent(l_gl->canciones);
            l_gl->CantCanciones--;
            break;
        }
        else
            aux_song = (cancion  *) nextList (l_gl->canciones);
    }
}

void eliminar_cancion(char * nombre, char * artista, int anyo, listaGlobal  * l_gl){
    cancion * aux_song = existe_cancion(nombre, artista, anyo, l_gl->canciones);
    if (aux_song == NULL)
    {
        printf("La cancion ingresada no existe!\n\n");
    }
    else
    {
        borrar_de_lista(aux_song);
        borrar_de_genero(aux_song);
        borrar_de_global(aux_song, l_gl);
        printf("Se ha eliminado la cancion seleccionada!\n\n");
    }
}

cancion * crear_cancion(void){
    cancion * aux = (cancion *) malloc (sizeof(cancion));
    if (aux == NULL)
    {
        perror("No se pudo crear la cancion auxiliar!\n");
        exit(1);
    }
    return aux;
}

listaGlobal * importar (char * nombre_archivo){
    // Variables a utilizar
    FILE * arc_canciones;
    listaGlobal * gl_canciones;
    char aux_cadena[150];

    // Abrir archivo
    arc_canciones = fopen(nombre_archivo, "rt");
    if (arc_canciones == NULL)
    {
        perror("No se pudo abrir el archivo de canciones en modo lectura");
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

    // Lectura detalles y rellenado de campos a traves de funcion
    while(fscanf(arc_canciones,"%150[^\n]", aux_cadena) != EOF)
    {
        cancion * aux_song = crear_cancion();
        rellenar_cancion(aux_song, aux_cadena, gl_canciones);
        gl_canciones->CantCanciones ++;
        pushBack(gl_canciones->canciones, aux_song);

        getc(arc_canciones);
    }

    /*
    // TEST IMPRESION DE INFORMACIONPOR GENERO
        generoC * test = (generoC *) firstList(gl_canciones->generos);
        int contador = 1;
        while (test != NULL)
        {
            printf("%d - %s\n\n", contador, test->NomGenero);
            cancion * test2 = (cancion *) firstList(test->canciones);
            int cont2 = 1;
            while(test2 != NULL)
            {
                printf("%d - %s\n",cont2, test2->nombre);
                test2 = (cancion *) nextList(test->canciones);
                cont2++;
            }
            printf("\n");
            contador++;
            test = (generoC *) nextList(gl_canciones->generos);
        }
    // TEST IMPRESION DE CANCIONES
    cancion * test = (cancion *) firstList(gl_canciones->canciones);
    while (test != NULL)
    {
        printf("%s\n\n", test->nombre);
        test = (cancion *) nextList(gl_canciones->canciones);
    }

    //TEST IMPRESION DE  LISTAS
    listaC * test = (listaC *) firstList(gl_canciones->listasExistentes);
    while (test != NULL)
    {
        printf("%s, cantidad de canciones = %d", test->NomLista, test->cantidadCan);

        cancion * test2= (cancion*)  firstList(test->canciones);
        int cont = 1;
        while (test2 != NULL){
            printf("%d.  %s, %s, %d\n",  cont, test2->nombre, test2->artista, test2->anyo);
            test2 = (cancion *) nextList(test->canciones);
            cont++;
        }
        printf("\n\n");
        test = (listaC *) nextList(gl_canciones->listasExistentes);
    }

    //TEST  INFO DE  GENEROS

    cancion * test = firstList(gl_canciones->canciones);
    test = nextList(gl_canciones->canciones);
    printf("test = %s\n\n", test->nombre);

    generoC * gen = firstList(test->generos);
    while(gen != NULL)
    {
        printf("nombre  genero : %s\n ", gen->NomGenero);
        gen = (generoC *) nextList(test->generos);
    }*/
        // TEST IMPRESION DE INFORMACIONPOR GENERO
        generoC * test = (generoC *) firstList(gl_canciones->generos);
        int contador = 1;
        while (test != NULL)
        {
            printf("%d - %s\n\n", contador, test->NomGenero);
            cancion * test2 = (cancion *) firstList(test->canciones);
            int cont2 = 1;
            while(test2 != NULL)
            {
                printf("%d - %s\n",cont2, test2->nombre);
                test2 = (cancion *) nextList(test->canciones);
                cont2++;
            }
            printf("\n");
            contador++;
            test = (generoC *) nextList(gl_canciones->generos);
        }


    fclose(arc_canciones);
    return gl_canciones;
}
