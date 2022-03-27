#include "list.h"
#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct cancion cancion;

typedef struct listaC listaC;

typedef struct listaGlobal  listaGlobal;

listaGlobal * importar (char * nombre_archivo);

void  rellenar_info_cancion(cancion * cancion, char info[150]);

void rellenar_cancion(cancion * song, char * aux_cadena);

const char *get_csv_field (char * tmp, int k);

#endif // FUNCIONES_H_INCLUDED
