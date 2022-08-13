#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define N 10
#define ARCHIVO "trabajadores.dat"
#define BAJA_FISICA "empleadito_baja_fisica.dat"


struct trabajador
{
    int id_legajo;
    char nombre[30];
    char categoria;
    float sueldo;
    int activo;

};

void crear_archivo(FILE *archivote);
void agregar_empleado(FILE *archivote);
void listar(FILE *archivote, char* n_archivo);
struct trabajador buscar(FILE *archivote,int flag,int id,char *nombre);
void modificar(FILE *archivote);
void actualizar(FILE *archivote,char categoria[1][3],float porcentaje[3]);
void baja_logica(FILE *archivote);
void baja_fisica(FILE *archivote);

int carga_lejago();
char *carga_nombre();
char carga_categoria();
float carga_flotante(char mensaje[30]);
int carga_activo();

int  valida_cadena(char cadena[30]);
int valida_numero(char numero[30],int punt);
int valida_flag(char activo[30],int verdadero,int falso);
void correcto_texto(char *nombre_persona);


int main(){

system("cls");
int flag=0;
char opcion;
char aux_opcion[30];
int id=0;
char nombre[30];
char caregorias[1][3];
float porcentaje[3];
FILE *archivote;
struct trabajador d_empleado;



do
{
    printf("Ingrese la opcion deseada:\n\n");
	printf("1- Crear Archivo\n");
	printf("2- Dar de alta a un trabajador\n");
	printf("3- Listar los empleados\n");
	printf("4- Buscar registro\n");
	printf("5- Modificar registro\n");
	printf("6- Actualizar sueldos por paritarias\n");
	printf("7- Baja logica\n");
	printf("8- Baja fisica\n");
	printf("9- Listar baja fisica\n");
	printf("10- Salir del programa\n");


   scanf("%d",&opcion);
   fflush(stdin);
    switch (opcion)
    {
    case 1:
        crear_archivo(archivote);
        system("pause");
        break;
    case 2:

        agregar_empleado(archivote);
        system("pause");
        break;
    case 3:
        listar(archivote,ARCHIVO);
        system("pause");
        break;
    case 4:
        system("cls");
        printf("1) Buscar por registro\n");
        printf("2) Buscar por nombre\n");
        scanf("%c",aux_opcion);
        fflush(stdin);
        while (!valida_flag(aux_opcion,49,50))
        {
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Buscar por registro\n");
        printf("2) Buscar por nombre\n");
        scanf("%c",aux_opcion);
        fflush(stdin);
        };
        flag=atof(aux_opcion);
        if (flag==1)
        {
            id=carga_lejago();
            d_empleado=buscar(archivote,flag,id,nombre);
        }
        else
        {
            strcpy(nombre,carga_nombre());
            d_empleado=buscar(archivote,flag,id,nombre);
        }
        switch (d_empleado.activo)
        {
        case 404:
            system("cls");
            printf("No se encontro el registro buscado.\n");
            break;

        default:
            system("cls");
            printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
            printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",d_empleado.id_legajo,d_empleado.nombre,d_empleado.categoria,d_empleado.sueldo,d_empleado.activo);

            break;
        }
        system("pause");
        break;
    case 5:
        modificar(archivote);
        system("pause");
        break;
    case 6:
        for (int i = 0; i < 3; i++)
        {
            system("sys");
            caregorias[1][i]=carga_categoria();
            porcentaje[i]=carga_flotante("Porcentaje");
            system("pause");
        };

        actualizar(archivote,caregorias,porcentaje);
        system("pause");
        break;
    case 7:
        baja_logica(archivote);
        system("pause");
        break;
    case 8:
        baja_fisica(archivote);
        system("pause");
        break;
    case 9:
        listar(archivote,BAJA_FISICA);
        system("pause");
        break;
    default:
        break;
    };
system("cls");
} while (opcion!=10);
return 0;
}
;


void baja_logica(FILE *archivote){

    struct trabajador emp;
    int id, flag=0;
    int aux;
    archivote = fopen(ARCHIVO, "r+b");
    if(archivote==NULL){
        printf("Error en la apertura del archivote\n");
    }
    else{
        system("cls");
        printf("Se mostrara los datos para que observe que legajo quiere dar de baja\n");
        fread(&emp,sizeof(struct trabajador),1,archivote);
        printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
        while(!feof(archivote)){
        printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
        fread(&emp,sizeof(struct trabajador),1,archivote);
            }
        printf("\nAprete una tecla para continuar y escojer un legajo\n");
        system("pause");
        id=carga_lejago();
        fseek(archivote,id*sizeof(struct trabajador),SEEK_SET);
        fread(&emp,sizeof(struct trabajador),1,archivote);
        if(emp.id_legajo==id  && emp.activo==1){
            emp.activo=0;
            fseek(archivote,-sizeof(struct trabajador),SEEK_CUR);
            fwrite(&emp,sizeof(struct trabajador),1,archivote);
            rewind(archivote);
            printf("Empleado dado de baja exitosamente\n");
            printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
            while(!feof(archivote)){
                    switch (emp.activo)
                    {
                    case 1:
                        printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                        fread(&emp,sizeof(struct trabajador),1,archivote);
                        break;
                    default:
                        fread(&emp,sizeof(struct trabajador),1,archivote);
                        break;
                    };
                                }
            }
        else{
            switch (emp.activo)
            {
            case 0:
                system("cls");
                printf("El cliente ya se encuentra inactivo\n");
                break;
            default:
                system("cls");
                printf("El cliente no existe\n");
                break;
            }
        }
    }
    fclose(archivote);
};

void baja_fisica(FILE *archivote){
    system("cls");
    remove(BAJA_FISICA);
    struct trabajador emp;
    archivote=fopen(ARCHIVO,"r+b");
    FILE *aux = fopen(BAJA_FISICA,"w+b");
    if(archivote==NULL){
        printf("Error en la apertura del archivote");
    }else{
        fread(&emp,sizeof(struct trabajador),1,archivote);
        while(!feof(archivote)){
            if(emp.activo==1){
                fseek(aux,sizeof(struct trabajador)*emp.id_legajo, SEEK_CUR);
                fwrite(&emp, sizeof(struct trabajador),1,aux);
                rewind(aux);
                fflush(aux);
            }
            fread(&emp,sizeof(struct trabajador),1,archivote);
        }
    }
    fclose(archivote);
    fclose(aux);
    printf("Bajas exitosas\n");
};

void actualizar(FILE *archivote,char categoria[1][3],float porcentaje[3]){

    struct trabajador emp;
    archivote=fopen(ARCHIVO,"r+b");
    if(archivote==NULL){
        printf("Error en la apertura del archivote");
    }
    else{


    for (int i = 0; i < sizeof(categoria[1]); i++)
    {
        fread(&emp,sizeof(struct trabajador),1,archivote);
        while(!feof(archivote)){

            emp.sueldo*=(1+(porcentaje[i]/100));
                if (emp.categoria==categoria[1][i])
                {
                fseek(archivote,-sizeof(struct trabajador),SEEK_CUR);
                fwrite(&emp,sizeof(struct trabajador),1,archivote);

                fseek(archivote,-sizeof(struct trabajador),SEEK_CUR);
                fread(&emp,sizeof(struct trabajador),1,archivote);

                fread(&emp,sizeof(struct trabajador),1,archivote);
                }
            fread(&emp,sizeof(struct trabajador),1,archivote);
            }
        rewind(archivote);
        }
    }
    fclose(archivote);
    system("cls");
    printf("Se actualizaron los sueldos\n");

};

int valida_cadena(char cadena[30]){

    int i=0,flag=0,cant_letras;
    cant_letras=strlen(cadena);
    while(i<cant_letras && flag==0){
        if (isalpha(cadena[i])!=0)
        {
            i+=1;
        }
        else if (cadena[i]==32)
        {
            i+=1;
        }
        else
        {
            flag=1;
        }
    }
return flag;

};
int valida_numero(char numero[30],int punt){

    int i=0,flag=0,cant_letras,flag_puntos=1;
    cant_letras=strlen(numero);
    while(i<cant_letras && flag==0){
        if (isdigit(numero[i])!=0)
        {
            i+=1;
        }
        else if (numero[i]==punt)
        {
            switch (flag_puntos)
            {
            case 1:
                i+=1;
                flag_puntos=0;
                break;

            default:
                flag=1;
                break;
            };
        }
        else
        {
            flag=1;
        }
    }
return flag;
};
void correcto_texto(char *nombre_persona){

    char tmp[30];
    int flag=0;
    strcpy(tmp,nombre_persona);
    nombre_persona[0]=toupper(tmp[0]);
    for (int i = 1; i < strlen(nombre_persona)  ; i++)
    {

        if ((flag==1))
        {
            nombre_persona[i]=toupper(tmp[i]);
        }
        else
        {
             nombre_persona[i]=tolower(tmp[i]);
        };
        switch (nombre_persona[i])
        {
        case 32:
            flag=1;
            break;
        default:
            flag=0;
            break;
        };
    };

};
int valida_flag(char activo[30],int verdadero,int falso){

    int flag=0;
    if(isdigit(activo[0])!=0 ){
        if (activo[0]==verdadero||activo[0]==falso)
        {
            flag=1;
        }
        else
        {
            flag=0;
        }
    }
    else
    {
        flag=0;
    };
return flag;
};
int carga_lejago(){
system("cls");
struct trabajador emp;
int id;
int cont=1;
int flag=1;
int aux;
char cmp_number[30];
printf("Ingrese el numero de legajo:\n");
gets(cmp_number);
fflush(stdin);
aux=valida_numero(cmp_number,0);
while (aux)
{
    printf("No se admite caracteres ni numeros negativos, Intente nuevamente\n");
    gets(cmp_number);
    fflush(stdin);
    aux=valida_numero(cmp_number,0);
};
id=atof(cmp_number);
return id;
};
char *carga_nombre(){
system("cls");
int aux;
static char nombre[30];
    printf("Ingrese el nombre del trabajador\n");
    gets(nombre);
    fflush(stdin);
    aux=valida_cadena(nombre);
    while (aux)
    {
    printf("No se admite nuemeros, Intente nuevamente\n");
    gets(nombre);
    fflush(stdin);
    aux=valida_cadena(nombre);
    }
    correcto_texto(nombre);
    system("cls");
return nombre;
};



void agregar_empleado(FILE *archivote){

    struct trabajador emp;
    int id;
    int flag=1;
    char cmp_number[30];


    archivote=fopen(ARCHIVO,"r+b");
    if (archivote==NULL)
    {
           printf("Error en la apertura del archivote\n");
    }
    else{
        while (!feof(archivote)&&(flag==1)){


                id=carga_lejago();
                emp=buscar(archivote,1,id,"");
                system("cls");
                if (id==emp.id_legajo)
                {
                    rewind(archivote);
                    printf("Ya existe el numero de lejago, vuelva a intentarlo\n");
                    system("pause");
                    }
                else
                {
                emp.id_legajo=id;

                strcpy(emp.nombre,carga_nombre());
                emp.categoria=carga_categoria();
                emp.sueldo=carga_flotante("sueldo");
                emp.activo=carga_activo();
                system("cls");
                fseek(archivote, sizeof(struct trabajador)*emp.id_legajo, SEEK_CUR);
                fwrite(&emp,sizeof(struct trabajador),1,archivote);
                rewind(archivote);
                fflush(archivote);
                system("cls");
                printf("Desea continuar agregando empleados? Precione: 1 para continuar 0 salir de la carga\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,48))
                {
                    printf("Porfavor ingrese una opcion valida\n1) continuar\n0) salir\n");
                    gets(cmp_number);
                    fflush(stdin);
                }
                flag=atof(cmp_number);
                };
        };
    };
   fclose(archivote);
};




char carga_categoria(){
    system("cls");
    int aux;
    char categ;
    printf("Ingrese la categoria al a que pertenece(A,B,C)\nSi inserta una minuscula sera cambiada por una mayuscula\n");
    scanf("%c",&categ);
    fflush(stdin);
    aux=1;
    while (aux)
    {
        switch (categ)
        {
        case 'A':
        case 'a':
            categ=toupper(categ);
            aux=0;
            break;
        case 'B':
        case 'b':
            categ=toupper(categ);
            aux=0;
            break;
        case 'C':
        case 'c':
            categ=toupper(categ);
            aux=0;
            break;
        default:
            printf("Ingrese una categoria admitida: A, B, C\n");
            scanf("%c",&categ);
            fflush(stdin);
            break;
        }
    }
    return categ;
};
float carga_flotante(char mensaje[30]){
    system("cls");
    char cmp_number[30];
    int aux;
    float sueldo;
    printf("Ingrese el %s correspondiente\n",mensaje);
    gets(cmp_number);
    fflush(stdin);
    aux=valida_numero(cmp_number,46);
    while (aux)
    {
        printf("No se admite caracteres ni numeros negativos, Intente nuevamente\n");
        gets(cmp_number);
        fflush(stdin);
        aux=valida_numero(cmp_number,46);
    };
    sueldo=atof(cmp_number);
    return sueldo;
};
int carga_activo(){
    system("cls");
    char cmp_number[30];
    int activo;
    printf("Es un trabajador activo? 1 para si, 0 para no\n");
    gets(cmp_number);
    fflush(stdin);
    while (!valida_flag(cmp_number,49,48))
    {
        printf("Porfavor ingrese una opcion valida (1 para si, 0 para no)\n");
        gets(cmp_number);
        fflush(stdin);
    }
    activo=atof(cmp_number);
    return activo;
};





void listar(FILE *archivote, char* n_archivo){

    struct trabajador emp;
    int flag;
    char aux[1];
    archivote=fopen(n_archivo,"rb");
    if (archivote==NULL)
    {
        printf("Error en la apertura del archivote");
    }
    else
    {
        system("cls");
        printf("1) Listar todos los empleados\n");
        printf("2) Listar todos los empleados activos\n");
        scanf("%c",aux);
        fflush(stdin);
        while (!valida_flag(aux,49,50)){
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Listar todos los empleados\n");
        printf("2) Listar todos los empleados activos\n");
        scanf("%c",aux);
        fflush(stdin);
        }
        flag=atof(aux);
        fread(&emp,sizeof(struct trabajador),1,archivote);
        system("cls");
        printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
        while(!feof(archivote)){
            if (flag==1)
            {
                printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                fread(&emp,sizeof(struct trabajador),1,archivote);
            }
            else if (flag==2)
            {
                switch (emp.activo)
                {
                case 1:
                    printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                    fread(&emp,sizeof(struct trabajador),1,archivote);
                    break;
                default:
                    fread(&emp,sizeof(struct trabajador),1,archivote);
                    break;
                }
            }

        };
    }
    fclose(archivote);
};

void crear_archivo(FILE *archivote){

    struct trabajador emp;
    char *v_nombre[N]={"Rodrigo Noya ","Denis vera","Marcos Maldini","Marcos Peralta","eduardo Torrez","Salazar Guzman","Esteban Altamar","Altamar Gutierrez","Marta Silvestre","Gutierrez Soledad"};
    char v_categoria[1][N]={'A','B','C','B','A','A','C','A','B','B'};
    float sueldo[N]={90000.00,70000.00,40000.00,80000.00,120000.00,15000.00,50000.00,70000.00,60000.00,90000.00};
    int activo[N]={1,0,1,1,1,0,1,1,0,1};
archivote=fopen(ARCHIVO,"rb");
if(archivote==NULL){
archivote=fopen(ARCHIVO,"w+b");
for (int i = 0; i < N; i++)
{
    emp.id_legajo=i+1;
    strcpy(emp.nombre,v_nombre[i]);
    emp.categoria=v_categoria[0][i];
    emp.sueldo=sueldo[i];
    emp.activo=activo[i];
    fseek(archivote,sizeof(struct trabajador)*(i+1),SEEK_CUR);
    fwrite(&emp,sizeof(struct trabajador),1,archivote);
    rewind(archivote);
    fflush(archivote);
}
    fclose(archivote);
}
else
{
    printf("El archivote ya existe\n");
}
};

struct trabajador buscar(FILE *archivote,int flag,int id,char *nombre){

    struct trabajador emp;
    archivote=fopen(ARCHIVO,"rb");
    if (archivote==NULL)
    {
           printf("Error en la apertura del archivote\n");
    }
    else
    {
        switch (flag)
        {
        case 1:
            fseek(archivote,sizeof(struct trabajador)*id, SEEK_CUR);
            fread(&emp,sizeof(struct trabajador),1,archivote);
            if (id==emp.id_legajo)
            {
            system("cls");
            fclose(archivote);
            return emp;
            };
            break;
        case 2:
            system("cls");
            while (!feof(archivote))
            {
                fread(&emp,sizeof(struct trabajador),1,archivote);
                if (strstr(nombre,emp.nombre)!=NULL&&emp.id_legajo!=0)
                {
                    return emp;
                    fclose(archivote);

                }
            }
            break;
        default:
            break;
        }

    }
emp.activo=404;
return emp;
};


void modificar(FILE *archivote){

    struct trabajador emp;
    char cmp_number[30];
    char nombre[30];
    int flag;
    int id;
    int confirmar;
    archivote=fopen(ARCHIVO,"r+b");
    if (archivote==NULL)
    {
           printf("Error en la apertura del archivote\n");
    }
    else
    {

        system("cls");
        printf("1) Modificar por registro\n");
        printf("2) Modificar por nombre\n");
        gets(cmp_number);
        fflush(stdin);
        while (!valida_flag(cmp_number,49,50))
        {
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Modificar por registro\n");
        printf("2) Modificar por nombre\n");
        gets(cmp_number);
        fflush(stdin);
        };
        flag=atof(cmp_number);


        switch (flag)
        {
        case 1:
            system("cls");
            id=carga_lejago();
            emp=buscar(archivote,flag,id,"");
            if (emp.activo==404)
            {
                system("cls");
                printf("No se encontro el registro para modificar\n");
                break;
            }


                system("cls");
                emp.categoria=carga_categoria();
                emp.sueldo=carga_flotante("sueldo");

                system("cls");

                printf("Esta seguro que quiere modificar los datos de: \t%s\n",emp.nombre);
                printf("\t1) CONFIRMAR\n");
                printf("\t2) RECHAZAR\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,50))
                {
                    printf("Porfavor ingrese una opcion valida\n");
                    printf("\t1) CONFIRMAR\n");
                    printf("\t2) RECHAZAR\n");
                    gets(cmp_number);
                    fflush(stdin);
                };
                flag=atof(cmp_number);
                system("cls");
                switch (flag)
                {
                case 1:
                    fseek(archivote,sizeof(struct trabajador)*emp.id_legajo,SEEK_CUR);
                    fwrite(&emp,sizeof(struct trabajador),1,archivote);
                    fflush(archivote);
                    fclose(archivote);
                    printf("se modifico\n");
                    break;
                case 2:
                    fclose(archivote);
                    break;
                default:
                    break;
                };
            system("cls");

            break;

        case 2:
            if (emp.activo==404)
            {
                system("cls");
                printf("No se encontro el registro para modificar\n");
                break;
            }
            system("cls");
            strcpy(nombre,carga_nombre());
            emp=buscar(archivote,flag,0,nombre);

            emp.categoria=carga_categoria();
            emp.sueldo=carga_flotante("sueldo");

                system("cls");

                printf("Esta seguro que quiere modificar los datos de: \t%s\n",nombre);
                printf("\t1) CONFIRMAR\n");
                printf("\t2) RECHAZAR\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,50))
                {
                    printf("Porfavor ingrese una opcion valida\n");
                    printf("\t1) CONFIRMAR\n");
                    printf("\t2) RECHAZAR\n");
                    gets(cmp_number);
                    fflush(stdin);
                }
                flag=atof(cmp_number);
                system("cls");
                switch (flag)
                {
                case 1:
                    system("cls");
                    fseek(archivote,sizeof(struct trabajador)*emp.id_legajo,SEEK_CUR);
                    fwrite(&emp,sizeof(struct trabajador),1,archivote);
                    fflush(archivote);
                    fclose(archivote);
                    printf("se modifico\n");

                    break;
                case 2:
                    fclose(archivote);
                    break;
                default:
                    break;
                }
                 break;
        default:
            break;
        };


    } ;
};

