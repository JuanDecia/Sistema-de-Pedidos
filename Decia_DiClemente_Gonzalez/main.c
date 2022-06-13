#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura Domicilio
typedef struct
{
    char nombreCalle[30];
    int alturaCalle;
} stDomicilio;

// Estructura Cliente
typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char mail[50];
    int movil;
    int bajaCliente;
    stDomicilio domicilio;

} stCliente;

// Estructura Fecha

typedef struct
{
    int dia;
    int mes;
    int anio;

} stFecha;

// Estructura Pedido

typedef struct
{
    int idCliente;
    int idPedido;
    char descripcionPedido[30];
    int costoPedido;
    int pedidoAnulado;
    stFecha fecha;

} stPedido;


int main()
{
    // Variables Menu
    int opcion;
    char continuar = 's';

    // Variables switch para clientes
    int opcionCliente1;

    //Variables switch para pedidos

    // Menu
    do {

        printf("\nSeleccione: \n\n");

        printf("1. Clientes \n2. Pedidos \n");
        fflush(stdin);
        scanf("%i", &opcion);


    switch(opcion)
    {

    case 1:

        do {
            printf("\nSeleccione")

            switch(opcionCliente1)
        {

        }

        } while (continuar == 's');



    break;

    case 2:

        printf("pedido");

    break;

    default:

        printf("\nOpcion incorrecta. \n");

    break;


    }

        printf("\nDesea seguir operando? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);

    } while (continuar == 's');

    return 0;
}
