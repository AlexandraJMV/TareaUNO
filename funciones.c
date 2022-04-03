#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"
#include "list.h"
#define MAX_CHAR 40
#define MAX_CHAR_GENS 50


typedef struct cancion{ //Estructura de las canciones del archivo con su: nombre,artista,genero,año y a la lista que pertenece.
    char nombre[MAX_CHAR];
    char artista[MAX_CHAR];
    List* generos;
    int anyo;
    listaC * lista;
}cancion;

typedef struct listaC{ //Estructura de las listas de canciones indica: Cantidad de canciones, las canciones , y nombre de la lista (segun archivo).
    size_t cantidadCan;
    List* canciones;
    char NomLista[MAX_CHAR];
}listaC;

typedef struct listaGlobal{ //Estructura de la lista "Global" que almacena todas las canciones del archivo.
    size_t CantCanciones;
    List* canciones;
    List* listasExistentes;
    List* generos;
}listaGlobal;

typedef struct generoC{ // Estructura de  los generos indiza: Cantidad, canciones  pertenecientes al genero y el nombre del mismo.
    size_t cantidadCan;
    List* canciones;
    char NomGenero[MAX_CHAR];
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

listaC* existe_Lista(listaGlobal * list_gl, const char *str_lista){ // Comprueba exitencia de una lista de reproduccion en la lista global
    listaC * aux_lista = (listaC *) firstList(list_gl->listasExistentes);
    char nom_lista[MAX_CHAR], buscar_lista[MAX_CHAR];

    formato((char *)str_lista, buscar_lista);

    if (aux_lista == NULL) return NULL;

    for (int i = 0 ; aux_lista != NULL ; i++)
    {
        formato(aux_lista->NomLista,nom_lista);
        if (strcmp(buscar_lista, nom_lista) == 0)
        {
            return aux_lista;
        }
        aux_lista = (listaC *) nextList(list_gl->listasExistentes);
    }
    return NULL;
}

void agregar_lista(const char * str_lista,  cancion * song, listaGlobal * list_gl){ // Agrega cancion a lista existente o crear nueva lista en caso de que no exista
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

generoC * existe_genero(char *genero, List *lista_gen){ // Comprueba existencia de un genero en la lista global
    generoC * aux_genero= (generoC *) firstList(lista_gen);
    char nom_genero[MAX_CHAR], genero_busc[MAX_CHAR];

    formato(genero, genero_busc);

    if (aux_genero == NULL)
    {
        return NULL;
    }
    while(aux_genero != NULL)
    {

        formato(aux_genero->NomGenero, nom_genero);
        if(strcmp(nom_genero, genero_busc) == 0)
        {
            return aux_genero;
        }

        aux_genero = (generoC *) nextList(lista_gen);
    }
    return NULL;
}

void agregar_genero(cancion * song, char * cad_generos, listaGlobal * list_gl){ // Agrega cancion a genero existente o crear un nuevo genero en caso de que no exista
    int i = 0;
    const char * aux_gen = get_csv_fieldV2(cad_generos, i);
    song->generos = createList();

    do
    {
        if (aux_gen == NULL ) break;

        generoC * aux_existe = existe_genero((char *)aux_gen, list_gl->generos);
        if (aux_existe != NULL)
        {
            pushBack(song->generos , aux_existe);
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

void rellenar_cancion(cancion * song, char * aux_cadena, listaGlobal * list_gl){ // Rellena cada campo de un struct cancion a partir de una cadena
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

cancion * existe_cancion(char *song, char * artista, int anyo, List *lista_can){ // Comprueba existencia de una cancion en la lista global


    char nom_en_lista[MAX_CHAR], nom_buscar[MAX_CHAR];
    char art_en_lista[MAX_CHAR], art_buscar[MAX_CHAR];

    formato(song, nom_buscar);
    formato(artista, art_buscar);

    cancion * aux_cancion = (cancion *) firstList(lista_can);
    if (aux_cancion == NULL)
    {
        return NULL;
    }
    while(aux_cancion != NULL)
    {
        formato(aux_cancion->nombre, nom_en_lista);

        if(strcmp(nom_en_lista, nom_buscar) == 0){
            
            printf("Existe el nombre!\n");
            formato(aux_cancion->artista, art_en_lista);

            if (strcmp(art_buscar, art_en_lista) == 0){

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

void borrar_de_lista(cancion * song){ // Borra la cancion de la lista de reproduccion a la que  pertenece
    cancion * aux_song = (cancion *) firstList(song->lista->canciones);

    while (aux_song != NULL)
    {
        if (aux_song == song)
        {
            popCurrent(song->lista->canciones);
            song->lista->cantidadCan--;
            song->lista  = NULL;
            break;
        }
        else
            aux_song = (cancion *)  nextList(song->lista->canciones);
    }
}

void borrar_de_genero(cancion * song){ // Borra la cancion de los generos a la cual pertenece
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
            else aux_song =  (cancion *)  nextList(rec_generos->canciones);
        }
        rec_generos =  (generoC *) nextList(song->generos);
    }
}

void borrar_de_global(cancion * song, listaGlobal * l_gl){ // Borra la cancion de la lista global
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

void eliminar_cancion(char * nombre, char * artista, int anyo, listaGlobal  * l_gl){ // Elimina cancion ingresada en caso de que exista
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

cancion * crear_cancion(void){ // Guarda memoria para una  nueva cancion
    cancion * aux = (cancion *) malloc (sizeof(cancion));
    if (aux == NULL)
    {
        perror("No se pudo crear la cancion auxiliar!\n");
        exit(1);
    }
    return aux;
}

listaGlobal * importar (char * nombre_archivo){ // Importacion de canciones desde archivo decanciones
    // Variables a utilizar
    FILE * arc_canciones;
    listaGlobal * gl_canciones;
    char aux_cadena[MAX_CHAR*5] ="";

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
    getc(arc_canciones);
    getc(arc_canciones);
    getc(arc_canciones);

    while(fscanf(arc_canciones,"%300[^\n]", aux_cadena) != EOF)
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

void elim_main_ver(listaGlobal * lg){ // Impresion de mensajes  para recibir imput al eliminar cancion, llamada a funcion eliminar
    char nom[MAX_CHAR];
    char artist[MAX_CHAR];
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

    printf("\nCancion seleccionada :\n| %s | %s | %d |\n\n", nom, artist, year);

    eliminar_cancion(nom, artist, year, lg);

    printf("---> Presione enter para continuar\n");
    getchar();
    system("cls");
}
//
void concat_song(char *nom, char * artist,  char * gens,  char * year, char * list){ // Concatenacion de informacion en cadenas en el formato que requiere la funcion RELLENAR CANCION
    strcat(nom, ",");
    strcat(nom,artist);
    strcat(nom,",");
    strcat(nom, gens);
    strcat(nom,",");
    strcat(nom,year);
    strcat(nom,",");
    strcat(nom,list);
}

void leer_agregar_main(listaGlobal  *  lg){ // Mensajes para imput de agregar cancion e implementacion
    char nom[300];
    char artist[MAX_CHAR];
    char list[MAX_CHAR];
    char gen[MAX_CHAR];
    char gens[MAX_CHAR_GENS] = "";
    char aux_gens[MAX_CHAR_GENS] = "\"";
    int aux_coma;
    char year[10];
    char nom_list[MAX_CHAR], busc_list[MAX_CHAR];

    system("cls");
    printf("\nIngrese el nombre, artista y anyo de la cancion a agregar :\n");
    printf("\nNombre :\n");
    scanf("%[^\n]", nom);
    getchar();

    printf("\nArtista :\n");
    scanf("%[^\n]", artist);
    getchar();

    printf("\nAnyo :\n");
    scanf("%s", year);
    getchar();

    printf("\nIngrese uno a uno los generos a los cuales pertenece su cancion ( y FIN cuando haya terminado)! :\n");
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
            printf("\nSu cancion es : \n| %s | %s | %s | %s |\n\n", nom, artist, aux_gens, year);
        }
        else
            printf("\nSu cancion es : \n| %s | %s | %s | %s |\n\n", nom, artist, gens, year);

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

                    printf("\nSu cancion era nueva! Se ha creado y guardado exitosamente!\n");
                    printf("---> Presione enter para continuar\n");
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
                    printf("Proceso terminado! Apriete enter para continuar.\n");
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
                printf("---> Presione enter para continuar\n");
                getchar();
                system("cls");

            }
            // SI EXISTE  LA LISTA
            else
            {
                formato(aux_song->lista->NomLista, nom_list);
                formato(list, busc_list);
                if (strcmp(nom_list, busc_list) == 0)
                {
                system("cls");
                printf("\nEsta cancion ya pertenece a la lista!\n");
                printf("---> Presione enter para continuar\n");
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
                    printf("---> Presione enter para continuar\n");
                    getchar();
                    system("cls");
                    return;
                }
            }
        }
}

void Buscar_gen (char* busqueda, listaGlobal* Global){
    cancion* aux2;
    generoC* aux;
    generoC * aux3;
    int num_cant;

    aux= (generoC *)existe_genero(busqueda, Global -> generos);

    if (aux == NULL)
    {
        printf("%s NO se encuentra en lista de Generos.\n",busqueda);
        getchar();
    }
    else
    {
        num_cant = aux -> cantidadCan;
        aux2 = (cancion * ) firstList(aux -> canciones);

        printf("%s SI se encuentra en lista de Generos.\n\n",aux->NomGenero);
        printf("Lista de canciones del genero\n\n");
        printf("Nombre/Artista/Anyo                      Lista/Generos\n");
        printf("---------------------------------------------------------------------------\n");
        for( int i = 0; i < num_cant; i++)
        {
            printf("%-41s| %-31s\n",aux2 -> nombre, aux2->lista->NomLista);
            printf("%-31s", aux2->artista);
            printf("%9d |",aux2 -> anyo);

            aux3 = (generoC*) firstList(aux2 -> generos);
            while (aux3 != NULL)
            {
                printf(" %s",aux3->NomGenero);
                aux3 = (generoC*) nextList(aux2 -> generos);
            }
            printf("\n                                         |                               \n");

            aux2 = (cancion*) nextList(aux -> canciones);
        }
        printf("-------------------------------------------------------------------------------------\n");
        printf("\nCanciones del genero impresas! Presione enter para continuar\n");
        getchar();

    }
}

// Funcion para Facilitar la comparacion de dos cadenas (Transforma a mayusculas y elimina espacios al inicio y final de la cadena)
void formato(char * str, char * strend){

    int ind = 0;

    for (int i = 0 ; str[i] != '\0' ; i++)
    {
        if (isspace(str[i])){
            continue;
        }
        else
        {
            strend[ind] = toupper(str[i]);
            ind ++;
        }
    }
    strend[ind] = '\0';
}   

void Buscar_nom (char* busqueda, listaGlobal* Global)
{
    cancion* aux;
    generoC * aux2;
    aux  = existe_nombre (busqueda, Global -> canciones );
    if (aux == NULL)
    {
        printf("%s. NO se encuentra en lista de Canciones.\n",busqueda);
    }
    else
    {
        printf("%s. SI se encuentra en lista de Canciones.\n",busqueda);
        printf("%s, %s, ",aux -> nombre, aux -> artista);
        
        aux2 = (generoC *) firstList(aux -> generos);
        while (aux2 != NULL)
        {
            printf(" %s", aux2->NomGenero);
            aux2 = (generoC*) nextList(aux -> generos);
        }
        printf(" ,%d, %s\n", aux -> anyo, aux -> lista -> NomLista);
    }

    printf("\n--> Ingrese enter para continuar\n");
    getchar();
}


cancion* existe_nombre(char *nom_can, List *lista_nom){ 
    char aux_nom[40], aux_list[40];
    cancion * aux_nombre= (cancion *) firstList(lista_nom);

    formato(nom_can, aux_nom);

    if (aux_nombre == NULL)
    {
        return NULL;
    }
    while(aux_nombre != NULL)
    {
        formato(aux_nombre->nombre, aux_list);
        if(strcmp(aux_nom, aux_list) == 0)
        {
            return aux_nombre;
        }
        aux_nombre = (cancion *) nextList(lista_nom);
    }
    return NULL;
}

void mostrar_nombres_listas(listaGlobal * lg){
    listaC * rec_lista = (listaC *) firstList (lg->listasExistentes);
    int cont = 0;

    printf("Listas de reproduccion existentes...\n\n");

    while(rec_lista != NULL)
    {
        printf("%-31s%10d\n", rec_lista->NomLista, rec_lista->cantidadCan);
        cont++;
        rec_lista = (listaC *) nextList (lg->listasExistentes);
    }

    if(cont == 0)
        printf("No tiene ninguna lista de reproduccion creada\n");
    else printf("Existen %d listas de reproduccion!\n\n\n", cont);

    printf("--> Presione enter para continuar\n");
    getchar();
}

void mostrar_una_lista(char * nom_lista, listaGlobal * lg){

    listaC * aux = existe_Lista(lg, nom_lista);
    cancion * aux2;
    generoC * aux3;
    int num_cant;

    if(aux == NULL)
        printf("Su lista de reproduccion no existe!\n\n");
    else
    {
        num_cant = aux->cantidadCan;
        aux2 = (cancion *) firstList (aux->canciones);

        printf("%s SI se encuentra en lista de Generos.\n\n",aux->NomLista);
        printf("Lista de canciones del genero\n\n");
        printf("Nombre/Artista/Anyo                      Lista/Generos\n");
        printf("---------------------------------------------------------------------------\n");
        for( int i = 0; i < num_cant; i++)
        {
            printf("%-41s| %-31s\n",aux2 -> nombre, aux2->lista->NomLista);
            printf("%-31s", aux2->artista);
            printf("%9d |",aux2 -> anyo);

            aux3 = (generoC*) firstList(aux2 -> generos);
            while (aux3 != NULL)
            {
                printf(" %s",aux3->NomGenero);
                aux3 = (generoC*) nextList(aux2 -> generos);
            }
            printf("\n                                         |                               \n");

            aux2 = (cancion*) nextList(aux -> canciones);
        }
        printf("-------------------------------------------------------------------------------------\n");
        printf("\nCanciones de la lista impresas!\n");
        getchar();
    }

    printf("--> Presione enter para continuar\n");
    getchar();

}