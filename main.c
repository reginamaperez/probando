#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbolUsuarios.h"
#include "stCelda.h"
#include "stComentario.h"
#include "stLibro.h"
#include "menu.h"

void mostrarArchivoUsuario(char archivoUsuarios[]);

int main()
{
    printf("\n");
    printf("\n");

    printf("-----      ---       ---     --    --  --      --     ---       -----  -------   ------   ------ \n");
    printf("--  --   --   --   --   --   --   --   ---    ---    --  --     --        --     --       --   --    \n");
    printf("----    --    --  --     --  ----      --  --  --   -- -- --    -----     --     ----     -----     \n");
    printf("--  --   --   --   --   --   --   --   --      --   --     --       --    --     --       --    --      \n");
    printf("-----      ---       ---     --    --  --      --  --       --  -----     --     ------   --    -- \n");

    printf("\n");
    printf("\n");

    printf("---------------------------------------- TU BIBLIOTECA PREFERIDA -----------------------------------------------\n");






    srand(time(NULL));
    //cargarLibrosRandom("archivoLibros.dat");
    //cargarUsuariosRandom("archivoUsuarios.dat");
   // printf("ARCHIVO USUARIOS:\n");
    //mostrarArchivoUsuario("archivoUsuarios.dat");
    //mostrarArchivoLibros("archivoLibros.dat");

    nodoArbolUsuarios *arbolUsuarios = inicArbol();
    nodoLibro * ldl=inicListaLibros();

    arbolUsuarios= cargarUsuariosDesdeArchivo(arbolUsuarios,"archivoUsuarios.dat");
    ldl= cargarArchivoEnLista("archivoLibros.dat", ldl);

/*
    printf("ARBOL DE USUARIOS ----------------\n");
    mostrarArbol(arbolUsuarios);
    printf("LISTA DE LIBROS:\n");
    mostrarListaLibros(ldl);
*/
    menu(&arbolUsuarios,&ldl);

    return 0;
}

/// CARGA ALEATORIA DE ARCHIVOS

void generarStringAleatorio(char *str, int longitud)
{
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < longitud; i++)
    {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[longitud] = '\0';
}

void cargarLibrosRandom(char archivoLibros[])
{
    FILE *archivo = fopen(archivoLibros, "wb");
    if (!archivo)
    {
        printf("Error al abrir el archivo de libros.\n");
        return;
    }

    stLibro libro;
    const char *categorias[] = {"Ficcion", "Ciencia ficcion", "Ciencia", "Arte", "Historia"};
    const char *editoriales[] = {"Editorial A", "Editorial B", "Editorial C"};
    const char *autores[] = {"Autor X", "Autor Y", "Autor Z"};

    for (int i = 1; i <= 50; i++)
    {
        libro.idLibro = i;
        generarStringAleatorio(libro.titulo, 10);
        strcpy(libro.editorial, editoriales[rand() % 3]);
        strcpy(libro.autor, autores[rand() % 3]);
        strcpy(libro.categoria, categorias[rand() % 5]);
        libro.valoracion = (float)(rand() % 51) / 10; // Entre 0.0 y 5.0
        libro.eliminado = 0; // Activo

        fwrite(&libro, sizeof(stLibro), 1, archivo);
    }

    fclose(archivo);
}

void cargarUsuariosRandom(char archivoUsuarios[])
{
    FILE *archivo = fopen(archivoUsuarios, "wb");
    if (!archivo)
    {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }

    stUsuario usuario;
    const char *generos = "FM";
    const char *ciudades[] = {"Buenos Aires", "Cordoba", "Rosario", "Mendoza"};
    const char *paises[] = {"Argentina", "Chile", "Uruguay"};

    for (int i = 1; i <= 20; i++)
    {
        usuario.idUsuario = i;
        sprintf(usuario.email, "usuario%d@mail.com", i);
        sprintf(usuario.password, "pass%d", i);
        sprintf(usuario.username, "user%d", i);
        usuario.esAdmin = (i == 1); // Solo el primer usuario es admin
        usuario.genero = generos[rand() % 2];
        sprintf(usuario.fechaNacimiento, "%02d-%02d-%04d", rand() % 28 + 1, rand() % 12 + 1, rand() % 30 + 1990);
        usuario.validosLibrosFavs = 0; // Sin favoritos al inicio
        usuario.eliminado = 0; // Activo
        sprintf(usuario.dni, "%08d", rand() % 100000000);

        // Domicilio
        generarStringAleatorio(usuario.domicilio.calle, 8);
        usuario.domicilio.altura = rand() % 5000 + 1;
        usuario.domicilio.cp = rand() % 10000;
        strcpy(usuario.domicilio.ciudad, ciudades[rand() % 4]);
        strcpy(usuario.domicilio.localidad, "Localidad");
        strcpy(usuario.domicilio.pais, paises[rand() % 3]);

        fwrite(&usuario, sizeof(stUsuario), 1, archivo);
    }

    fclose(archivo);
}

void mostrarArchivoUsuario(char archivoUsuarios[])
{
    FILE * archi=fopen(archivoUsuarios,"rb");
    stUsuario aux;

    if(archi)
    {
        while(fread(&aux,sizeof(stUsuario),1,archi))
        {
            mostrarUnUsuario(aux);
        }
        fclose(archi);
    }
}

void mostrarArchivoLibros(char archivoLibros[])
{
    FILE * archi=fopen(archivoLibros,"rb");
    stLibro aux;

    if(archi)
    {
        while(fread(&aux,sizeof(stLibro),1,archi))
        {
            mostrarUnLibro(aux);
        }
        fclose(archi);
    }
}

