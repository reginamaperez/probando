#include "stLibro.h"


void mostrarUnLibro(stLibro libro)
{
    printf("\n -----------------------\n");
    printf ("ID Libro: %i\n", libro.idLibro);
    printf ("Titulo: %s\n", libro.titulo);
    printf("Editorial: %s\n", libro.editorial);
    printf("Autor: %s\n", libro.autor);
    printf("Categoria: %s\n", libro.categoria);
    printf("Valoracion: %f\n", libro.valoracion);
    printf("\n -----------------------\n");
}

stLibro cargarUnLibro()
{
    stLibro libro;

    printf ("Ingrese Titulo del Libro:\n");
    fflush(stdin);
    gets(libro.titulo);
    printf ("Ingrese la editorial:\n");
    fflush(stdin);
    gets(libro.editorial);
    printf ("Ingrese el autor del Libro:\n");
    fflush(stdin);
    gets(libro.autor);
    printf ("Ingrese la categoria:\n");
    fflush(stdin);
    gets(libro.categoria);

    return libro;
}


