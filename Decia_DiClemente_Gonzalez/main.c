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

/// Funciones Clientes

void pause();
void altaDeClientes(char arregloChar[]);
void cargaDeDomicilio(stCliente cliente);
void cargaDeClientes(stCliente cliente);
void bajaDeClientes(char arregloChar[]);
void modificarCliente (char archivo[]);
stCliente modificarApellido(stCliente cliente);
stCliente modificarNombre(stCliente cliente);
stCliente modificarMovil(stCliente cliente);
stDomicilio modificardomicilio(stDomicilio domicilio);
stCliente modificarEmail(stCliente cliente);



// Funciones Listado de clientes
int BuscarPosMenor (stCliente cliente[],int pos,int validos);
void ordenamientoPorSeleccionClientes (stCliente clientes[],int validos);
int pasarArchivoToArreglo (char nombreArch[],stCliente clientes[],int dimension);
void pasarArregloToArchivo (char nombreArch[],stCliente clientes[],int validos);

///Funciones pedidos
void anularPedido (char archivo[]);
void modificarPedido (char archivo[]);
stPedido modificarCosto(stPedido pedido);
stPedido modficarDescripcion (stPedido pedido);
stFecha modificarFecha (stFecha fecha);

// Funciones listado y estadistica


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

        case 3:

            modificarCliente(arregloChar);

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
    scanf("%i", &cliente.domicilio.alturaCalle);

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

// Modificacion de clientes

void modificarCliente (char archivo[])
{
    FILE * buff;

    buff = fopen(archivo, "r+b");

    stCliente cliente;
    stDomicilio domicilio;

    char continuar = ' ';
    int auxID;

    // Variables para el switch
    int opcion;
    char continuar2;

    if (archivo != NULL)
    {
        while (continuar == 's')
        {
            printf("\nSeleccione el ID para buscar el usuario a modificar: ");
            fflush(stdin);
            scanf("%i", &auxID);

            while(fread (&cliente, sizeof(stCliente), 1, buff) > 0)
            {
                if(cliente.idCliente == auxID)
                {
                    printf("\nSeleccione el/los datos que desea modificar: \n");

                    do {

                        printf("\n1. Apellido. \n");
                        printf("\n2. Nombre. \n");
                        printf("\n3. Mail \n");
                        printf("\n4. Movil \n");
                        printf("\n5. Direccion \n");

                        scanf("%i", &opcion);

                        switch(opcion)
                        {

                        case 1:

                            cliente=modificarApellido(cliente);
                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 2:

                            cliente=modificarNombre(cliente);
                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 3:

                            cliente=modificarEmail(cliente);
                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 4:

                            cliente=modificarMovil(cliente);
                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 5:

                            domicilio=modificardomicilio(domicilio);
                            fseek(buff, sizeof(stDomicilio) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stDomicilio), 1, buff);


                        break;

                        }

                        rewind(buff);

                        printf("\nDesea continuar modificando datos? ('s' es afirmativo): ");
                        fflush(stdin);
                        scanf("%c", &continuar2);


                    } while (continuar2 == 's');

                }
            }

            printf("\nDesea modificar otro usuario? (S/N): ");
            fflush(stdin);
            scanf("%c", &continuar);
        }

        fclose(buff);

    } else
    {
        printf("\nNo se ha podido abrir el archivo\n");
    }

}

//modularizacion de modificacion de clientes

stCliente modificarNombre(stCliente cliente)
{
    printf("\nIngrese el nuevo nombre: ");
    fflush(stdin);
    gets(cliente.nombre);

    return cliente;
}

stDomicilio modificardomicilio(stDomicilio domicilio)
{
    printf("\ningrese el nuevo domicilio: ");
    fflush(stdin);
    gets(domicilio.nombreCalle);

    printf("\nIngrese la altura: ");
    fflush(stdin);
    scanf("%d",&domicilio.alturaCalle);

    return domicilio;
}

stCliente modificarApellido(stCliente cliente)
{
    printf("\ningrese el nuevo Apellido: ");
    fflush(stdin);
    gets(cliente.apellido);

    return cliente;
}

stCliente modificarEmail(stCliente cliente)
{
    printf("\ningrese el nuevo Mail: ");
    fflush(stdin);
    gets(cliente.mail);

    return cliente;
}

stCliente modificarMovil(stCliente cliente)
{
    printf("\ningrese el nuevo movil: ");
    fflush(stdin);
    scanf("%d",&cliente.movil);

    return cliente;
}



void anularPedido (char archivo[])
{
    FILE * buff = buff = fopen(archivo, "r+b");

    stPedido pedido;

    int idAux;

    if(archivo != NULL)
    {

        printf("Ingrese ID del pedido para realizar la baja: ");
        scanf("%i", &idAux);
        printf("\n");

        while(fread (&pedido, sizeof(stPedido), 1, buff) > 0)
        {
            if(pedido.idPedido == idAux)
            {
                pedido.pedidoAnulado = 1;  // 1 == pedido anulado
            }
        }

        fclose(buff);

    }else{

        printf("No se ha abierto el archivo correctamente\n");

    }

}

// Modificar Pedido

void modificarPedido (char archivo[])
{
    FILE * buff;

    buff = fopen(archivo, "r+b");

    stPedido pedido;
    stFecha fecha;

    char continuar = ' ';
    int auxID;

    // Variables para el switch
    int opcion;
    char continuar2 = ' ';
    char anular = ' ';

    if (archivo != NULL)
    {
        while (continuar == 's')
        {
            printf("\nSeleccione el ID para buscar el pedido a modificar: ");
            fflush(stdin);
            scanf("%i", &auxID);

            while(fread (&pedido, sizeof(stPedido), 1, buff) > 0)
            {
                if(pedido.idPedido == auxID)
                {
                    printf("\nSeleccione el/los datos que desea modificar: \n");

                    do {

                        printf("\n1. Costo. \n");
                        printf("\n2. Descripcion. \n");
                        printf("\n3. Fecha \n");
                        printf("\n4. Anular Pedido \n");

                        scanf("%i", &opcion);

                        switch(opcion)
                        {

                        case 1:

                            pedido=modificarCosto(pedido);
                            fseek(buff, sizeof(stPedido) * -1, SEEK_CUR);
                            fwrite(&pedido.costoPedido, sizeof(stPedido), 1, buff);

                        break;

                        case 2:

                            pedido=modficarDescripcion(pedido);
                            fseek(buff, sizeof(stPedido) * -1, SEEK_CUR);
                            fwrite(&pedido.descripcionPedido, sizeof(stPedido), 1, buff);

                        break;

                        case 3:

                            fecha=modificarFecha(fecha);

                            fseek(buff, sizeof(stPedido) * -1, SEEK_CUR);
                            fwrite(&pedido.fecha, sizeof(stPedido), 1, buff);

                        break;

                        case 4:

                            printf("\n:Desea anular el pedido?(S/N):  \n");
                            fflush(stdin);
                            scanf("%c", &anular);

                            if(anular == 's')
                            {
                                anularPedido(archivo);
                            }
                        }

                        rewind(buff);

                        printf("\nDesea continuar modificando pedidos? ('s' es afirmativo): ");
                        fflush(stdin);
                        scanf("%c", &continuar2);

                    } while (continuar2 == 's');

                }
            }

            printf("\nDesea modificar otro pedido? (S/N): ");
            fflush(stdin);
            scanf("%c", &continuar);
        }

        fclose(buff);

    } else
    {
        printf("\nNo se ha podido abrir el archivo\n");
    }

}

//modularizacion de la modificacion de pedidos
stPedido modificarCosto(stPedido pedido){
    printf("\nIngrese el nuevo costo: \n");
    fflush(stdin);
    scanf("%i", &pedido.costoPedido);
}

stPedido modficarDescripcion (stPedido pedido){
    printf("\nIngrese nueva descripcion: \n");
    fflush(stdin);
    gets(pedido.descripcionPedido);
}

stFecha modificarFecha (stFecha fecha){
    printf("\nIngrese nueva fecha: \n");

    printf("\nIngrese dia: ");
    fflush(stdin);
    scanf("%i", &fecha.dia);

    printf("\nIngrese mes: ");
    fflush(stdin);
    scanf("%i", &fecha.mes);

    printf("\nIngrese anio: ");
    fflush(stdin);
    scanf("%i", &fecha.anio);
}


//Listar clientes

//Ordenados por método de selección tomando en cuenta número de id del cliente.

int BuscarPosMenor (stCliente cliente[],int pos,int validos){

    int MiMenor=cliente[pos].idCliente;
    int posMenor = pos;
    int i = pos+1;

    while(i<validos){
        if(cliente[i].idCliente<MiMenor){
            MiMenor=cliente[i].idCliente;
            posMenor=1;
        }
        i++;
    }
    return posMenor;
}

void ordenamientoPorSeleccionClientes (stCliente clientes[],int validos){
    int i=0;
    int pmenor;
    stCliente aux;

    while(i<validos){
        pmenor=BuscarPosMenor(clientes,i,validos);
        aux=clientes[pmenor];
        clientes [pmenor]=clientes[i];
        clientes[i]=aux;
        i++;
    }
}

//Pasar archivo a arreglo
int pasarArchivoToArreglo (char nombreArch[],stCliente clientes[],int dimension){
    FILE * buf=fopen(nombreArch,"rb");
    stCliente aux;

    int i =0;

    if(buf){
        while((fread(&aux,sizeof(stCliente),1,buf)>0)&& i<dimension){

                clientes[i]=aux;
                i++;
        }
        fclose(buf);
    }
    return i;
}

//Pasar arreglo a archivo
void pasarArregloToArchivo (char nombreArch[],stCliente clientes[],int validos){
    FILE * archi=fopen(nombreArch,"ab");
    int i=0;

    if(archi!=NULL){
        i=fwrite(clientes,sizeof(stCliente),1,archi);

        fclose(archi);

    }
}

//Ordenados por método de inserción tomando en cuenta nombre Y apellido (ambos al mismo tiempo)
