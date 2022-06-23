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
void modificarDatosCliente (char archivo[],int opcion);


/// Funciones Listado de clientes
int BuscarPosMenor (stCliente cliente[],int pos,int validos);
void ordenamientoPorSeleccionClientes(int validos);
int pasarArchivoToArreglo (char nombreArch[],stCliente clientes[],int dimension);
void pasarArregloToArchivo (char nombreArch[],stCliente clientes[],int validos);
void ordenamientoPorInsercionNombreApellido(char arregloChar[], int validos);
void unirApellidoNombre(stCliente cliente, stCliente auxCliente[]);

///Funciones pedidos
void anularPedido (char archivo[]);
void modificarPedido (char archivo[], int contadorPedido[]);
void modificacionDatosPedido (char archivo[],int opcion);
void mostrarPedidos(stPedido pedido);


// Funciones listado y estadistica
void listarTopTenClientes (char nombreArch[],int contadorPedidos[], int top10clientes[]);
void buscarPeorCliente (char archivo[],int contadorPedidos[]);
void busquedaMasViejo(char archivo[],stPedido pedidos);
void mostrarPedidosDeUnCliente (char nombreArchivo[],int idClienteAbuscar, int contadorPedidos[]);

int main()
{

    // Variable Archivo
    char arregloChar[30]={"ArchivoNumeros"};

    // Variables Menu
    int opcion;
    int validos;
    char seleccion;
    char continuar = 's';

    // Variables switch para clientes
    int opcionCliente1;


    //Variables switch para pedidos
    int opcionPedido;

    int contadorDePedidos[100];

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
            pause();

            break;
        /// Baja de clientes
        case 2:

            bajaDeClientes(arregloChar);
            pause();

            break;
        /// Modificar Clientes
        case 3:

            modificarCliente(arregloChar);
            pause();

            break;
        /// Listar clientes
        case 4:

            printf("Quiere ordenarlos por seleccion o insercion? (I=Insercion, S=Seleccion)\n");
            fflush(stdin);
            scanf("%c", &seleccion);

            if(seleccion=='s'){

                ordenamientoPorSeleccionClientes(int validos);

            }else{

                ordenamientoPorInsercionNombreApellido(char arregloChar[], int validos);

            }

            pause();

            break;

        default:

            printf("Numero ingresado incorrecto\n");
            pause();

            break;


        }

        printf("\nDesea ingresar a otro apartado?\n");
        fflush(stdin);
        scanf("%c", &continuar);



        }while (continuar == 's');



        break;

    case 2:

        do {
            printf("\nIngrese que apartado quiere ver: \n1. Alta de Pedido\n");
            printf("2. Baja de Pedido\n");
            printf("3. Modificacion de Pedido\n");
            printf("4. Listar Pedidos\n");

            scanf("%i", &opcionPedido);

            switch(opcionPedido)
            {

            //alta de pedido
            case 1:

                altaPedido(arregloChar);
                pause();

                break;

            //baja de pedido
            case 2:

                anularPedido(arregloChar);
                pause();

                break;

            //modificar pedido
            case 3:

                modificarPedido(arregloChar, contadorDePedidos);
                pause();

                break;

            //listar pedido
            case 4:

                listarPedidos(arregloChar, contadorDePedidos);
                pause();

                break;


            }
        } while (continuar == 's');

        break;

    default:

        printf("\nOpcion incorrecta. \n");

        break;


    }

        printf("\nDesea seguir operando? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);

    } while (continuar == 's');

    pause();

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

                        modificarDatosCliente(archivo,opcion);

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

//modificacion de datos del cliente

void modificarDatosCliente (char archivo[],int opcion){

    FILE* buff = fopen(archivo,"r+b");
    stCliente cliente;



    if(archivo!=NULL){
        switch(opcion)
                        {

                        case 1:

                            printf("\ningrese el nuevo Apellido: ");
                            gets(cliente.apellido);

                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 2:

                            printf("\nIngrese el nuevo nombre: ");
                            gets(cliente.nombre);

                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 3:

                            printf("\ningrese el nuevo Mail: ");
                            gets(cliente.mail);

                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 4:

                            printf("\ningrese el nuevo movil: ");
                            scanf("%d",&cliente.movil);

                            fseek(buff, sizeof(stCliente) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stCliente), 1, buff);

                        break;

                        case 5:

                            printf("\ningrese el nuevo domicilio: ");
                            gets(cliente.domicilio.nombreCalle);

                            printf("\nIngrese la altura: ");
                            scanf("%d",&cliente.domicilio.alturaCalle);

                            fseek(buff, sizeof(stDomicilio) * -1, SEEK_CUR);
                            fwrite(&cliente, sizeof(stDomicilio), 1, buff);


                        break;
        }
    }
}


/// ================================= FUNCIONES PEDIDOS ===================================

// Carga de Fecha para pedido
void cargaFecha (stFecha fecha)
{
    printf("\nSe cargara la fecha de registro del pedido: ");

    printf("\nIngrese Dia: ");
    scanf("%i", &fecha.dia);

    printf("\nIngrese Mes: ");
    scanf("%i", &fecha.mes);

    printf("\nIngrese Anio: ");
    scanf("%i", &fecha.anio);
}

// Carga de Pedidos
void cargaPedido(stPedido pedido){   /// Carga de clientes, se llama cuantas veces sea necesario en altaDeClientes

    stFecha fecha;

        printf("\nIngrese la descripcion del pedido: ");
        fflush(stdin);
        gets(pedido.descripcionPedido);

        cargaFecha(fecha);

        printf("\nIngrese el costo del pedido: ");
        scanf("%i", &pedido.costoPedido);
}

void altaPedido(char archivo[]){

    FILE * buff = fopen(archivo, "w+b");

    char continuar = 's';

    stPedido pedido;
    stPedido pedidoAuxiliar;

    printf("\nDe alta al pedido entrante, realice los siguientes pasos: \n");

    if(buff!=NULL){

        do{

        fseek(buff, sizeof(stPedido) * -1, SEEK_END);

        if(fread(&pedidoAuxiliar, sizeof(stPedido), 1, buff) == 0){

            pedido.idPedido = 1;

        }else {

        pedido.idPedido = pedidoAuxiliar.idPedido + 1;

        }

        cargaPedido(pedido);

        fwrite(&pedido, sizeof(stPedido), 1, buff);

        printf("Desea seguir ingresando pedidos (S/N)? \n");
        fflush(stdin);
        scanf("%c", &continuar);

        }while(continuar=='s');

        fclose(buff);

    }else{

        printf("El Archivo no se pudo abrir\n");

    }


    printf("Desea ver todo lo que ha ingresado? (S/N) \n");
    fflush(stdin);
    scanf("%c", &continuar);

    if(continuar=='s'){

        verArchivo(archivo);

    }
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
//mostrar pedidos

void mostrarPedidos(stPedido pedido){

    puts("\n---------------------------\n");
    printf("\nID cliente: %d",pedido.idCliente);
    printf("\nID pedido: %d",pedido.idPedido);
    printf("\nDescripcion del pedido: %s",pedido.descripcionPedido);
    printf("\nCosto del pedido: %d",pedido.costoPedido);
    printf("\nPedido anulado: %d",pedido.pedidoAnulado);
    printf("\nFecha del pedido: ");
    printf("\nDia: %d",pedido.fecha.dia);
    printf("\nMes: %d",pedido.fecha.mes);
    printf("\nAnio: %d",pedido.fecha.anio);

}


// Modificar Pedido

void modificarPedido (char archivo[], int contadorPedidos[])
{
    FILE * buff;

    buff = fopen(archivo, "r+b");

    int i;

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

            i=auxID-1;
            contadorPedidos[i]=contadorPedidos[i]+1;

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

                        modificacionDatosPedido(archivo,opcion);

                        rewind(buff);

                        printf("\nDesea continuar modificando pedidos? ('s' es afirmativo): ");
                        fflush(stdin);
                        scanf("%c", &continuar2);

                    } while (continuar2 == 's');

                }
                i=0;
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

//modificar datos del pedido
void modificacionDatosPedido (char archivo[],int opcion){

    FILE * buff=fopen(archivo, "r+b");

    stPedido pedido;
    stFecha fecha;
    char anular = ' ';


    if(buff!=NULL){
        switch(opcion){

                        case 1:

                            printf("\nIngrese el nuevo costo: \n");
                            scanf("%i", &pedido.costoPedido);
                            fseek(buff, sizeof(stPedido) * -1, SEEK_CUR);
                            fwrite(&pedido.costoPedido, sizeof(stPedido), 1, buff);

                        break;

                        case 2:

                            printf("\nIngrese nueva descripcion: \n");
                            gets(pedido.descripcionPedido);
                            fseek(buff, sizeof(stPedido) * -1, SEEK_CUR);
                            fwrite(&pedido.descripcionPedido, sizeof(stPedido), 1, buff);

                        break;

                        case 3:

                            printf("\nIngrese nueva fecha: \n");

                            printf("\nIngrese dia: ");
                            scanf("%i", &fecha.dia);

                            printf("\nIngrese mes: ");
                            scanf("%i", &fecha.mes);

                            printf("\nIngrese anio: ");
                            scanf("%i", &fecha.anio);

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
    }
}


/*=====================Listar clientes===============*/

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

void ordenamientoPorSeleccionClientes(int validos){
    int i=0;
    int pmenor;
    stCliente clientes[];
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
int pasarArchivoToArreglo(char nombreArch[],stCliente clientes[],int dimension){
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

void ordenamientoPorInsercionNombreApellido(char arregloChar[], int validos){

    FILE * archi=fopen(arregloChar, "r+b");
    stCliente cliente;
    int j=1;
    int i=0-1;
    int flag=0;

    char auxCliente[30];
    char aux2Cliente[30];
    char auxNombre[30];
    char auxNombre2[30];
    char auxApellido[30];
    char auxApellido2[30];
    char auxAuxNombre[30];
    char auxAuxApellido[30];



    if(archi!=NULL){

        while((fread(&cliente, sizeof(stCliente), 1, archi))>0 && j<validos+1){


            do{

            flag=0;

            strcpy(auxNombre, cliente.nombre);
            strcpy(auxApellido, cliente.apellido);

            unirApellidoNombre(cliente, auxCliente);

            fseek(archi, sizeof(stCliente) * i+1, SEEK_SET);
            fread(&cliente, sizeof(stCliente), 1, archi);

            strcpy(auxNombre2, cliente.nombre);
            strcpy(auxApellido2, cliente.apellido);

            unirApellidoNombre(cliente, aux2Cliente);

            if(strcmpi(auxCliente, aux2Cliente)==(0-1)){

                strcpy(auxAuxNombre, auxNombre2);
                strcpy(auxAuxApellido, auxApellido2);

                strcpy(cliente.nombre, auxNombre);
                strcpy(cliente.apellido, auxApellido);

                i--;

                fseek(archi, sizeof(stCliente) * i, SEEK_SET);

                strcpy(cliente.nombre, auxNombre2);
                strcpy(cliente.apellido, auxApellido2);
                flag=1;

            }else{

                fseek(archi, sizeof(stCliente) * j, SEEK_SET);

            }

            }while(flag!=0);

            i=j-1;
            j++;

        }

    fclose(archi);

    }else{

        printf("No se pudo abrir el archivo\n");

    }


}

void unirApellidoNombre(stCliente cliente, stCliente auxCliente[]){

    strcat(auxCliente, cliente.nombre);
    strcat(auxCliente, cliente.apellido);

}

///////////////////listado y estadisticas////////////////////////

//Listar top ten de mejores clientes (por cantidad de pedidos)

void listarPedidos(char arregloChar[], int contadorPedidos[], ){

    int opcion;
    char seguir;
    int idClienteAbuscar;

    printf("Que apartado del listado de pedidos quiere acceder?: \n");
    printf("1. Listar todos los pedidos por orden de fecha (Viejo->Nuevo)\n");
    printf("2. Listar pedidos por cliente\n");
    printf("3. Listar TOP 10 mejores clientes\n");
    printf("4. Listar el PEOR cliente\n");

    do{

        switch(opcion){

        /// Listar pedidos fecha
        case 1:

            busquedaMasViejo(char arregloChar[])
            pause();

            break;

        /// Listar pedidos por cliente
        case 2:

            printf("Que cliente quiere buscar? Ingrese el ID\n");
            scanf("%i", &idClienteAbuscar);

            mostrarPedidosDeUnCliente (char nombreArchivo[],int idClienteAbuscar, int contadorPedidos[]);
            pause();

            break;

        /// Listar top 10 clientes
        case 3:

            listarTopTenClientes (char arregloChar[],int contadorPedidos[]);
            pause();

            break;

        /// Listar peor cliente
        case 4:

            buscarPeorCliente (char arregloChar[],int contadorPedidos[]);
            pause();

            break;

        }

    }while(seguir=='s');


}



void listarTopTenClientes (char nombreArch[],int contadorPedidos[]){

    FILE * archi=fopen(nombreArch,"rb");

    int top10clientes[10];
    char opcion;
    int IDmasGrande=0;
    stPedido pedido;
    int MasGrande=0;
    int i=0;
    IDmasGrande=pedido.idCliente;

    if(archi!=NULL){
            while(i<10){

        while(fread(&pedido,sizeof(stCliente),1,archi)>0){
            if((contadorPedidos[pedido.idCliente]>IDmasGrande) && (contadorPedidos[pedido.idCliente]<contadorPedidos[MasGrande])){
                IDmasGrande=pedido.idCliente;
            }

        }
        top10clientes[i]=IDmasGrande;
        MasGrande=IDmasGrande;
         i++;
        }

        printf("Quiere ver los mejores clientes? S/N\n");
        fflush(stdin);
        scanf("%c", &opcion);

        if(opcion=='s'){

            mostrarTopTenClientes(top10clientes);

        }

        fclose(archi);
    }
}

void mostrarTopTenClientes (int top10clientes[]){

    printf("\nMejores clientes: ");

    for(int i=0;i<10;i++){

        printf("\n Cliente: %i", top10clientes[i]);

    }

}

//busqueda del peor cliente

void buscarPeorCliente (char archivo[],int contadorPedidos[]){

    FILE*archi=fopen(archivo,"rb");


    stPedido pedido;
    int IDdelPeor=contadorPedidos[0];
    int i=0;

    if(archi!=NULL){
        while(fread(&pedido,sizeof(stCliente),1,archi)>0){
            if((contadorPedidos[pedido.idCliente]<IDdelPeor)){
                IDdelPeor=pedido.idCliente;
            }

        }
        printf("\nEl ID del peor cliente es: %d",IDdelPeor);
    }
        fclose(archi);
}

//busqueda pedido mas viejo

void busquedaMasViejo(char archivo[]){

    FILE * archi=fopen(archivo,"r+b");

    stPedido pedidos
    stFecha aux1;
    stFecha aux2;


    while(fread(&pedidos,sizeof(stPedido),1,archi)>0){

        aux1.anio=pedidos.fecha.anio;
        aux1.mes=pedidos.fecha.mes;
        aux1.dia=pedidos.fecha.dia;

    fread(&pedidos,sizeof(stPedido),1,archi);

        aux2.anio=pedidos.fecha.anio;
        aux2.mes=pedidos.fecha.mes;
        aux2.dia=pedidos.fecha.dia;

        if(aux1.anio==aux2.anio){

            if(aux1.mes==aux2.mes){
                if(aux1.dia>=aux1.dia){

                }else{
                    pedidos.fecha.dia=aux1.dia;
                    fseek(archi,sizeof(stPedido)*(-2),SEEK_CUR);
                    pedidos.fecha.dia=aux2.dia;
                    fwrite(&pedidos,sizeof(stPedido),1,archi);

                }
            }else{
                if(aux1.mes>aux2.mes){

                }else{
                    pedidos.fecha.mes=aux1.mes;
                    fseek(archi,sizeof(stPedido)*(-2),SEEK_CUR);
                    pedidos.fecha.mes=aux2.mes;
                    fwrite(&pedidos,sizeof(stPedido),1,archi);
                }

            }
        }else{
            if(aux1.anio>aux2.anio){

            }else{
                pedidos.fecha.anio=aux1.anio;
                fseek(archi,sizeof(stPedido)*(-2),SEEK_CUR);
                pedidos.fecha.anio=aux2.anio;
                fwrite(&pedidos,sizeof(stPedido),1,archi);
            }

        }

    }

    printf("\nLos pedidos estan ordenados de mas viejo a mas joven: ");
    mostrarPedidos(pedidos);
    fclose(archi);

}

//muestro pedido de un cliente elegido por el usuario

void mostrarPedidosDeUnCliente (char nombreArchivo[],int idClienteAbuscar, int contadorPedidos[]){
    FILE * archi=fopen(nombreArchivo,"rb");
    stCliente cliente;
    stPedido pedido;
    int i=0;

    if(archi!=NULL){
        while(fread(&cliente,sizeof(stCliente),1,archi)>0){
            if(pedido.idCliente==idClienteAbuscar){

                mostrarPedidos(pedido);
            }
        }
        fclose(archi);
    }
}













