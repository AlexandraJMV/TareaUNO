
#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct cancion cancion;

typedef struct listaC listaC;

typedef struct listaGlobal  listaGlobal;

listaGlobal * importar (char * nombre_archivo);

void  rellenar_info_cancion(cancion * cancion, char info[150]);

void rellenar_cancion(cancion * song, char * aux_cadena, listaGlobal * gbl_list);

const char *get_csv_field (char * tmp, int k);

void agregar_genero(const char * str_generos,  cancion * song);

int existe_Lista(listaGlobal * list_gl, const char *str_lista);

#endif // FUNCIONES_H_INCLUDED
