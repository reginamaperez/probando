#include "menu.h"


int menu(nodoArbolUsuarios ** arbolUsuarios, nodoLibro ** listaLibros)
{
    int opcion = 0;

    do
    {
        mostrarMenuPrincipal();
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            system("cls");
            registrarUsuario(arbolUsuarios);
            guardarUsuariosEnArchivo(*arbolUsuarios,"archivoUsuarios.dat");
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            iniciarSesion(*arbolUsuarios,*listaLibros);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            guardarUsuariosEnArchivo(*arbolUsuarios,"archivoUsuarios.dat");
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida.\n");
        }
    }
    while (opcion != 3);

    return 0;
}

void mostrarMenuPrincipal()
{
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar sesion\n");
    printf("3. Salir\n");
}

void registrarUsuario(nodoArbolUsuarios **arbolUsuarios)
{
    stUsuario usuario;
    char username[20];
    char email[100];
    char password[20];
    char confirmPassword[20];
    char alturaStr[10];
    char opcionStr[10];
    int rta = 0;
    int opcion = 0;

    do
    {
        printf("Ingrese su Nombre de Usuario: ");
        fflush(stdin);
        gets(username);

        rta = verificarUsuarioExistente(*arbolUsuarios, username);

        if (rta == 1)
        {
            printf("El nombre de usuario ya existe.\n");
            printf("1. Intentar de nuevo\n");
            printf("2. Salir\n");
            printf("Elija una opcion: ");
            fflush(stdin);
            gets(opcionStr);
            opcion = atoi(opcionStr);
            if (opcion == 2)
            {
                printf("Registro cancelado.\n");
                return;
            }
        }
    }
    while (rta == 1);
    strcpy(usuario.username, username);

    do
    {
        printf("Ingrese su email: ");
        fflush(stdin);
        gets(email);

        if (!validarMail(email))
        {
            printf("Formato de email invalido. El mismo debe contener un '@' y un '.com'. Intetelo nuevamente.\n");
            continue; // Vuelve a pedir el email
        }

        rta = verificarEmailExistente(*arbolUsuarios, email);

        if (rta == 1)
        {
            printf("El email ya se encuentra registrado. Intentelo nuevamente.\n");
        }
    }
    while (!validarMail(email) || rta == 1);
    strcpy(usuario.email, email);

    pedirPassword(password, confirmPassword);
    strcpy(usuario.password, password);

    do
    {
        printf("Ingrese su genero (M/F/O): ");
        fflush(stdin);
        scanf("%c",&usuario.genero);

        if (!validarGenero(usuario.genero))
        {
            printf("Genero invalido. Ingrese M (Masculino), F (Femenino) u O (Otro).\n");
        }
    }
    while (!validarGenero(usuario.genero));

    do
    {
        printf("Ingrese su fecha de nacimiento (DD/MM/YYYY): ");
        fflush(stdin);
        gets(usuario.fechaNacimiento);

        if (!validarFechaNacimiento(usuario.fechaNacimiento))
        {
            printf("Fecha invalida. Asegurese de usar el formato DD/MM/YYYY y que sea una fecha valida.\n");
        }
    }
    while (!validarFechaNacimiento(usuario.fechaNacimiento));

    do
    {
        printf("Ingrese su DNI: ");
        fflush(stdin);
        gets(usuario.dni);

        if (!validarDNI(usuario.dni))
        {
            printf("DNI invalido. Asegurese de ingresar un numero de 7 u 8 digitos y sin caracteres no numericos.\n");
        }
    }
    while (!validarDNI(usuario.dni));

    printf("Ingrese su direccion:\n");
    printf("Calle: ");
    fflush(stdin);
    gets(usuario.domicilio.calle);

    do
    {
        printf("Altura: ");
        fflush(stdin);
        gets(alturaStr);

        if (!validarAltura(alturaStr))
        {
            printf("Altura invalida. Asegurese de ingresar un numero mayor a 0.\n");
        }
    }
    while (!validarAltura(alturaStr));
    usuario.domicilio.altura = atoi(alturaStr);

    printf("Codigo Postal: ");
    scanf("%d", &usuario.domicilio.cp);

    printf("Ciudad: ");
    fflush(stdin);
    gets(usuario.domicilio.ciudad);

    printf("Pais: ");
    fflush(stdin);
    gets(usuario.domicilio.pais);

    usuario.eliminado = 0;
    for (int i = 0; i < 50; i++)
    {
        usuario.librosFavoritos[i] = 0;
    }
    usuario.idUsuario = generarIdUsuarios(*arbolUsuarios);
    nodoArbolUsuarios *nuevoNodo = crearNodoArbol(usuario);
    if (nuevoNodo == NULL)
    {
        printf("Error al crear nodo de usuario.\n");
        return;
    }

    *arbolUsuarios = insertarEnArbol(*arbolUsuarios, nuevoNodo);
    printf("Usuario registrado exitosamente!\n");
}

void iniciarSesion(nodoArbolUsuarios *arbolUsuarios,nodoLibro * listaLibros)
{
    char password[20];
    char userName[20];

    printf("\n=== INICIO DE SESION ===\n");

    printf("Ingrese su nombre de usuario: ");
    fflush(stdin);
    gets(userName);
    printf("Ingrese su contrasenia: ");
    fflush(stdin);
    gets(password);

    if (strcmp(userName, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("Inicio de sesion exitoso como administrador.\n");
        system("cls");
        menuAdministrador(arbolUsuarios,listaLibros);
        return;
    }

    nodoArbolUsuarios *usuarioActual = buscarUsuarioPorUsername(arbolUsuarios, userName);
    if (usuarioActual != NULL)
    {
        if (strcmp(usuarioActual->datosUsuarios.password, password) == 0)
        {
            printf("Inicio de sesion exitoso.\n");
            system("cls");
            menuPostLogin(usuarioActual, arbolUsuarios,listaLibros);
        }
        else
        {
            printf("Contrasenia incorrecta. Por favor, intente de nuevo.\n");
        }
    }
    else
    {
        printf("El usuario ingresado no existe en nuestro registro.\n");
    }
}

void menuAdministrador(nodoArbolUsuarios ** arbolUsuarios, nodoLibro **listaLibros)
{
    stLibro libro;
    int opcion;
    int idLibro=0;

    do
    {
        printf("\n=== MENU ADMINISTRADOR ===\n");
        printf("1. Ver usuarios\n");
        printf("2. Agregar usuario\n");
        printf("3. Eliminar usuario\n");
        printf("4. Ver libros\n");
        printf("5. Agregar libro\n");
        printf("6. Quitar libro\n");
        printf("7. Salir al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            elegirArbolAVer(arbolUsuarios);
            system("pause");
            system("cls");
            break;
        case 2:
            registrarUsuario(&arbolUsuarios);
            system("pause");
            system("cls");
            break;
        case 3:
            *arbolUsuarios = bajaDelUsuario(arbolUsuarios);
            system("pause");
            system("cls");
            break;
        case 4:
            elegirListaAVerLibros(listaLibros); // Asume que tienes una función para mostrar los libros.
            system("pause");
            system("cls");
            break;
        case 5:
            printf("\n=== Cargar un nuevo libro ===\n");

            // Cargar datos del libro
            libro = cargarUnLibro();
            printf("Libro ingresado: Titulo - %s\n", libro.titulo);

            // Pedir la valoración
            printf("Ingrese la valoración (0-5): ");
            scanf("%f", &libro.valoracion); // CORRECCIÓN AQUÍ

            // Generar ID único
            libro.idLibro = generarIdLibros(*listaLibros);
            printf("ID generado: %d\n", libro.idLibro);

            // Marcar el libro como activo
            libro.eliminado = 0;

            // Crear un nodo para el libro y agregarlo a la lista
            nodoLibro *nuevoNodo = crearNodoLibros(libro);
            *listaLibros = agregarAlFinalLibro(*listaLibros, nuevoNodo);

            printf("\nLibro agregado exitosamente.\n");
            system("pause");
            system("cls");
            break;
        case 6:
            printf("Ingrese el id del libro que desea dar de baja\n");
            scanf("%d",&idLibro);
            bajaLogicaLibro(listaLibros,idLibro); // Asume que tienes una función para eliminar libros.
            system("pause");
            system("cls");
            break;
        case 7:
            guardarUsuariosEnArchivo(*arbolUsuarios, "archivoUsuarios.dat");
            guardarLibrosEnArchivo(*listaLibros, "archivoLibros.dat"); // Asume que tienes esta función.
            printf("Cerrando sesion...\n");
            system("cls");
            return;
        default:
            printf("Opcion no valida.\n");
            break;
        }
    }
    while (opcion != 7);
}

void menuPostLogin(nodoArbolUsuarios *usuarioLogueado, nodoArbolUsuarios **arbolUsuarios,nodoLibro ** listaLibros)
{
    int opcion;
    nodoComentario * listaComentarios=NULL ;
    do
    {
        printf("\n=== BIENVENIDO! ===\n");
        printf("1. Modificar informacion personal\n");
        printf("2. Menu libros\n");
        printf("3. Cerrar sesion\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            system("cls");
            modificarInformacionPersonal(usuarioLogueado, arbolUsuarios);
            break;
        case 2:
            system("cls");
            menuLibros(usuarioLogueado,listaLibros,listaComentarios);
            break;
        case 3:
            system("cls");
            guardarUsuariosEnArchivo(arbolUsuarios, "archivoUsuarios.dat");
            printf("Cerrando sesion...\n");
            return;
        default:
            printf("Opcion no valida.\n");
            break;
        }
    }
    while (opcion != 2);
}

void modificarInformacionPersonal(nodoArbolUsuarios* usuario, nodoArbolUsuarios *arbolUsuarios)
{
    char mail[100];
    int opcion;
    do
    {
        printf("\n=== MODIFICAR INFORMACION PERSONAL ===\n");
        printf("1. Cambiar email\n");
        printf("2. Cambiar contrasenia\n");
        printf("3. Cambiar nombre de usuario\n");
        printf("4. Volver\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            do
            {
                printf("Ingrese nuevo email: ");
                fflush(stdin);
                gets(mail);

                if (!validarMail(mail))
                {
                    printf("El formato del email no es valido. Asegurese de incluir un '@' y un '.com'\n");
                }
                else if (verificarEmailExistente(arbolUsuarios, mail))
                {
                    printf("El email ingresado ya existe. Intente nuevamente.\n");
                }
                else
                {
                    strcpy(usuario->datosUsuarios.email, mail);
                    printf("Email actualizado correctamente.\n");
                    break;
                }
            }
            while (1);
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Ingrese nueva contrasenia: ");
            fflush(stdin);
            gets(usuario->datosUsuarios.password);
            printf("Contrasenia actualizada.\n");
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Ingrese nuevo nombre de usuario: ");
            fflush(stdin);
            gets(usuario->datosUsuarios.username);
            printf("Nombre de usuario actualizado.\n");
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Retorno exitoso.\n");
            system("pause");
            system("cls");
            return;
        default:
            printf("Opcion no valida.\n");
        }
    }
    while(opcion != 4);
}

void menuLibros(nodoArbolUsuarios * usuarioLogueado, nodoLibro ** listaLibros, nodoComentario ** listaComentarios)
{
    nodoLibro * aux= listaLibros;
    char categoriaAbuscar[50];
    char tituloAbuscar[50];
    char autorAbuscar[50];

    int opcion;

    do
    {
        printf("\n=== MENU DE LIBROS ===\n");
        printf("1. Consultar libros por categoria\n");
        printf("2. Consultar libros por autor\n");
        printf("3. Buscar libro por titulo\n");
        printf("4. Agregar/Quitar libro favorito\n");
        printf("5. Mostrar libros\n");
        printf("6. Ver un libro y sus comentarios\n");
        printf("7. Agregar un comentario a un libro\n");
        printf("8. Ver comentarios\n");
        printf("9. Borrar o editar comentario propio\n");
        printf("10. Salir al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            printf("Ingrese la categoria que desea buscar:\n");
            fflush(stdin);
            gets(categoriaAbuscar);
            buscarLibroPorCategoria(listaLibros, categoriaAbuscar);
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Ingrese el autor que desea buscar: \n");
            fflush(stdin);
            gets(autorAbuscar);
            buscarLibrosPorAutor(listaLibros,autorAbuscar);
            system("pause");
            system("cls");
            break;

        case 3:
            printf("Ingrese el titulo que desea buscar: \n");
            fflush(stdin);
            gets(tituloAbuscar);
            buscarLibroPorTitulo(listaLibros,tituloAbuscar);
            system("pause");
            system("cls");
            break;

        case 4:
            gestionarLibrosFavoritos(usuarioLogueado,listaLibros);
            system("pause");
            system("cls");
            break;

        case 5:
            mostrarListaLibrosActivos(listaLibros);
            system("pause");
            system("cls");
            break;

        case 6: // Ver un libro y sus comentarios
        {
            int idLibro;
            printf("\nIngrese el ID del libro que desea consultar: ");
            scanf("%d", &idLibro);

            aux = buscaLibroPorId(listaLibros, idLibro);
            if (aux)
            {
                mostrarUnNodoLibro(aux);
                printf("\n=== Comentarios del libro ===\n");
                if (!listaComentarios)
                {
                    printf("No hay comentarios para este libro.\n");
                }
                else
                {
                    mostrarComentariosPorLibro(listaComentarios, idLibro);
                }
            }
            else
            {
                printf("No se encontro un libro con ese ID.\n");
            }
        }
        system("pause");
        system("cls");
        break;

        case 7:
        {
            int idLibro;
            printf("\nIngrese el ID del libro al que desea agregar un comentario: ");
            scanf("%d", &idLibro);

            printf("ID ingresado: %d\n", idLibro);

            nodoLibro* aux = buscaLibroPorId(listaLibros, idLibro);
            if (aux)
            {
                printf("Libro encontrado: %s\n", aux->libro.titulo);

                // Verificar si ya existe un comentario para este libro y usuario
                if (comentarioExistente(listaComentarios, idLibro, usuarioLogueado))
                {
                    printf("Ya existe un comentario para este libro de este usuario.\n");
                }
                else
                {
                    nodoComentario* nuevo = crearNodoComentario(aux->libro, listaComentarios, usuarioLogueado);
                    if (nuevo)
                    {
                        printf(" Nodo comentario creado correctamente.\n");

                        listaComentarios = agregarAlFinalComentario(listaComentarios, nuevo);
                        printf("Comentario agregado exitosamente.\n");
                    }
                    else
                    {
                        printf("ERROR: No se pudo crear el comentario.\n");
                    }
                }
            }
            else
            {
                printf("ERROR: No se encontro un libro con ese ID.\n");
            }
        }
            guardarComentariosEnArchivo(listaComentarios,"archivoComentarios.dat");
            system("pause");
            system("cls");
            break;
        case 8:
            mostrarArchivoComentarios("archivoComentarios.dat"); // Llamamos a la función para mostrar todos los comentarios
            system("pause");
            system("cls");
            break;
        case 9:
            menuComentarios("archivoComentarios.dat", usuarioLogueado);
            break;
        case 10:
                guardarLibrosEnArchivo(listaLibros,"archivoLibros.dat");
                guardarComentariosEnArchivo(listaComentarios,"archivoComentarios.dat");
                printf("Regresando al menu principal...\n");
                system("cls");
                break;

            default:
                printf("Opcion no valida.\n");
            }
        }
        while(opcion != 10);
    }


