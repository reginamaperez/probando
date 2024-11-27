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
        fflush(stdin); // No siempre limpia correctamente
        while (getchar() != '\n'); // Limpiar buffer manualmente
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

nodoComentario* crearNodoComentario(stLibro libro, nodoComentario* listaC, nodoArbolUsuarios* usuarioLogueado) {
    nodoComentario* nuevo = (nodoComentario*)malloc(sizeof(nodoComentario));
    if (!nuevo) {
        return NULL;
    }

    nuevo->dato = crearComentario(libro, usuarioLogueado->datosUsuarios.idUsuario, listaC);
    nuevo->sig = NULL;
    return nuevo;
}

int generarIdComentario(nodoComentario * listaComentarios)
{
    int id = 0;
    nodoComentario * aux = listaComentarios;

    if (!aux) {
        printf("DEBUG: Lista de comentarios vacía. Asignando ID 1.\n");
        return 1;
    }

    while (aux)
    {
        if (aux->dato.idComentario > id)
        {
            id = aux->dato.idComentario;
        }
        aux = aux->sig;
    }

    printf("DEBUG: ID generado: %d\n", id + 1);
    return id + 1;
}
/*
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

nodoComentario *buscaComentarioPorId(nodoComentario *lista, int idComentario) {
    nodoComentario *actual = lista;

    while (actual) {
        printf("DEBUG: Revisando comentario con ID: %d\n", actual->dato.idComentario);
        if (actual->dato.idComentario == idComentario) {
            return actual; // Devuelve el nodo encontrado
        }
        actual = actual->sig;
    }

    return NULL; // No se encontró el comentario
}
*/
nodoComentario *buscaComentarioPorId(nodoComentario *lista, int idComentario) {
    nodoComentario *actual = lista;
    while (actual) {
        if (actual->dato.idComentario == idComentario) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL; // No encontrado
}

void mostrarComentariosPorUsuario(nodoComentario *lista, int idUsuario) {
    nodoComentario *actual = lista;
    int contador = 0;

    while (actual) {
        if (actual->dato.idUsuario == idUsuario) {
            printf("ID: %d - Comentario: %s\n", actual->dato.idComentario, actual->dato.descripcion);
            contador++;
        }
        actual = actual->sig;
    }

    if (contador == 0) {
        printf("No tienes comentarios.\n");
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

nodoComentario* agregarAlFinalComentario(nodoComentario* listaComentario, nodoComentario* nuevo) {
    if (!listaComentario) {
        // La lista está vacía, el nuevo nodo es el primero
        listaComentario = nuevo;
    } else {
        nodoComentario* ultimo = listaComentario;
        while (ultimo->sig != NULL) {
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevo; // Conectamos el nuevo nodo al final
    }
    return listaComentario;
}


void mostrarComentariosPorLibro(nodoComentario *listaComentarios, int idLibro)
{
    nodoComentario *aux = listaComentarios;
    int encontrados = 0;

    while (aux != NULL) {
        if (aux->dato.idLibro == idLibro) {
            printf("Comentario de %s: %s\n", aux->dato.idUsuario, aux->dato.descripcion);
            printf("Puntuacion: %d\n", aux->dato.puntaje);
            encontrados++;
        }
        aux = aux->sig;
    }

    if (encontrados == 0) {
        printf("No hay comentarios para este libro.\n");
    }
}
/*
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
*/

nodoComentario* buscarAeliminar(nodoComentario* lista, nodoArbolUsuarios* usuarioLogueado, int idComentario) {
    nodoComentario* actual = lista;
    nodoComentario* anterior = NULL;

    while (actual) {
        if (actual->dato.idComentario == idComentario &&
            actual->dato.idUsuario == usuarioLogueado->datosUsuarios.idUsuario) {
            // Encontrado
            if (anterior) {
                anterior->sig = actual->sig; // Salta el nodo
            } else {
                lista = actual->sig; // Eliminar cabeza
            }
            free(actual); // Libera memoria
            return lista;
        }
        anterior = actual;
        actual = actual->sig;
    }
    printf("DEBUG: Comentario no encontrado o no pertenece al usuario.\n");
    return lista;
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

int comentarioExistente(nodoComentario* lista, int idLibro, nodoArbolUsuarios* usuario)
{
    nodoComentario* aux = lista;
    while (aux)
    {
        if (aux->dato.idLibro == idLibro && aux->dato.idUsuario == usuario->datosUsuarios.idUsuario)
        {
            return 1; // Ya existe un comentario
        }
        aux = aux->sig;
    }
    return 0; // No existe un comentario
}

void mostrarComentarios(nodoComentario* listaComentarios)
{
    if (listaComentarios == NULL) {
        printf("No hay comentarios disponibles.\n");
        return;
    }

    nodoComentario* aux = listaComentarios;
    while (aux != NULL) {
        printf("\nComentario: %s\n", aux->dato.tituloComentario); // Asumiendo que 'titulo' es el campo del comentario
        printf("Descripcion: %s\n", aux->dato.descripcion);
        printf("Puntuacion: %d\n", aux->dato.puntaje);

        // Mostrar libro relacionado
        printf("Libro: %d\n", aux->dato.idLibro);

        // Mostrar el usuario que hizo el comentario
        printf("Usuario: %d\n", aux->dato.idUsuario);

        aux = aux->sig;
    }
}

void editarComentario(nodoComentario *comentario)
{
    printf("\nEditar Comentario:\n");
    printf("Título actual: %s\n", comentario->dato.tituloComentario);
    printf("Descripcion actual: %s\n", comentario->dato.descripcion);

    printf("\nIngrese el nuevo título: ");
    fflush(stdin);
    gets(comentario->dato.tituloComentario);  // Si prefieres usar gets, como mencionaste

    printf("\nIngrese la nueva descripción: ");
    fflush(stdin);
    gets(comentario->dato.descripcion);  // Si prefieres usar gets

    // Puedes agregar más validaciones o cambios aquí
    printf("Comentario editado exitosamente.\n");
}
/*
void guardarComentariosEnArchivo(nodoComentario* listaC, char nombreArchivo[]) {
    if (!listaC) {
        printf("DEBUG: Lista de comentarios está vacía. Nada que guardar.\n");
        return;
    }

    FILE* archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        printf("ERROR: No se pudo abrir el archivo para guardar comentarios.\n");
        return;
    }

    nodoComentario* actual = listaC;
    while (actual) {
        fwrite(&(actual->dato), sizeof(stComentario), 1, archivo);
        printf("DEBUG: Guardando comentario con ID %d.\n", actual->dato.idComentario);
        actual = actual->sig;
    }

    fclose(archivo);
    printf("DEBUG: Comentarios guardados correctamente.\n");
}

*/
void guardarComentariosEnArchivo(nodoComentario* listaC, char nombreArchivo[]) {
    if (!listaC) {
        printf("DEBUG: Lista de comentarios está vacía. Nada que guardar.\n");
        return;
    }

    FILE* archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        perror("ERROR al abrir archivo para guardar comentarios");
        return;
    }

    nodoComentario* actual = listaC;
    while (actual) {
        if (fwrite(&(actual->dato), sizeof(stComentario), 1, archivo) != 1) {
            perror("ERROR al escribir en el archivo");
            fclose(archivo);
            return;
        }
        printf("DEBUG: Guardando comentario con ID %d.\n", actual->dato.idComentario);
        actual = actual->sig;
    }

    fclose(archivo);
    printf("DEBUG: Comentarios guardados correctamente.\n");
}

nodoComentario* cargarComentariosDesdeArchivo(char nombreArchivo[])
 {
    FILE* archivo = fopen(nombreArchivo, "rb");
    nodoComentario* listaC = NULL;

    if (archivo)
        {
        stComentario comentario;
        while (fread(&comentario, sizeof(stComentario), 1, archivo) > 0)
        {
        nodoComentario* nuevoNodo = (nodoComentario*)malloc(sizeof(nodoComentario));
            if (nuevoNodo) {
            nuevoNodo->dato = comentario;
            nuevoNodo->sig = NULL;
            listaC = agregarAlFinalComentario(listaC, nuevoNodo);
            } else {
            printf("Error: No se pudo asignar memoria para un nodo de comentario.\n");
        }
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
/*
void menuComentarios(char *archivoComentarios, nodoArbolUsuarios *usuarioLogueado)
{
    nodoComentario *listaComentarios = cargarComentariosDesdeArchivo(archivoComentarios);
    if (listaComentarios) {
    printf("Comentarios cargados correctamente.\n");
    } else {
    printf("No se encontraron comentarios.\n");
    }

    printf("\nTus comentarios:\n");
    mostrarComentariosPorUsuario(listaComentarios, usuarioLogueado->datosUsuarios.idUsuario);

    // Opciones para editar o eliminar un comentario
    if (listaComentarios) {
        int idComentario;
        printf("\nIngrese el ID del comentario que desea editar/eliminar: ");
        scanf("%d", &idComentario);

        nodoComentario *comentarioEncontrado = buscaComentarioPorId(listaComentarios, idComentario);
        if (comentarioEncontrado && comentarioEncontrado->dato.idUsuario == usuarioLogueado->datosUsuarios.idUsuario) {
            int opcionAccion;
            printf("\n1. Editar comentario\n");
            printf("2. Eliminar comentario\n");
            printf("3. Volver\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcionAccion);

            switch (opcionAccion) {
                case 1:
                    editarComentario(comentarioEncontrado); // Edita el comentario
                    break;
                case 2:
                    listaComentarios = buscarAeliminar(listaComentarios, usuarioLogueado, idComentario);
                    printf("Comentario eliminado correctamente.\n");
                    break;
                case 3:
                    printf("Volviendo al menu...\n");
                    break;
                default:
                    printf("Opcion no valida.\n");
            }
        } else {
            printf("No se encontro el comentario o no es tuyo.\n");
        }
    } else {
        printf("No hay comentarios cargados.\n");
    }

    // Guardar los cambios en el archivo
    guardarComentariosEnArchivo(archivoComentarios, listaComentarios);

    system("pause");
    system("cls");
}

*/

void menuComentarios(char *archivoComentarios, nodoArbolUsuarios *usuarioLogueado) {
    nodoComentario *listaComentarios = cargarComentariosDesdeArchivo(archivoComentarios);

    if (listaComentarios) {
        printf("Comentarios cargados correctamente.\n");
    } else {
        printf("DEBUG: No se encontraron comentarios. Inicia el programa sin comentarios cargados.\n");
    }

    printf("\nTus comentarios:\n");
    mostrarComentariosPorUsuario(listaComentarios, usuarioLogueado->datosUsuarios.idUsuario);

    // Opciones para editar o eliminar un comentario
    if (listaComentarios) {
        int idComentario;
        printf("\nIngrese el ID del comentario que desea editar/eliminar: ");
        if (scanf("%d", &idComentario) != 1) {
            printf("Entrada no valida. Seleccione un numero.\n");
            fflush(stdin);
            return;
        }

        nodoComentario *comentarioEncontrado = buscaComentarioPorId(listaComentarios, idComentario);
        if (comentarioEncontrado && comentarioEncontrado->dato.idUsuario == usuarioLogueado->datosUsuarios.idUsuario) {
            int opcionAccion;
            printf("\n1. Editar comentario\n");
            printf("2. Eliminar comentario\n");
            printf("3. Volver\n");
            printf("Seleccione una opcion: ");
            if (scanf("%d", &opcionAccion) != 1) {
                printf("Entrada no valida. Seleccione un numero.\n");
                fflush(stdin);
                return;
            }

            switch (opcionAccion) {
                case 1:
                    editarComentario(comentarioEncontrado); // Edita el comentario
                    printf("Comentario editado correctamente.\n");
                    break;
                case 2:
                    listaComentarios = buscarAeliminar(listaComentarios, usuarioLogueado, idComentario);
                    printf("Comentario eliminado correctamente.\n");
                    break;
                case 3:
                    printf("Volviendo al menu...\n");
                    break;
                default:
                    printf("Opcion no valida.\n");
            }
        } else {
            printf("No se encontro el comentario o no es tuyo.\n");
        }
    } else {
        printf("No hay comentarios cargados.\n");
    }

    // Guardar los cambios en el archivo
    guardarComentariosEnArchivo(listaComentarios, archivoComentarios);

    system("pause");
    system("cls");
}
