// Autor: Mauricio CAstro Leal
// Fecha: 20/12/2024
// Objetivo: Calculadora de Liquidez

#include <stdio.h>

void calculo_liquidez(int *monedas, int *cantidad);

int main()
{
    int monedas[9] = {10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000}; // Moneda Chilena
    int cantidad[9];

    printf("Ingreso de liquidez\n");
    printf("-------------------\n");
    printf("Ingrese la cantidad para cada moneda\n");

    for (int i = 0; i < 9; i++) // Ciclo donde se ingrese el dinero
    {
        printf("\nMonedas $%i: ", monedas[i]);
        scanf("%d", &cantidad[i]);
        
        if (cantidad[i] < 0){ // Ciclo que verifique el correcto ingreso del dinero
            printf("cantidad invalida");
            i -= 1;
        }

    }

    calculo_liquidez(monedas, cantidad);

    return 0;
}

void calculo_liquidez(int *monedas, int *cantidad) // Función que calcule el dinero total
{
    int dinero = 0;

    for(int i = 0; i < 9; i++)
    {
        dinero += monedas[i] * cantidad[i]; // Calculo del dinero final
    }

    printf("\nLa cantidad de dinero reunida es de: $%i", dinero);
}