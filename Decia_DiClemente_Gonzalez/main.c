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

/// Funciones

void pause();
void altaDeClientes(char arregloChar[]);
void cargaDeDomicilio(stCliente cliente);
void cargaDeClientes(stCliente cliente);
void bajaDeClientes(char arregloChar[]);




int main()
{

    /// Variables varias
    char arregloChar[30]={"ArchivoNumeros"};

    // Variables Menu
    int opcion;
    char continuar = 's';

    // Variables switch para clientes

    int opcionCliente1;

    //Variables switch para pedidos

    // Menu
    do {

        printf("\nSeleccione: \n\n");

        printf("1. Clientes \n2. Pedidos \n\n");
        fflush(stdin);
        scanf("%i", &opcion);


    switch(opcion)
    {

    case 1:

        do{

            printf("\nIngrese que apartado quiere ver: \n1. Alta de Clientes\n");
            printf("2. Baja de Clientes\n");
            printf("3. Modificacion de clientes\n");
            printf("4. Listar Clientes\n");

            scanf("%i", &opcionCliente1);

        switch(opcionCliente1){

        /// Alta de clientes
        case 1:


            altaDeClientes(arregloChar);


            break;
        /// Baja de clientes
        case 2:


            bajaDeClientes(arregloChar);


            break;


        default:

            printf("Numero ingresado incorrecto\n");

            break;


        }

        printf("\nDesea ingresar a otro apartado?\n");
        fflush(stdin);
        scanf("%c", &continuar);


        }while (continuar == 's');



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

/// Miscelaneo
void pause(){

    system("Pause");
    system("cls");

}


/// Alta de clientes

void verArchivo(char arregloChar[]){   /// Lee lo que el usuario haya ingresado en carga de clientes

    FILE * archivo=fopen(arregloChar, "rb");

    stCliente cliente;

    if(archivo!=NULL){

        while(!feof(archivo)){

            fread(&cliente, sizeof(stCliente), 1, archivo);

            printf("Nombre y apellido: ");
            puts(cliente.nombre);
            printf("%s", cliente.apellido);

            printf("\nDomicilio: ");
            printf("%s", cliente.domicilio.nombreCalle);
            printf(" %i", cliente.domicilio.alturaCalle);

            printf("\nMail: ");
            printf("%s", cliente.mail);

            printf("\nMovil: ");
            printf("%i", cliente.movil);

        }

        fclose(archivo);

    }else{

        printf("No se pudo abrir el archivo\n");

    }

}


void cargaDeDomicilio(stCliente cliente){  /// Funcion exclusivamente para cargar el domicilio

    printf("\nIngrese el nombre de la calle del domicilio: ");
    fflush(stdin);
    gets(cliente.domicilio.nombreCalle);

    printf("\nIngrese la altura de la calle: ");
    scanf("%i", cliente.domicilio.alturaCalle);

}

void cargaDeClientes(stCliente  cliente){   /// Carga de clientes, se llama cuantas veces sea necesario en altaDeClientes

        printf("\nIngrese el nombre del cliente: ");
        fflush(stdin);
        gets(cliente.nombre);

        printf("\nIngrese el apellido del cliente: ");
        fflush(stdin);
        gets(cliente.apellido);

        cargaDeDomicilio(cliente);

        printf("\nIngrese el mail del cliente: ");
        fflush(stdin);
        gets(cliente.mail);

        printf("\nIngrese el movil del cliente: ");
        scanf("%i", &cliente.movil);

}


void altaDeClientes(char arregloChar[]){

    FILE * archivo=fopen(arregloChar, "w+b");

    char continuar = 's';
    int i=0;
    stCliente cliente;
    stCliente clienteAuxiliar;

    printf("Va a ingresar los datos de los clientes tal como se le pida\n");

    if(archivo!=NULL){

        do{

        fseek(archivo, sizeof(stCliente)*-1, SEEK_END);

        if(fread(&clienteAuxiliar, sizeof(stCliente), 1, archivo)==0){

            cliente.idCliente=1;

        }else{

        cliente.idCliente = clienteAuxiliar.idCliente + 1;

        }

        cargaDeClientes(cliente);

        fwrite(&cliente, sizeof(stCliente), 1, archivo);

        printf("Desea seguir ingresando clientes? (s=Si / n=No)\n");
        fflush(stdin);
        scanf("%c", &continuar);

        }while(continuar=='s');

        fclose(archivo);

    }else{

        printf("El Archivo no se pudo abrir\n");

    }


    printf("Desea ver todo lo que ha ingresado? (s=Si / n=No)\n");
    fflush(stdin);
    scanf("%c", &continuar);

    if(continuar=='s'){

        verArchivo(arregloChar);

    }


}


/// Baja de clientes


void bajaDeClientes(char arregloChar[]){

    FILE * archivo = fopen(arregloChar, "rb");

    stCliente cliente;

    int idAux;

    if(archivo != NULL){

        printf("Que cliente quiere darle de baja? Ingrese el ID de este: ");
        scanf("%i", &idAux);
        printf("\n");

        while(!feof(archivo)){

            if((fread(&cliente.idCliente, sizeof(stCliente), 1, archivo)==idAux)){  /// Encuentra el id de cliente a bajar

                cliente.bajaCliente=1;  /// Por si se tiene que ver el cliente bajado la condicion es 1 en bajaCliente

            }

        }


        fclose(archivo);

    }else{

        printf("No se ha abierto el archivo correctamente\n");

    }


}

