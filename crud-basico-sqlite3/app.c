/*
Crud Basico en C
y SQLite
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sqlite3.h"
//structura inicial de la tabla 
#define CREATE_TABLE \
                    "CREATE TABLE IF NOT EXISTS tarea"\
                    "("\
                    "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL"\
                    ",nombre TEXT NOT NULL"\
                    ",descripcion TEXT NOT NULL"\
                    ",estado TEXT NOT NULL"\
                    ")"

int registro(void*,int, char**, char**);
int errores(sqlite3*);
void inicio_db(sqlite3*);
void insertar_registro(sqlite3*);
void mostrar_registros(sqlite3*);
void mostrar_registro(sqlite3*);
void actualizar_registro(sqlite3*);
void eliminar_registro(sqlite3*);
bool menu(sqlite3*);
int main(){
    //base de datos
    sqlite3 *db = NULL;
    bool continuar=false;
    if (sqlite3_open("BaseDeDatos.db",&db)!= SQLITE_OK){
        printf("error al conectar a la base de datos\n");
    }else{
        printf("conectado correctamente a la base de datos\n");
        inicio_db(db);
    }
    //core 
    do{
        continuar = menu(db);
    }while(continuar);

    sqlite3_close(db);
    printf("Preciona cualquier tecla para continuar...\n");
    getchar();
    return 0;

}
//
bool menu(sqlite3 *db){
    int opc;
    
    printf("Indique la accion a realizar...\n1. Agregar Tarea\n2. Ver Tareas\n3. Buscar tarea\n4. Buscar tarea y cambiar estado\n5. Buscar una tarea y eliminarla \n6. Salir\n");
    fflush( stdin );
    scanf("%d",&opc);
    system("cls");
    switch (opc){
        case 1:{
                    insertar_registro(db);
                    return true;
                    break;
                }
        case 2:{
                    mostrar_registros(db);
                    return true;
                    break;
                }
        case 3:{
                    mostrar_registro(db);
                    return true;
                    break;
                } 
        case 4:{
                    actualizar_registro(db);
                    return true;
                    break;
                }   
        case 5:{
                    eliminar_registro(db);
                    return true;
                    break;
                }   
        case 6:{
                    return false;
                    break;
                }    
        default:{
            printf("opcion invalida\n");
        }
        return true;return true;
    }
}

void eliminar_registro(sqlite3 *db){
    char sql[500];
    int id;
    printf("ingrese el numero de la tarea a Eliminar\n");
    fflush( stdin );
    scanf("%d",&id);
    
    sprintf(sql,"DELETE FROM tarea WHERE id=%d",id);
    
    if(sqlite3_exec(db,sql,registro,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }
    system("pause");
    system("cls");
}
void actualizar_registro(sqlite3 *db){
    char sql[500];
    int id,estado;
    printf("ingrese el numero de la tarea a buscar actualizar\n");
    fflush( stdin );
    scanf("%d",&id);
    printf("ingrese\n1. COMPLETADA \n2. CANCELADA\n Para Cancelar esta accion precionar cualquier tecla (deja la tarea con estado SIN COMPLETAR)\n");
    fflush( stdin );
    scanf("%d",&estado);
    if (!(estado== 1 || estado == 2)){
        printf("accion cancelada");
    }
    if(estado==1){
        sprintf(sql,"UPDATE tarea SET estado='COMPETADA' WHERE id=%d",id);
    }
    if(estado==2){
        sprintf(sql,"UPDATE tarea SET estado='CANCELADA' WHERE id=%d",id);
    }
    if(sqlite3_exec(db,sql,registro,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }
    system("pause");
    system("cls");
}
void insertar_registro(sqlite3 *db){
    int id;
    char nombre[50];
    char descripcion[250];
    char sql[500]; 

    printf("ingrese el nombre de la tarea...\n");
    fflush( stdin );
    fgets(nombre,50,stdin);
    strtok(nombre,"\n");
    printf("ingrese la descripcion de la tarea...\n");
    fflush( stdin );
    fgets(descripcion,250,stdin);
    strtok(descripcion,"\n");
    sprintf(sql,"INSERT INTO tarea(id,nombre,descripcion,estado) Values (NULL,'%s','%s','SIN COMPLETAR')",nombre,descripcion);

    if(sqlite3_exec(db,sql,NULL,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }else{
        printf("Registro Guardado Correctamente!\n");
    }
    system("pause");
    system("cls");
}
void mostrar_registros(sqlite3 *db){
    char sql[500];

    sprintf(sql,"SELECT * FROM tarea");

    if(sqlite3_exec(db,sql,registro,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }
    system("pause");
    system("cls");
}
void mostrar_registro(sqlite3 *db){
    char sql[500];
    int id;
    printf("ingrese el numero de la tarea a buscar a buscar\n");
    fflush( stdin );
    scanf("%d",&id);

    sprintf(sql,"SELECT * FROM tarea WHERE id=%d",id);

    if(sqlite3_exec(db,sql,registro,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }
    system("pause");
    system("cls");
}
void inicio_db(sqlite3 *db){
    if(sqlite3_exec(db,CREATE_TABLE,NULL,NULL,NULL)!= SQLITE_OK){
        errores(db);
    }
}
int errores(sqlite3 *db){
    fprintf(stderr,"error: %s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}
int registro(void *ptr,int NumeroDeRegistros, char **ValorDeLaCelda, char **NombresDeLaColumnas){
    int i;
    (void) ptr;
    for (i=0 ; i < NumeroDeRegistros;++i){
        printf("%s: %s\n",NombresDeLaColumnas[i],ValorDeLaCelda[i]);
    }
    printf("\n");
    return 0;
}