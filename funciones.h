#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "list.h"

typedef struct cancion cancion;

typedef struct listaC listaC;

typedef struct listaGlobal  listaGlobal;

typedef struct generoC generoC;

listaGlobal * importar (char * nombre_archivo);

const char *get_csv_fieldV2 (char * tmp, int k);

void  rellenar_info_cancion(cancion * cancion, char info[150]);

void rellenar_cancion(cancion *song, char * aux_cadena, listaGlobal * gbl_list);

const char *get_csv_field (char * tmp, int k);

void agregar_lista(const char * str_generos,  cancion * song, listaGlobal *list_global );

generoC  * existe_genero(char *genero, List *lista_gen);

listaC * existe_Lista(listaGlobal * list_gl, const char *str_lista);

void agregar_genero(cancion * song, char * aux_cadena, listaGlobal * list_gl);

cancion * existe_cancion(char *song, char * artista, int anyo, List *lista_can);

void borrar_de_lista(cancion * song);

void eliminar_cancion(char * nombre, char * artista, int anyo, listaGlobal  * l_gl);

void borrar_de_genero(cancion * song);

#endif // FUNCIONES_H_INCLUDED
