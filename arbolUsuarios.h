#ifndef ARBOLUSUARIOS_H_INCLUDED
#define ARBOLUSUARIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char calle[50];
    int altura;
    int cp;
    char ciudad[100];
    char localidad[50];
    char pais[100];
} stDomicilio;

typedef struct
{
    int idUsuario;
    char email[100];
    char password[20];
    char username[20];
    int esAdmin; /// 1 = si 0 = no
    char genero;
    char fechaNacimiento[20]; /// o se puede hacer con dia, mes, anio.
    int librosFavoritos[50]; /// se van a guardar los id de los libros favs.
    int validosLibrosFavs;
    char dni[10];
    stDomicilio domicilio;
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stUsuario;

typedef struct
{
    stUsuario datosUsuarios;
    struct nodoArbolUsuarios * izq;
    struct nodoArbolUsuarios * der;
} nodoArbolUsuarios;

/// PROTOTIPADO

void mostrarUnUsuario(stUsuario usuario);
nodoArbolUsuarios * inicArbol();
nodoArbolUsuarios * crearNodoArbol(stUsuario usuario);
nodoArbolUsuarios *insertarEnArbol(nodoArbolUsuarios *arbol, nodoArbolUsuarios *nuevoNodo);
void mostrarArbol(nodoArbolUsuarios * arbol);
void mostrarUsuariosActivos(nodoArbolUsuarios *arbol);
void mostrarUsuariosInactivos(nodoArbolUsuarios *arbol);
void elegirArbolAVer(nodoArbolUsuarios *arbol);
nodoArbolUsuarios *buscarUsuarioPorDni(nodoArbolUsuarios *arbol, char dni[20]);
nodoArbolUsuarios *buscarUsuarioPorEmail(nodoArbolUsuarios *arbol, char email[100]);
nodoArbolUsuarios *buscarUsuarioPorUsername(nodoArbolUsuarios *arbol, char username[20]);
nodoArbolUsuarios *bajaDelUsuario(nodoArbolUsuarios *arbol);
void modificarDireccionUsuario(nodoArbolUsuarios *arbol);
nodoArbolUsuarios * modificarUsername (nodoArbolUsuarios * arbol);
stUsuario cargarContraseniaRegistro(stUsuario usuario);
int obtenerMayorUsuario(nodoArbolUsuarios *arbolUsuarios);
int generarIdUsuarios(nodoArbolUsuarios *arbolUsuarios);
int verificarUsuarioExistente(nodoArbolUsuarios *arbol, char username[]);
int verificarEmailExistente(nodoArbolUsuarios *arbol, char email[]);
int verificarDniExistente(nodoArbolUsuarios *arbolUsuarios, char *dni);
void guardarUsuariosEnArchivo(nodoArbolUsuarios *arbolUsuarios, char nombreArchivo[]);
void guardarEnArchivoRec(nodoArbolUsuarios *arbolUsuarios, FILE *archivo);
nodoArbolUsuarios * cargarUsuariosDesdeArchivo(nodoArbolUsuarios *arbolUsuarios, char nombreArchivo[]);

#endif // ARBOLUSUARIOS_H_INCLUDED
