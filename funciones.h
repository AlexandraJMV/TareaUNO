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

void agregar_cancion (char *nom, char * artista, int anyo, listaGlobal * lg);

void elim_main_ver(listaGlobal *  lg);

void leer_agregar_main(listaGlobal * lg);

void concat_song(char *nom, char * artist,  char * gens,  char * year, char * lista);


void Buscar_gen (char* gen, listaGlobal* lg);

void formato(char * str, char * strend);

cancion * existe_nombre(char *nom_can, List *lista_nom);

void Buscar_nom (char* busqueda, listaGlobal* Global);

void mostrar_nombres_listas(listaGlobal * lg);

void mostrar_una_lista(char * nom_lista, listaGlobal * lg);

#endif // FUNCIONES_H_INCLUDED
