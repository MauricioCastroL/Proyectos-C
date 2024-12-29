// Autor: Mauricio CAstro Leal
// Fecha: 20/12/2024
// Objetivo: Creación de fichero para estudiantes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINEA 1024 

int listado_csv();
void guardar_csv();
int es_numero(const char *str);
int get_opcion();
char* get_str(void);
int get_int();

void agregar();
void mostrar_todos();
void eliminar();
void buscar();
void modificar();
void limpiar();


struct Estudiantes {
    char nombre[100];
    int notas[10];
    char curso[50];
    int cant_notas;
};

struct Estudiantes stu[100];

int contador_elementos = 0;


int main()
{
    listado_csv();
    
    int opcion;
    limpiar();

    do{
        printf("Opciones del menú\n");
        printf("------------------\n");
        printf("1. Agregar estudiantes\n");
        printf("2. Mostrar estudiantes\n");
        printf("3. Buscar un estudiante\n");
        printf("4. Eliminar un estudiante\n");
        printf("5. Modificar datos de un estudiante\n");
        printf("6. Pulse para salir.\n");

        opcion = get_opcion();

        if ((1 > opcion) || (6 < opcion))
        {
            limpiar();
            printf("Opción no válida.\n");
        }

        if (opcion == 1)
        {
            agregar(); //Agregar estudiante
        }
        else if (opcion == 2)
        {
            mostrar_todos(); //Mostrar todos los estudiante
        }
        else if (opcion == 3)
        {
            buscar(); //Buscar a un estudiante
        }
        else if (opcion == 4)
        {
            eliminar(); //Eliminar a un estudiante
        }
        else if (opcion == 5)
        {
            modificar(); //Modificar datos del estudiante 
        }
        else if (opcion == 6)
        {
            guardar_csv();
            printf("Saliendo...");
            break;
        }
    } while (opcion != 6);
}

void guardar_csv() {
    FILE *archivo = fopen("/home/mauricio/Proyectos C/data.csv", "w");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    // Escribir los datos de cada estudiante sin encabezado
    for (int i = 0; i < contador_elementos; i++) {
        // Escribir el nombre
        fprintf(archivo, "%s,", stu[i].nombre);

        // Escribir las notas
        for (int j = 0; j < stu[i].cant_notas; j++) {
            fprintf(archivo, "%d", stu[i].notas[j]);
            if (j < stu[i].cant_notas - 1) {
                fprintf(archivo, ","); // Separa las notas con comas
            }
        }

        // Escribir el curso
        fprintf(archivo, ",%s", stu[i].curso);

        // Escribir una nueva línea al final de cada estudiante
        fprintf(archivo, "\n");
    }

    fclose(archivo);
    printf("Los cambios se han guardado correctamente en el archivo CSV.\n");
}


int listado_csv() 
{
    char linea[MAX_LINEA];

    FILE *archivo = fopen("/home/mauricio/Proyectos C/data.csv", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar salto de línea y verificar que la línea no esté vacía
        linea[strcspn(linea, "\n")] = 0;

        if (strlen(linea) == 0) {  // Evitar procesar líneas vacías
            continue;
        }

        struct Estudiantes estudiante;
        estudiante.cant_notas = 0;
        estudiante.curso[0] = '\0'; 

        char *token = strtok(linea, ","); 
        if (token != NULL) {
            strncpy(estudiante.nombre, token, sizeof(estudiante.nombre) - 1);
            estudiante.nombre[sizeof(estudiante.nombre) - 1] = '\0'; 
        }

        token = strtok(NULL, ",");
        while (token != NULL && es_numero(token) && estudiante.cant_notas < 10) {
            estudiante.notas[estudiante.cant_notas] = atoi(token); 
            estudiante.cant_notas++;
            token = strtok(NULL, ",");  
        }

        if (token != NULL) {
            if (!es_numero(token)) {
                strncpy(estudiante.curso, token, sizeof(estudiante.curso) - 1);
                estudiante.curso[sizeof(estudiante.curso) - 1] = '\0'; 
            }
        }

        stu[contador_elementos] = estudiante;
        contador_elementos++;
    }

    fclose(archivo); 

    return 0;
}


int es_numero(const char *str) 
{
    while (*str) {
        if (!isdigit(*str)) {
            return 0;  
        }
        str++;
    }
    return 1;  
}

int get_opcion()
{
    int num;
    char ch;

    while (1)
    {
        printf("Su opción: ");
        
        if (scanf("%d", &num) == 1)
        {
            return num;
        }
        else
        {
            printf("Entrada inválida.\n");

            while ((ch = getchar()) != '\n' && ch != EOF); 
        }
    }
}

char* get_str(void)
{
    char *str = NULL;
    size_t size = 0;

    if (getline(&str, &size, stdin) == -1) 
    {
        printf("Error al leer la entrada.\n");
        exit(1);
    }

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') 
    {
        str[len - 1] = '\0';  
    }

    return str;
}

int get_int()
{
    int num;
    char ch;

    while (1)
    {
        if (scanf("%d", &num) == 1)
        {
            return num;
        }
        else
        {
            printf("Entrada inválida.\n");

            while ((ch = getchar()) != '\n' && ch != EOF); 
        }
    }
}

void agregar()
{
    int x;

    printf("\nA cuantos estudiantes desea agregar: ");
    x = get_int();

    getchar();

    for (int i = 0; i < x; i++)
    {
        printf("\nIngrese el nombre del estudiante: "); 
        strcpy(stu[contador_elementos].nombre, get_str());

        printf("\nIngrese la cantidad de notas del estudiante a ingresar: ");
        stu[contador_elementos].cant_notas = get_int();

        for (int j = 0; j < stu[contador_elementos].cant_notas; j++){
            printf("Ingrese la nota del estudiante: ");
            stu[contador_elementos].notas[j] = get_int();
        }

        getchar();

        printf("\nIngrese el curso del estudiante: ");
        strcpy(stu[contador_elementos].curso, get_str());

        contador_elementos++;
    }
    
}

void mostrar_todos()
{

    if (contador_elementos == 0) {
        printf("\nNo hay estudiantes registrados.\n");
        return;
    }

    for(int i = 0; i < contador_elementos; i++)
    {
        printf("\n%i: %s, ", i+1, stu[i].nombre);
        printf("Notas:");

        for(int z = 0; z < stu[i].cant_notas; z++)
        {
            printf(" %d", stu[i].notas[z]);
        }
        printf(", Curso: ");
        printf("%s\n", stu[i].curso);
    }
}

void eliminar()
{
    char nombre_detele[100];

    getchar();

    printf("\nIngrese el nombre del estudiante a eliminar: ");
    strcpy(nombre_detele, get_str());

    for (int i = 0; i < contador_elementos; i++)
    {
        if (strcmp(nombre_detele, stu[i].nombre) == 0)
        {
            for (int j = i; j < contador_elementos - 1; j++)
            {
                stu[j] = stu[j + 1]; 
            }
            contador_elementos--; 

            printf("Estudiante eliminado correctamente.\n");

            return;
        }

    }

    printf("\nEl estudiante no estaba en la lista.\n");
}

void buscar()
{
    char nombre_serch[100];

    getchar();

    printf("\nIngrese el nombre del estudiante a buscar: ");
    strcpy(nombre_serch, get_str());

    for (int i = 0; i < contador_elementos; i++)
    {
        if (strcmp(nombre_serch, stu[i].nombre) == 0 )
        {
            printf("\nEstudiante encontrado...\n");

            printf("\n%i: %s, ", i+1, stu[i].nombre);
            printf("Notas:");

            for(int z = 0; z < stu[i].cant_notas; z++)
            {
                printf(" %d", stu[i].notas[z]);
            }
            printf(", Curso: ");
            printf("%s\n", stu[i].curso);

            return;
        }
    }

    printf("\nEstudiante no encontrado.\n");
}


void modificar()
{
    char nombre_change[100];

    getchar();

    printf("\nIngrese el nombre del estudiante a modificar sus datos: ");
    strcpy(nombre_change, get_str());

    for (int i = 0; i < contador_elementos; i++)
    {
        if (strcmp(nombre_change, stu[i].nombre) == 0){
            printf("\nIngrese las modificaciones de: %s\n", nombre_change);

            printf("Debe ingresar todas las notas corregidas, ¿Cuantas ingresara?: ");
            stu[i].cant_notas = get_int();

            getchar();
            
            for(int z = 0; z < stu[i].cant_notas; z++)
            {
                printf("\nIngrese la nota del estudiante: ");
                stu[i].notas[z] = get_int();
            }
            
            getchar();

            printf("\nIngrese el curso del estudiante: ");
            strcpy(stu[i].curso, get_str());
            
            printf("\nDatos cambiado exitosamente!\n");

            return;
        }
    }
    
    printf("\nEstudiante no encontrado..\n");

}

void limpiar()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}