#include <stdio.h>
#include <string.h>
#include "libreria.h"

int cantidadDeMinas( int porcentaje ){
    int operacion;

    operacion = ((tam*tam) * porcentaje)/100;

    return operacion;
}

int main(){

    int i,j;
    int minas;
    int posicionConNumeros;
    int dificultadPorcentaje;
    int fila, columna;
    int mostrarMinas = 2;
    int ganarJuego = 0;
    int minasAcertadas = 0;
    char posicionConLetras;
    char dificultad;
    char eleccionJugador = 2;
    char tablero[tam][tam];
    char tableroEnJuego[tam][tam];
    char cuentaMinas;

    //inicio
    Titulo();
    printf("Ingrese dificultad de la partida (F (facil), M (medio), D (dificil): ");
    fflush(stdin);
    scanf("%c", &dificultad);

    //calcula el porcentaje dependiendo de la dificultad
    if(dificultad == 'f' || dificultad == 'F'){
        dificultadPorcentaje = 10;
        minas = cantidadDeMinas(dificultadPorcentaje);
        /*printf("%d", minas);
        system("PAUSE");*/
    }
    else if(dificultad == 'm' || dificultad == 'M'){
        dificultadPorcentaje = 15;
        minas = cantidadDeMinas(dificultadPorcentaje);
        /*printf("%d", minas);
        system("PAUSE");*/
    }
    else if(dificultad == 'd' || dificultad == 'D'){
        dificultadPorcentaje = 20;
        minas = cantidadDeMinas(dificultadPorcentaje);
        /*printf("%d", minas);
        system("PAUSE");*/
    }

    construir_tablero(tablero, minas);

    //copia el tablero original en el que usara el usuario
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            tableroEnJuego[i][j] = tablero[i][j];
        }
    }

    LimpiaPantalla();

    while(ganarJuego != minas){

        /*
        mostrarMinas = 1;
        mostrar_tablero(tableroEnJuego, mostrarMinas);
        */
        mostrar_tablero(tableroEnJuego, mostrarMinas);

        printf("Ingrese M para marcar, A para abrir una casilla: ");
        fflush(stdin);
        scanf("%c", &eleccionJugador);
        LimpiaPantalla();

        printf("Ingrese M para marcar, A para abrir una casilla: %c", eleccionJugador);
        printf("\nIngrese coordenada de casilla (ej: 1,a): ");
        fflush(stdin);
        scanf("%i,%c", &posicionConNumeros, &posicionConLetras);

        //dependiendo los datos que da el usuario se calcula la posicion en donde jugo
        fila = posicionConNumeros - 1;
        columna = posicionConLetras - 97;

        //printf("\n %i,%i \n", fila, columna);

        //revisa si hay una minas alrededor y guarda la cantidad de minas en el arreglo
        if(eleccionJugador == 'a' || eleccionJugador == 'A'){
            if(tablero[fila][columna] == '*'){
                mostrarMinas = 1;
                mostrar_tablero(tablero, mostrarMinas);
                ganarJuego = 3;

            }
            else{
                cuentaMinas = '0';
                for(i = fila - 1; i <= fila + 1; i++){
                    for(j = columna - 1; j <= columna + 1; j++){
                        if(tablero[i][j] == '*'){
                            cuentaMinas += 1;
                            //printf("\n%c\n", cuentaMinas);
                        }
                    }
                }
                tablero[fila][columna] = cuentaMinas;
                tableroEnJuego[fila][columna] = cuentaMinas;
            }
        }

        else if(eleccionJugador == 'm' || eleccionJugador == 'M'){
            tableroEnJuego[fila][columna] = 'M';
            if(tableroEnJuego[fila][columna] == 'M' && tablero[fila][columna] == '*'){
                ganarJuego++;
                minasAcertadas++;
            }
        }
    }

    if(minasAcertadas != minas){
        printf("Perdiste!!!");
        printf("\nAcertaste a %i minas.", minasAcertadas);
    }
    if(minasAcertadas == minas){
        mostrarMinas = 0;
        mostrar_tablero(tableroEnJuego, mostrarMinas);
        printf("Ganaste!!!");
        printf("\nMarcaste correctamente las %i minas.", minasAcertadas);
    }
    //LimpiaPantalla();

    return 0;
}
