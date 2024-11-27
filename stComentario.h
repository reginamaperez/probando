#ifndef STCOMENTARIO_H_INCLUDED
#define STCOMENTARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stLibro.h"
#include "arbolUsuarios.h"

typedef struct {
    int idComentario;  /// único, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio.
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stComentario;

typedef struct{
    stComentario dato;
    struct nodoComentario * sig;
}nodoComentario;

/// PROTOTIPADO

void mostrarComentario(stComentario comentario);
nodoComentario * inicListaComentario();
nodoComentario* crearNodoComentario(stLibro libro, nodoComentario* listaC, nodoArbolUsuarios* usuarioLogueado);
stComentario crearComentario(stLibro libro, int idUsuario, nodoComentario* listaC);
int generarIdComentario(nodoComentario * listaComentarios);
nodoComentario * buscaComentarioPorId(nodoComentario * listaComentario, int idComentario);
nodoComentario* buscarUltimoNodoComentario(nodoComentario* listaComentario);
nodoComentario* agregarAlFinalComentario(nodoComentario* listaComentario, nodoComentario* nuevo);
void mostrarComentarios(nodoComentario* listaComentarios);
void mostrarComentariosPorLibro(nodoComentario * listaComentarios, int idLibro);
nodoComentario* buscarAeliminar(nodoComentario* listaC, nodoArbolUsuarios* usuarioLogueado, int idComentario);
void editarComentario(nodoComentario *comentario);

#endif // STCOMENTARIO_H_INCLUDED
