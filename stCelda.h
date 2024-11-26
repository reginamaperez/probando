#ifndef STCELDA_H_INCLUDED
#define STCELDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stComentario.h"
#include "arbolUsuarios.h"
#include "stLibro.h"


typedef struct{
    int idLibro;
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int libroEliminado;
    int idComentario;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20];
    int comentarioEliminado;
}stRegistroLibroComentario;

typedef struct{
    stLibro libro;
    struct nodoLibro * sig;
    nodoComentario * dato;
}nodoLibro;


/// PROTOTIPADO:

nodoLibro * inicListaLibros();
nodoLibro * crearNodoLibros(stLibro libro);
nodoLibro * buscaLibroPorId(nodoLibro * listaLibros, int idLibro);
nodoLibro* buscarUltimoNodo(nodoLibro* listaLibros);
nodoLibro* agregarAlFinalLibro(nodoLibro* listaLibros, nodoLibro* nuevo);
void mostrarListaLibros(nodoLibro * listaLibros);
void mostrarUnNodoLibro(nodoLibro * nodo);
nodoLibro * altaLdl(nodoLibro * ldl, stLibro libro, stComentario comentario,nodoArbolUsuarios * usuarioLogueado);
nodoLibro *  archivoToLDL(char nombreArchivo[], nodoLibro * ldl,nodoArbolUsuarios * usuarioLogueado);
stLibro refactorizacionLibro(stRegistroLibroComentario reg);
stComentario refactorizacionComentario(stRegistroLibroComentario reg);
void mostrarLDL(nodoLibro * ldl);
void buscarLibrosPorAutor(nodoLibro * listaLibros, char autorBuscar[]);
void buscarLibroPorTitulo(nodoLibro * listaLibros, char tituloBuscar []);
void buscarLibroPorCategoria(nodoLibro * listaLibros, char categoriaBuscar []);
nodoLibro * cargarArchivoEnLista(char nombreArchivo[], nodoLibro *listaLibros);


#endif // STCELDA_H_INCLUDED
