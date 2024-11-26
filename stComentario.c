#include "stComentario.h"


void mostrarComentario(stComentario comentario)
{
    printf("ID Comentario: %d\n", comentario.idComentario);
    printf("ID Libro: %d\n", comentario.idLibro);
    printf("ID Usuario: %d\n", comentario.idUsuario);
    printf("Título: %s\n", comentario.tituloComentario);
    printf("Descripcion: %s\n", comentario.descripcion);
    printf("Puntaje: %d/5\n", comentario.puntaje);
    printf("Fecha: %s\n", comentario.fechaComentario);
    printf("---------------------------------------\n");
}


nodoComentario * inicListaComentario()
{
    return NULL;
}

nodoComentario* crearNodoComentario(stLibro libro, nodoComentario* listaC, nodoArbolUsuarios* usuarioLogueado)
 {
    nodoComentario* nuevo = (nodoComentario*)malloc(sizeof(nodoComentario));
    nuevo->dato = crearComentario(libro, usuarioLogueado->datosUsuarios.idUsuario, listaC);
    nuevo->sig = NULL;

    return nuevo;
}

stComentario crearComentario(stLibro libro, int idUsuario, nodoComentario* listaC)
{
    stComentario nuevo;
    time_t tp;
    time(&tp); // Fecha actual

    printf("\nIngrese el titulo del comentario: ");
    fflush(stdin);
    gets(nuevo.tituloComentario);

    printf("\nDescripcion: ");
    fflush(stdin);
    gets(nuevo.descripcion);

    int puntajeValido = 0;
    do {
        printf("\nPuntuacion (0-5): ");
        if (scanf("%d", &nuevo.puntaje) == 1 && nuevo.puntaje >= 0 && nuevo.puntaje <= 5) {
            puntajeValido = 1;
        } else {
            printf("Entrada invalida. Ingrese un numero entre 0 y 5.\n");
            fflush(stdin);
        }
    } while (!puntajeValido);

    nuevo.eliminado = 0;
    nuevo.idUsuario = idUsuario;
    nuevo.idLibro = libro.idLibro;

    char *fecha = asctime(localtime(&tp));
    fecha[strcspn(fecha, "\n")] = '\0';
    strcpy(nuevo.fechaComentario, fecha);

    nuevo.idComentario = generarIdComentario(listaC);

    return nuevo;
}

int generarIdComentario(nodoComentario * listaComentarios)
{
    int id = 0;
    nodoComentario * aux = listaComentarios;

    while (aux)
    {
        if (aux->dato.idComentario > id)
        {
            id = aux->dato.idComentario;
        }
        aux = aux->sig;
    }
    return id + 1;
}

nodoComentario * buscaComentarioPorId(nodoComentario * listaComentario, int idComentario)
{
    nodoComentario * aBuscar = NULL;
    nodoComentario * aux = listaComentario;

    while(aux && !aBuscar)
    {
        if(aux->dato.idComentario == idComentario)
        {
            aBuscar = aux;
        }
        aux = aux->sig;
    }
    return aBuscar;
}

void mostrarComentariosPorUsuario(nodoComentario *listaComentarios, int idUsuario)
{
    printf("\nComentarios del Usuario ID %d:\n", idUsuario);

    if (listaComentarios == NULL) {
        printf("No hay comentarios para este usuario.\n");
        return;
    }

    nodoComentario *aux = listaComentarios;
    int encontrado = 0;

    while (aux != NULL) {
        if (aux->dato.idUsuario == idUsuario && aux->dato.eliminado == 0) {
            printf("\nComentario ID: %d\n", aux->dato.idComentario);
            printf("Titulo: %s\n", aux->dato.tituloComentario);
            printf("Descripcion: %s\n", aux->dato.descripcion);
            printf("Puntuacion: %d\n", aux->dato.puntaje);
            printf("Fecha: %s\n", aux->dato.fechaComentario);
            encontrado = 1;
        }
        aux = aux->sig;
    }

    if (!encontrado) {
        printf("No hay comentarios activos para este usuario.\n");
    }
}

nodoComentario* buscarUltimoNodoComentario(nodoComentario* listaComentario)
{
    nodoComentario * seg = listaComentario;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoComentario* agregarAlFinalComentario(nodoComentario* listaComentario, nodoComentario* nuevo)
{
    if(!listaComentario)
    {
        listaComentario = nuevo;
    }
    else
    {
        nodoComentario* ultimo = buscarUltimoNodo(listaComentario);
        ultimo->sig = nuevo;
    }

    return listaComentario;
}


void mostrarComentarios(nodoComentario* lista)
{
    nodoComentario* aux = lista;
    while (aux)
    {
        mostrarComentario(aux->dato);
        aux = aux->sig;
    }
}

void mostrarComentariosPorLibro(nodoComentario * listaComentarios, int idLibro)
{
    nodoComentario * aux = listaComentarios;
    int encontrado = 0;

    while (aux)
    {
        if (aux->dato.idLibro == idLibro)
        {
            mostrarComentario(aux->dato);
            encontrado = 1;
        }
        aux = aux->sig;
    }

    if (!encontrado)
    {
        printf("No hay comentarios para este libro.\n");
    }
}

nodoComentario* buscarAeliminar(nodoComentario* listaC, nodoArbolUsuarios* usuarioLogueado, int idComentario)
{
    nodoComentario* actual = listaC;
    nodoComentario* anterior = NULL;

    while (actual) {
        if (actual->dato.idUsuario == usuarioLogueado->datosUsuarios.idUsuario &&
            actual->dato.idComentario == idComentario) {

            if (anterior) {
                anterior->sig = actual->sig;
            } else {
                listaC = actual->sig;
            }
            free(actual);
            return listaC;
        }

        anterior = actual;
        actual = actual->sig;
    }

    return listaC;
}

nodoComentario* buscarComentarioPorId(nodoComentario* lista, int idComentario)
{
    nodoComentario* actual = lista;

    while (actual != NULL) {
        if (actual->dato.idComentario == idComentario) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

void guardarComentariosEnArchivo(nodoComentario* listaC, char nombreArchivo[])
{
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo)
        {
        nodoComentario* actual = listaC;
        while (actual) {
            fwrite(&(actual->dato), sizeof(stComentario), 1, archivo);
            actual = actual->sig;
        }
        fclose(archivo);
        printf("Comentarios guardados exitosamente en archivo.\n");
    } else {
        printf("Error al abrir el archivo para guardar los comentarios.\n");
    }
}

nodoComentario* cargarComentariosDesdeArchivo(char nombreArchivo[])
 {
    FILE* archivo = fopen(nombreArchivo, "rb");
    nodoComentario* listaC = NULL;

    if (archivo)
        {
        stComentario comentario;
        while (fread(&comentario, sizeof(stComentario), 1, archivo) > 0) {
            nodoComentario* nuevoNodo = (nodoComentario*)malloc(sizeof(nodoComentario));
            nuevoNodo->dato = comentario;
            nuevoNodo->sig = NULL;
            listaC = agregarAlFinalComentario(listaC, nuevoNodo);
        }
        fclose(archivo);
        printf("Comentarios cargados exitosamente.\n");
    }
    return listaC;
}

void mostrarArchivoComentarios(char archivoComentario[])
{
    FILE * archi=fopen(archivoComentario,"rb");
    stComentario aux;

    if(archi)
    {
        while(fread(&aux,sizeof(stComentario),1,archi))
        {
            mostrarComentario(aux);
        }
        fclose(archi);
    }
}
