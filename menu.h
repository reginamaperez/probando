#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "arbolUsuarios.h"
#include "stCelda.h"
#include "stComentario.h"
#include "stLibro.h"

int menu(nodoArbolUsuarios ** arbolUsuarios, nodoLibro ** listaLibros, nodoComentario * listaComentatrios);
void mostrarMenuPrincipal();
void registrarUsuario(nodoArbolUsuarios **arbolUsuarios);
void iniciarSesion(nodoArbolUsuarios *arbolUsuarios,nodoLibro * listaLibros, nodoComentario * listaComentarios);
void menuAdministrador(nodoArbolUsuarios ** arbolUsuarios, nodoLibro **listaLibros);
void menuPostLogin(nodoArbolUsuarios *usuarioLogueado, nodoArbolUsuarios **arbolUsuarios,nodoLibro ** listaLibros, nodoComentario * listaComentarios);
void modificarInformacionPersonal(nodoArbolUsuarios* usuario, nodoArbolUsuarios *arbolUsuarios);
void menuLibros(nodoArbolUsuarios * usuarioLogueado, nodoLibro ** listaLibros, nodoComentario ** listaComentarios);
#endif // MENU_H_INCLUDED
