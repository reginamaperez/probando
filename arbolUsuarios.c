#include "arbolUsuarios.h"

void mostrarUnUsuario(stUsuario usuario)
{

    printf("\n -----------------------\n");
    printf("ID Usuario: %d\n", usuario.idUsuario);
    printf("Username: %s\n", usuario.username);
    printf("Email: %s\n", usuario.email);
    printf("DNI: %s\n", usuario.dni);
    printf("Genero: %c\n", usuario.genero);
    printf("Fecha de Nacimiento: %s\n", usuario.fechaNacimiento);
    printf("Domicilio: %s %d\n", usuario.domicilio.calle, usuario.domicilio.altura);
    printf("Codigo Postal: %d\n", usuario.domicilio.cp);
    printf("Ciudad: %s\n", usuario.domicilio.ciudad);
    printf("Pais: %s\n", usuario.domicilio.pais);

    printf("\n -----------------------\n");
}

nodoArbolUsuarios * inicArbol()
{
    return NULL;
}

nodoArbolUsuarios * crearNodoArbol(stUsuario usuario)
{
    nodoArbolUsuarios * nuevo= (nodoArbolUsuarios*)malloc(sizeof(nodoArbolUsuarios));
    nuevo->datosUsuarios=usuario;
    nuevo->izq=NULL;
    nuevo->der=NULL;

    return nuevo;
}

nodoArbolUsuarios* insertarEnArbol(nodoArbolUsuarios *arbol, nodoArbolUsuarios *nuevoNodo)
{
    if (arbol == NULL)
    {
        return nuevoNodo;
    }

    if (nuevoNodo->datosUsuarios.idUsuario < arbol->datosUsuarios.idUsuario)
    {
        arbol->izq = insertarEnArbol(arbol->izq, nuevoNodo);  // Insertar en el subárbol izquierdo
    }
    else
    {
        arbol->der = insertarEnArbol(arbol->der, nuevoNodo);  // Insertar en el subárbol derecho
    }

    return arbol;
}

void mostrarArbol(nodoArbolUsuarios * arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izq);
        mostrarUnUsuario(arbol->datosUsuarios);
        mostrarArbol(arbol->der);
    }
}

void mostrarUsuariosActivos(nodoArbolUsuarios *arbol)
{
    if (arbol)
    {
        mostrarUsuariosActivos(arbol->izq);
        if (arbol->datosUsuarios.eliminado == 0)
        {
            mostrarUnUsuario(arbol->datosUsuarios);
        }
        mostrarUsuariosActivos(arbol->der);
    }
}

void mostrarUsuariosInactivos(nodoArbolUsuarios *arbol)
{
    if (arbol)
    {
        mostrarUsuariosInactivos(arbol->izq);
        if (arbol->datosUsuarios.eliminado == 1)
        {
            mostrarUnUsuario(arbol->datosUsuarios);
        }
        mostrarUsuariosInactivos(arbol->der);
    }
}

void elegirArbolAVer(nodoArbolUsuarios *arbol)
{
    if (!arbol) {
        printf("\nEl arbol esta vacío. No hay usuarios que mostrar.\n");
        return;
    }

    char opcion;
    printf("Elija arbol a ver: A- Todos los usuarios B- Usuarios activos C- Usuarios inactivos\n");
    fflush(stdin);
    scanf(" %c", &opcion);
    opcion = toupper(opcion);

    switch (opcion) {
        case 'A':
            mostrarArbol(arbol);
            break;
        case 'B':
            mostrarUsuariosActivos(arbol);
            break;
        case 'C':
            mostrarUsuariosInactivos(arbol);
            break;
        default:
            printf("\nOpcion invalida. Intente nuevamente.\n");
            break;
    }
}

nodoArbolUsuarios *buscarUsuarioPorDni(nodoArbolUsuarios *arbol, char dni[20])
{
    if (!arbol)
        return NULL;

    if (strcmp(arbol->datosUsuarios.dni, dni) == 0)
    {
        printf("Usuario encontrado!\n");
        return arbol;
    }
    else if (strcmp(dni, arbol->datosUsuarios.dni) < 0)
    {
        return buscarUsuarioPorDni(arbol->izq, dni);
    }
    else
    {
        return buscarUsuarioPorDni(arbol->der, dni);
    }
}

nodoArbolUsuarios *buscarUsuarioPorEmail(nodoArbolUsuarios *arbol, char email[100])
{
    if (arbol == NULL)
    {
        return NULL;
    }

    if (strcmp(arbol->datosUsuarios.email, email) == 0)
    {
        return arbol;
    }
    if (strcmp(email, arbol->datosUsuarios.email) < 0)
    {
        return buscarUsuarioPorEmail(arbol->izq, email);
    }
    else
    {
        return buscarUsuarioPorEmail(arbol->der, email);
    }
}

nodoArbolUsuarios *buscarUsuarioPorUsername(nodoArbolUsuarios *arbol, char username[20])
{
    if (!arbol)
        return NULL;

    if (strcmpi(arbol->datosUsuarios.username, username) == 0)
    {
        printf("Usuario encontrado!\n");
        return arbol;
    }

    nodoArbolUsuarios *izq = buscarUsuarioPorUsername(arbol->izq, username);
    if (izq)
        return izq;

    return buscarUsuarioPorUsername(arbol->der, username);
}

nodoArbolUsuarios *bajaDelUsuario(nodoArbolUsuarios *arbol) {
    if (!arbol) {
        printf("El árbol está vacío.\n");
        return arbol;
    }

    char opcion;
    char dato[100];
    nodoArbolUsuarios *usuario = NULL;

    printf("Buscar usuario segun: A- DNI | B- EMAIL | C- USERNAME\n");
    printf("Ingrese una opcion: ");
    fflush(stdin);
    scanf(" %c", &opcion);

    switch (tolower(opcion)) {
        case 'a':
            printf("Ingrese DNI:\n");
            fflush(stdin);
            gets(dato);
            usuario = buscarUsuarioPorDni(arbol, dato);
            break;
        case 'b':
            printf("Ingrese Email:\n");
            fflush(stdin);
            gets(dato);
            usuario = buscarUsuarioPorEmail(arbol, dato);
            break;
        case 'c':
            printf("Ingrese Username:\n");
            fflush(stdin);
            gets(dato);
            usuario = buscarUsuarioPorUsername(arbol, dato);
            break;
        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            return arbol;
    }

    if (usuario) {
        usuario->datosUsuarios.eliminado = 1;
        printf("Usuario '%s' dado de baja exitosamente.\n", usuario->datosUsuarios.username);
    } else {
        printf("No se encontro el usuario con los datos proporcionados.\n");
    }

    return arbol;
}

void modificarDireccionUsuario(nodoArbolUsuarios *arbol)
{
    char opcion;
    char dato[100];
    nodoArbolUsuarios *usuario = NULL;

    printf("Buscar usuario segun: A- DNI B- EMAIL\n");
    fflush(stdin);
    scanf("%c", &opcion);

    if (opcion == 'A' || opcion == 'a')
    {
        printf("Ingrese DNI:\n");
        fflush(stdin);
        gets(dato);
        usuario = buscarUsuarioPorDni(arbol, dato);
    }
    else if (opcion == 'B' || opcion == 'b')
    {
        printf("Ingrese Email:\n");
        fflush(stdin);
        gets(dato);
        usuario = buscarUsuarioPorEmail(arbol, dato);
    }
    else
    {
        printf("Opcion invalida\n");
    }

    if (usuario)
    {
        printf("Modificar domicilio:\n");
        printf("Ingrese nueva calle:\n");
        fflush(stdin);
        gets(usuario->datosUsuarios.domicilio.calle);

        printf("Ingrese nueva altura:\n");
        scanf("%d", &usuario->datosUsuarios.domicilio.altura);

        printf("Ingrese nuevo codigo postal:\n");
        scanf("%d", &usuario->datosUsuarios.domicilio.cp);

        printf("Ingrese nueva localidad:\n");
        fflush(stdin);
        gets(usuario->datosUsuarios.domicilio.localidad);

        printf("Ingrese ciudad:\n");
        fflush(stdin);
        gets(usuario->datosUsuarios.domicilio.ciudad);

        printf("Ingrese nuevo pais:\n");
        fflush(stdin);
        gets(usuario->datosUsuarios.domicilio.pais);

        printf("Usuario modificado exitosamente.\n");
    }
    else
    {
        printf("Usuario no encontrado.\n");
    }
}

nodoArbolUsuarios * modificarUsername (nodoArbolUsuarios * arbol)
{
    nodoArbolUsuarios * aux = NULL;
    char opcion;
    char dato [100];
    char nuevoUser[20];

    if (arbol)
    {
        printf("\nBuscar usuario a modificar segun: A-DNI B- EMAIL\n");
        fflush(stdin);
        scanf (" %c",&opcion);

        if (opcion == 'A' || opcion == 'a')
        {
            printf("Ingrese DNI:\n");
            fflush(stdin);
            gets(dato);
            aux = buscarUsuarioPorDni(arbol, dato);
        }
        else if (opcion == 'B' || opcion == 'b')
        {
             printf("Ingrese Mail:\n");
            fflush(stdin);
            gets(dato);
            aux = buscarUsuarioPorEmail(arbol,dato);
        }
        else
        {
            printf ("\nOpcion invalida\n");
        }

        if (aux!=NULL)
        {

            printf ("\nIngrese el nuevo Username:\n");
            fflush (stdin);
            gets (nuevoUser);
            strcpy(aux->datosUsuarios.username, nuevoUser);
            printf ("\nUsuario modificado:\n");
            mostrarUnUsuario(aux->datosUsuarios);
        }
        else
        {
             printf ("\nEl usuario que desea modificar no se encuentra en el sistema\n");
        }

    }
    return arbol;
}

stUsuario cargarContraseniaRegistro(stUsuario usuario)
{
    char contrasenia[30];
    char confirmacion[30];

    do
    {
        printf("Ingrese su nueva contrasenia:  \n");
        fflush(stdin);
        gets(contrasenia);

        printf("Vuelva a ingresar su contrasenia \n");
        fflush(stdin);
        gets(confirmacion);

        if (!validarContrasenia(contrasenia, confirmacion))
        {
            printf("Las contrasenias no coinciden\n");
        }
        else if (!validarMayusculaMinuscula(contrasenia))
        {
            printf("La contrasenia debe tener al menos una mayuscula y una minuscula\n");
        }

    } while (!validarContrasenia(contrasenia, confirmacion) || !validarMayusculaMinuscula(contrasenia));

    strcpy(usuario.password, contrasenia);

    return usuario;
}

int obtenerMayorUsuario(nodoArbolUsuarios *arbolUsuarios)
{
    if (arbolUsuarios == NULL)
    {
        return 0;
    }

    int maxIzq = obtenerMayorUsuario(arbolUsuarios->izq);
    int maxDer = obtenerMayorUsuario(arbolUsuarios->der);

    int maxActual = arbolUsuarios->datosUsuarios.idUsuario;
    return (maxIzq > maxActual ? maxIzq : maxActual) > maxDer ?
           (maxIzq > maxActual ? maxIzq : maxActual) : maxDer;
}

int generarIdUsuarios(nodoArbolUsuarios *arbolUsuarios) {
    return obtenerMayorUsuario(arbolUsuarios) + 1;
}

int verificarUsuarioExistente(nodoArbolUsuarios *arbol, char userName[]) {
    if (!arbol) return 0;

    if (strcmp(arbol->datosUsuarios.username, userName) == 0) {
        return 1;
    }
    int encontradoEnIzquierda = verificarUsuarioExistente(arbol->izq, userName);
    int encontradoEnDerecha = verificarUsuarioExistente(arbol->der, userName);

    return encontradoEnIzquierda || encontradoEnDerecha;
}


int verificarEmailExistente(nodoArbolUsuarios *arbol, char email[]) {
    if (!arbol) return 0;

    if (strcmp(arbol->datosUsuarios.email, email) == 0) {
        return 1;
    }
    int encontradoEnIzquierda = verificarEmailExistente(arbol->izq, email);
    int encontradoEnDerecha = verificarEmailExistente(arbol->der, email);

    return encontradoEnIzquierda || encontradoEnDerecha;
}

int verificarDniExistente(nodoArbolUsuarios *arbolUsuarios, char *dni)
{
    if (arbolUsuarios == NULL)
    {
        return 0;
    }
    if (strcmp(arbolUsuarios->datosUsuarios.dni, dni) == 0)
    {
        return 1;
    }

    if (strcmp(dni, arbolUsuarios->datosUsuarios.dni) < 0)
    {
        return verificarDniExistente(arbolUsuarios->izq, dni);
    } else {
        return verificarDniExistente(arbolUsuarios->der, dni);
    }
}

void guardarUsuariosEnArchivo(nodoArbolUsuarios *arbolUsuarios, char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo)
    {
        guardarEnArchivoRec(arbolUsuarios, archivo);
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para guardar.\n");
    }
}

void guardarEnArchivoRec(nodoArbolUsuarios *arbolUsuarios, FILE *archivo)
{
    if (arbolUsuarios != NULL)
    {
        guardarEnArchivoRec(arbolUsuarios->izq, archivo);
        fwrite(&arbolUsuarios->datosUsuarios, sizeof(stUsuario), 1, archivo);
        guardarEnArchivoRec(arbolUsuarios->der, archivo);
    }
}

nodoArbolUsuarios * cargarUsuariosDesdeArchivo(nodoArbolUsuarios *arbolUsuarios, char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi) {
        stUsuario usuario; // Estructura temporal para leer registros del archivo
        while (fread(&usuario, sizeof(stUsuario), 1, archi)) {
            nodoArbolUsuarios *nuevoNodo = crearNodoArbol(usuario); // Crear un nodo del árbol con los datos del usuario
            arbolUsuarios = insertarEnArbol(arbolUsuarios, nuevoNodo); // Insertar el nodo en el árbol
        }
        fclose(archi);
        }
    return arbolUsuarios;
}
