#include "stCelda.h"

nodoLibro * inicListaLibros()
{
    return NULL;
}

nodoLibro * crearNodoLibros(stLibro libro)
{
    nodoLibro * nuevo= (nodoLibro*)malloc(sizeof(nodoLibro));
    nuevo->libro=libro;
    nuevo->sig=NULL;
    nuevo->dato= inicListaComentario();

    return nuevo;
}

/*

nodoLibro * buscaLibroPorId(nodoLibro * listaLibros, int idLibro){

    nodoLibro * aBuscar = NULL;
    nodoLibro * aux = listaLibros;

    while(aux && !aBuscar){
            if(aux->libro.idLibro == idLibro){
                aBuscar = aux;
            }
            aux = aux->sig;
    }

    return aBuscar;

}
*/
nodoLibro* buscaLibroPorId(nodoLibro* listaLibros, int id) {
    while (listaLibros) {
        printf("DEBUG: Revisando libro con ID: %d\n", listaLibros->libro.idLibro);
        if (listaLibros->libro.idLibro == id) {
            printf("DEBUG: Libro encontrado.\n");
            return listaLibros;
        }
        listaLibros = listaLibros->sig;
    }
    printf("DEBUG: No se encontró libro con el ID %d.\n", id);
    return NULL;
}

nodoLibro* buscarUltimoNodo(nodoLibro* listaLibros)
{
    nodoLibro * seg = listaLibros;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoLibro* agregarAlFinalLibro(nodoLibro* listaLibros, nodoLibro* nuevo)
{
    if(!listaLibros)
    {
        listaLibros = nuevo;
    }
    else
    {
        nodoLibro* ultimo = buscarUltimoNodo(listaLibros);
        ultimo->sig = nuevo;
    }

    return listaLibros;
}

void mostrarListaLibros(nodoLibro * listaLibros){

     while(listaLibros)
    {
        mostrarUnNodoLibro(listaLibros);
        listaLibros = listaLibros->sig;
    }
}

void gestionarLibrosFavoritos(nodoArbolUsuarios *usuarioLogueado, nodoLibro *listaLibros)
{
    printf("\nLibros Favoritos:\n");

    if (usuarioLogueado->datosUsuarios.validosLibrosFavs == 0) {
        printf("No tienes libros favoritos.\n");
    } else {
        for (int i = 0; i < usuarioLogueado->datosUsuarios.validosLibrosFavs; i++) {
            nodoLibro *libro = buscaLibroPorId(listaLibros, usuarioLogueado->datosUsuarios.librosFavoritos[i]);
            if (libro != NULL) {
                printf("%d. %s por %s\n", i + 1, libro->libro.titulo, libro->libro.autor);
            }
        }
    }

    char opcion;
    printf("¿Desea agregar un libro a favoritos (A) o quitar uno (Q)?\n");
    scanf(" %c", &opcion);

    if (opcion == 'A' || opcion == 'a') {
        // Agregar un libro a favoritos
        int idLibro;
        printf("Ingrese el ID del libro a agregar a favoritos:\n");
        scanf("%d", &idLibro);
        agregarLibroFavorito(usuarioLogueado, listaLibros, idLibro);
    } else if (opcion == 'Q' || opcion == 'q') {
        // Quitar un libro de favoritos
        if (usuarioLogueado->datosUsuarios.validosLibrosFavs == 0) {
            printf("No tienes libros favoritos para quitar.\n");
            return;
        }

        int libroAQuitar;
        printf("Ingrese el numero del libro a quitar (1-%d):\n", usuarioLogueado->datosUsuarios.validosLibrosFavs);
        scanf("%d", &libroAQuitar);

        if (libroAQuitar < 1 || libroAQuitar > usuarioLogueado->datosUsuarios.validosLibrosFavs) {
            printf("Opcion no valida.\n");
            return;
        }

        int idLibroAQuitar = usuarioLogueado->datosUsuarios.librosFavoritos[libroAQuitar - 1];

        for (int j = libroAQuitar - 1; j < usuarioLogueado->datosUsuarios.validosLibrosFavs - 1; j++) {
            usuarioLogueado->datosUsuarios.librosFavoritos[j] = usuarioLogueado->datosUsuarios.librosFavoritos[j + 1];
        }
        usuarioLogueado->datosUsuarios.validosLibrosFavs--;

        printf("Libro %s quitado de favoritos.\n", buscaLibroPorId(listaLibros, idLibroAQuitar));
    } else {
        printf("Opcion no valida.\n");
    }
}

void elegirListaAVerLibros (nodoLibro * listaLibros)
{
    char opcion;

    printf ("Elija lista a ver: A- Todos los libros B- Libros activos C- Libros eliminados\n");
    fflush(stdin);
    scanf("%c",&opcion);

    if (opcion == 'A' || opcion == 'a')
    {
         mostrarListaLibros(listaLibros);
    }
    else if (opcion == 'B' || opcion == 'b')
    {
        mostrarListaLibrosActivos(listaLibros);
    }
    else if (opcion == 'C' || opcion == 'c')
    {
        mostrarListaLibrosInactivos(listaLibros);
    }
    else
    {
        printf ("\nOpcion invalida\n");
    }
}


/// Ver listado solo de usuarios activos

void mostrarListaLibrosActivos (nodoLibro * listaLibros)
{
    while (listaLibros!=NULL)
    {
        if (listaLibros->libro.eliminado == 0)
        {
            mostrarUnLibro(listaLibros->libro);
        }
        listaLibros = listaLibros->sig;
    }
}

/// Ver listado solo de usuarios inactivos
void mostrarListaLibrosInactivos (nodoLibro * listaLibros)
{
    while (listaLibros!=NULL)
    {
        if (listaLibros->libro.eliminado == 1)
        {
            mostrarListaLibros(listaLibros);
        }
        listaLibros = listaLibros->sig;
    }
}

void bajaLogicaLibro(nodoLibro *listaLibros, int idLibro)
 {
    nodoLibro *actual = listaLibros;
    int encontrado = 0;

    while (actual != NULL) {
        if (actual->libro.idLibro == idLibro) {
            actual->libro.eliminado = 1; // Marcamos el libro como eliminado
            printf("El libro con ID %d ha sido dado de baja.\n", idLibro);
            encontrado = 1;
            break;
        }
        actual = actual->sig;
    }

    if (!encontrado) {
        printf("No se encontro ningun libro con ID %d.\n", idLibro);
    }
}

void agregarLibroFavorito(nodoArbolUsuarios *usuarioLogueado, nodoLibro *listaLibros, int idLibro)
{
    if (usuarioLogueado->datosUsuarios.validosLibrosFavs >= 50) {
        printf("Ya tienes el limite de libros favoritos alcanzado.\n");
        return;
    }

    for (int i = 0; i < usuarioLogueado->datosUsuarios.validosLibrosFavs; i++) {
        if (usuarioLogueado->datosUsuarios.librosFavoritos[i] == idLibro) {
            printf("Este libro ya esta en tus favoritos.\n");
            return;
        }
    }

    usuarioLogueado->datosUsuarios.librosFavoritos[usuarioLogueado->datosUsuarios.validosLibrosFavs] = idLibro;
    usuarioLogueado->datosUsuarios.validosLibrosFavs++;

    printf("Libro agregado a tus favoritos.\n");
}

void mostrarUnNodoLibro(nodoLibro * nodo)
{
    printf("\n Nodo: %p", nodo);
    mostrarUnLibro(nodo->libro);
    printf("\n Nodo->sig: %p", nodo->sig);

}

nodoLibro* altaLdl(nodoLibro* ldl, stLibro libro, stComentario comentario,nodoArbolUsuarios * usuarioLogueado)
{
    nodoLibro* libroABuscar = buscaLibroPorId(ldl, libro.idLibro);
    nodoComentario * listaComentario=NULL;

    if (!libroABuscar) {
        libroABuscar = crearNodoLibros(libro);
        ldl = agregarAlFinalLibro(ldl, libroABuscar);
    }

    nodoComentario* nuevoComentario = crearNodoComentario(libro, listaComentario,usuarioLogueado);

    libroABuscar->dato = agregarAlFinalComentario(libroABuscar->dato, nuevoComentario);

    return ldl;
}

nodoLibro *  archivoToLDL(char nombreArchivo[], nodoLibro * ldl,nodoArbolUsuarios * usuarioLogueado)
{

    FILE * archi = fopen(nombreArchivo, "rb");
    stRegistroLibroComentario aux;

    if(archi)
    {
        while(fread(&aux, sizeof(stRegistroLibroComentario),1,archi)>0)
        {
            stLibro libro = refactorizacionLibro(aux);
            stComentario comentario = refactorizacionComentario(aux);
            ldl = altaLdl(ldl,libro,comentario,usuarioLogueado);
        }

        fclose(archi);
    }
    return ldl;
}

stLibro refactorizacionLibro(stRegistroLibroComentario reg)
{
    stLibro aux;

    aux.idLibro=reg.idLibro;
    strcpy(aux.titulo, reg.titulo);
    strcpy(aux.editorial, reg.editorial);
    strcpy(aux.autor, reg.autor);
    strcpy(aux.categoria, reg.categoria);
    aux.valoracion = reg.valoracion;
    aux.eliminado = reg.libroEliminado;

    return aux;
}


stComentario refactorizacionComentario(stRegistroLibroComentario reg)
{
    stComentario aux;

    aux.idComentario=reg.idComentario;
    aux.idLibro=reg.idLibro;
    aux.idUsuario=reg.idUsuario;
    strcpy(aux.tituloComentario, reg.tituloComentario);
    strcpy(aux.descripcion, reg.descripcion);
    aux.puntaje = reg.puntaje;
    strcpy(aux.fechaComentario, reg.fechaComentario);
    aux.eliminado=reg.comentarioEliminado;

    return aux;
}

void mostrarLDL(nodoLibro *ldl)
{
   while (ldl) {
        mostrarUnLibro(ldl->libro); // Mostrar los detalles del libro
        printf("\n"); // Separar los libros con una línea nueva
        ldl = ldl->sig; // Mover al siguiente nodo
   }
}

int generarIdLibros(nodoLibro * listaLibros)
{
    int id = 0;
    nodoLibro * aux = listaLibros;

    while(aux)
    {
        if(aux->libro.idLibro> id)
        {
            id = aux->libro.idLibro;
        }
        aux = aux->sig;
    }
    return id + 1;
}

void buscarLibrosPorAutor(nodoLibro *listaLibros, char autorBuscar[])
{
    nodoLibro *autor = listaLibros;
    int encontrado = 0;

    printf("\n--- Libros del autor '%s' ---\n", autorBuscar);

    while (autor != NULL) {
        if (strcmpi(autor->libro.autor, autorBuscar) == 0 && autor->libro.eliminado == 0) {
            printf("- Titulo: %s | Autor: %s | Editorial: %s | Valoracion: %.2f\n",
                   autor->libro.titulo,
                   autor->libro.autor,
                   autor->libro.editorial,
                   autor->libro.valoracion);
            encontrado = 1;
        }
        autor = autor->sig;
    }

    if (!encontrado) {
        printf("\nNo se encontraron libros del autor '%s'.\n", autorBuscar);
    }

    printf("-----------------------------------\n");
}


void buscarLibroPorTitulo(nodoLibro *listaLibros, char tituloBuscar[])
{
    nodoLibro *titulo = listaLibros;
    int encontrado = 0;

    while (titulo != NULL && !encontrado) {
        if (strcmpi(titulo->libro.titulo, tituloBuscar) == 0) {
            printf("\nLibro encontrado:\n");
            printf("Titulo: %s\n", titulo->libro.titulo);
            printf("Autor: %s\n", titulo->libro.autor);
            printf("Categoria: %s\n", titulo->libro.categoria);
            printf("Valoracion: %f\n", titulo->libro.valoracion);
            encontrado = 1;
        }
        titulo = titulo->sig;
    }

    if (!encontrado) {
        printf("\nNo se encontro un libro con el titulo: %s\n", tituloBuscar);
    }
}

void buscarLibroPorCategoria(nodoLibro *listaLibros, char categoriaBuscar[])
{
    nodoLibro *actual = listaLibros;
    int encontrado = 0;

    printf("\n--- Libros en la categoria '%s' ---\n", categoriaBuscar);

    while (actual != NULL) {
        if (strcmpi(actual->libro.categoria, categoriaBuscar) == 0 && actual->libro.eliminado == 0) {
            printf("- Titulo: %s | Autor: %s | Editorial: %s | Valoracion: %.2f\n",
                   actual->libro.titulo,
                   actual->libro.autor,
                   actual->libro.editorial,
                   actual->libro.valoracion);
            encontrado = 1;
        }
        actual = actual->sig;
    }

    if (!encontrado) {
        printf("\nNo se encontraron libros en la categoria '%s'.\n", categoriaBuscar);
    }

    printf("-----------------------------------\n");
}

void guardarLibrosEnArchivo(nodoLibro *listaLibros,char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo)
    {
        nodoLibro *aux = listaLibros;

        while (aux != NULL)
        {
            fwrite(&aux->libro, sizeof(stLibro), 1, archivo);
            aux = aux->sig;
        }

    fclose(archivo);
    }
}

nodoLibro * cargarArchivoEnLista(char nombreArchivo[], nodoLibro *listaLibros)
{
    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo) {

    stLibro libro; // Estructura para leer los datos
    while (fread(&libro, sizeof(stLibro), 1, archivo) > 0) {
        if (libro.eliminado == 0) { // Solo cargar usuarios activos
            nodoLibro *nuevoNodo = crearNodoLibros(libro);
            listaLibros = agregarAlFinalLibro(listaLibros, nuevoNodo);
        }
    }

    fclose(archivo);
    }
return listaLibros;
}

