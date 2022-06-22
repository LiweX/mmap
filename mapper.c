#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

struct data_struct
{
    unsigned short int          version;        //  Versión del dato n1.                            2
    unsigned short int          drxVersion;     //  Versión del DRX que generó el dato n1.          2
    const int                   RESERVED_1;     //  RESERVADO                                       4
    double                      initCW;         //  Inicio de la ventana de recepción, en segundos. 8
    float                       azimuth;        //  Apuntamiento acimut en grados.                  4
    float                       elevation;      //  Apuntamiento elevación en grados.               4
    unsigned short int          idVolumen;      //  Identificador de volumen.                       2
    unsigned short int          idBarrido;      //  Identificador de barrido.                       2
    unsigned short int          idCnjunto;      //  Identificador de conjunto.                      2
    unsigned short int          idGrupo;        //  Identificador de grupo.                         2
    unsigned short int          idPulso;        //  Identificador de pulso.                         2
    bool                        iniBarrido;     //  Bandera del primer pulso de barrido.            1
    bool                        finBarrido;     //  Bandera del último pulso de barrido.            1
    bool                        finGrupo;       //  Bandera del último pulso del grupo.             1
    bool                        inhibido;       //  Bandera de transmisión inhibida.                1
    unsigned short int          validSamples;   //  Cantidad de muestras complejas válidas.         2
    unsigned short int          nroAdquisicion; //  Contador de adquisiciones.                      2
    const unsigned short int    RESERVED_2;     //  RESERVADO                                       2
    unsigned int                nroSecuencia;   //  Número de secuencia.                            4
    unsigned long int           readTime_high;  //  Campo alto de la marca de tiempo.               8
    unsigned long int           readTime_low;   //  Campo bajo de la marca de tiempo.               8
    const unsigned long int     RESERVED_3[8];  //  RESERVADO                                       64
};

int main(){

    FILE *raw = fopen("./rawdata/datos","rb");
    if(raw==NULL){
        printf("Error al abrir binario");
        exit(EXIT_FAILURE);
    }

    int raw_fd = fileno(raw);
    if(raw_fd == -1){
        printf("Error al obtener file descriptor");
        exit(EXIT_FAILURE);
    }

    struct stat binary_stats;
    int value = fstat(raw_fd,&binary_stats);
    if(value == -1){
        printf("Error al obtener stats");
        exit(EXIT_FAILURE);
    }

    int binary_size = binary_stats.st_size;
    int struct_size = sizeof(struct data_struct);
    int cant_muestras = binary_size/struct_size;

    //struct data_struct muestras[cant_muestras];

    printf("File size: %d bytes\nStruct size: %d bytes\nCantidad de muestras: %d\n",binary_size,struct_size,cant_muestras);

    exit(EXIT_SUCCESS);
}