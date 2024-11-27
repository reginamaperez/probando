#ifndef STLIBRO_H_INCLUDED
#define STLIBRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idLibro; /// �nico, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si est� activo - 1 si est� eliminado
}stLibro;

stLibro cargarUnLibro();
void mostrarUnLibro(stLibro libro);



#endif // STLIBRO_H_INCLUDED
