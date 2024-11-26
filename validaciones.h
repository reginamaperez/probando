#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validarStringNombre(char username[]);
int validarStringNum(char username[]);
int validarMayusculaMinuscula(char contrasenia[]);
int validarMail(char mail[]);
int validarLenghtContrasenia(char password[]);
int validarContrasenia(char password[], char password1[]);
int validarFechaNacimiento(char *fecha);
int validarGenero(char genero);
int validarAltura(char *alturaStr);



#endif // VALIDACIONES_H_INCLUDED
