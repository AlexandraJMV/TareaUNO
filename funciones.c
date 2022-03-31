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
       while(tmp[i]!=  '\0')
        {
            ret[i-ini_i] =  tmp[i];
            i++;
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
            if(tmp[i]== ' ' && tmp[i-1]==',')
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
        while( tmp[i]!=  '\0')
        {
            ret[i-ini_i] =  tmp[i];
            i++;
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

void agregar_cancion (char *nom, char * artista, int anyo, listaGlobal * lg){
    return;
}

cancion * existe_cancion(char *song, char * artista, int anyo, List *lista_can){


    cancion * aux_cancion = (cancion *) firstList(lista_can);
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
                printf("Pero no parece ser de este anyo! \n");
                break;
            }
            printf("Pero no el  artista </3\n");
            break;
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
        l_gl->CantCanciones--;
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

    fclose(arc_canciones);
    return gl_canciones;
}

void elim_main_ver(listaGlobal * lg){
    char nom[31];
    char artist[31];
    int year;

    system("cls");
    printf("\nIngrese el nombre, artista y anyo de la cancion a eliminar :\n");
    printf("\nNombre :\n");
    scanf("%[^\n]", nom);
    getchar();

    printf("\nArtista :\n");
    scanf("%[^\n]", artist);
    getchar();

    printf("\nAnyo :\n");
    scanf("%d", &year);
    getchar();

    printf("\nCancion seleccionada : %s, %s, %d\n\n", nom, artist, year);

    eliminar_cancion(nom, artist, year, lg);

    printf("---> Presione cualquier tecla para continuar\n");
    getchar();
    system("cls");
}
//
void concat_song(char *nom, char * artist,  char * gens,  char * year, char * list){
    strcat(nom, ",");
    strcat(nom,artist);
    strcat(nom,",");
    strcat(nom, gens);
    strcat(nom,",");
    strcat(nom,year);
    strcat(nom,",");
    strcat(nom,list);
}

void leer_agregar_main(listaGlobal  *  lg){
    char nom[150];
    char artist[31];
    char list[31];
    char gen[31];
    char gens[100] = "";
    char aux_gens[100] = "\"";
    int aux_coma;
    char year[10];

    system("cls");
    printf("\nIngrese el nombre, artista y anyo de la cancion a agregar :\n");
    printf("Nombre :\n");
    scanf("%[^\n]", nom);
    getchar();

    printf("\nArtista :\n");
    scanf("%[^\n]", artist);
    getchar();

    printf("\nAnyo :\n");
    scanf("%s", year);
    getchar();

    printf("\nIngrese a que generos pertenece su cancion ( y FIN cuando haya terminado!) :\n");
    aux_coma = 0;
    do{
            scanf("%[^\n]", gen);
            getchar();
            if(strcmp(gen, "FIN") == 0) break;
            if (aux_coma>0)
                        strcat(gens, ", ");
            aux_coma++;
            strcat(gens, gen);
            }while(1);
        if(aux_coma > 1){
            char comillas[2] = "\"";
            strcat(gens, comillas);
            strcat(aux_gens, gens);
            printf("\nSu cancion es : %s,%s,%s,%s\n\n", nom, artist, aux_gens, year);
        }
        else
            printf("\nSu cancion es : %s,%s,%s,%s\n\n", nom, artist, gens, year);

        printf("Ingrese la lista de reproduccion a la que la desea agregar :\n");
        scanf("%[^\n]", list);
        getchar();


        // MEJOR BUSCAR  POR CANCION
        cancion * aux_song = existe_cancion(nom, artist, atoi(year), lg->canciones);

        // NO EXISTE LA CANCION
        if (aux_song == NULL)
        {
                    if (aux_coma > 1)
                        concat_song(nom, artist, aux_gens, year, list);
                    else concat_song(nom, artist, gens, year, list);

                    cancion * new_song = crear_cancion();
                    rellenar_cancion(new_song, nom, lg);
                    pushBack(lg->canciones, new_song);
                    lg->CantCanciones++;

                    printf("\nSu cancion se ha guardado exitosamente!\n");
                    printf("---> Presione cualquier tecla para continuar\n");
                    getchar();
                    system("cls");
        }
        // SI EXISTE LA CANCION
        else
        {
            listaC * rec_listas = existe_Lista(lg, list);
            // NO EXISTE LA LISTA
            if(rec_listas == NULL)
            {
                int eleccion = 1;
                printf("\nSu lista no existe! Desea crearla? (yes = 1, no = 0)\n");
                scanf("%d", &eleccion);
                getchar();

                if (eleccion == 0){
                    system("cls");
                    printf("Proceso terminado! Apriete cualquier  tecla para continuar.\n");
                    getchar();
                    system("cls");
                    return;
                }

                listaC * new_lista = (listaC *) malloc (sizeof(listaC));
                new_lista->canciones = createList();
                strcpy(new_lista->NomLista, list);
                new_lista->cantidadCan = 1;

                pushBack(new_lista->canciones, aux_song);
                pushBack(lg->listasExistentes, new_lista);
                borrar_de_lista(aux_song);
                aux_song->lista = new_lista;

                system("cls");
                printf("\nSu lista se ha creado exitosamente!\n");
                printf("---> Presione cualquier tecla para continuar\n");
                getchar();
                system("cls");

            }
            // SI EXISTE  LA LISTA
            else
            {
                if (strcmp(aux_song->lista->NomLista, list) == 0)
                {
                system("cls");
                printf("\nEsta cancion ya pertenece a la lista!\n");
                printf("---> Presione cualquier tecla para continuar\n");
                getchar();
                system("cls");
                return;
                }
                // LA CANCION NO PERTENECE A LA LISTA
                else
                {
                    borrar_de_lista(aux_song);
                    aux_song->lista = rec_listas;
                    pushBack(rec_listas->canciones, aux_song);
                    system("cls");
                    printf("\nSu cancion se ha guardado exitosamente!\n");
                    printf("---> Presione cualquier tecla para continuar\n");
                    getchar();
                    system("cls");
                    return;
                }
            }
        }
}
