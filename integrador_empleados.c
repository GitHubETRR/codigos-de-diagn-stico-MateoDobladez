#include <stdio.h>
#include <string.h>

#define MAX_TXT 50
#define MAX_EMPLEADOS 5

struct empleado {
    char nombre[MAX_TXT];
    int edad;
    float salario;
};

void limpiarBuffer(void);
void ingresarDatos(struct empleado empleados[], int *cantidad_empleados);
void mostrarDatos(struct empleado empleados[], int cantidad_empleados);
void procesarDatos(struct empleado empleados[], int cantidad_empleados);

int main() {
    struct empleado empleados[MAX_EMPLEADOS];
    int cantidad_empleados = 0;
    int opcion;

    do {
        printf("\nMenu de empleados\n");
        printf("1. Ingresar empleado\n");
        printf("2. Procesar datos\n");
        printf("3. Mostrar empleados\n");
        printf("4. Salir del programa\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                ingresarDatos(empleados, &cantidad_empleados);
                break;
            case 2:
                procesarDatos(empleados, cantidad_empleados);
                break;
            case 3:
                mostrarDatos(empleados, cantidad_empleados);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 4);
    
    return 0;
}

void limpiarBuffer() {
    while (getchar() != '\n');
}

void ingresarDatos(struct empleado empleados[], int *cantidad_empleados) {
    if (*cantidad_empleados < MAX_EMPLEADOS) {
        printf("Ingrese el nombre del empleado: ");
        scanf("%s", empleados[*cantidad_empleados].nombre); 
        limpiarBuffer();
        printf("Ingrese la edad: ");
        scanf("%d", &empleados[*cantidad_empleados].edad);
        printf("Ingrese el salario: ");
        scanf("%f", &empleados[*cantidad_empleados].salario);
        (*cantidad_empleados)++;
        printf("Empleado agregado con éxito!\n");
    } else {
        printf("No se pueden agregar más empleados\n");
    }
}

void mostrarDatos(struct empleado empleados[], int cantidad_empleados) {
    if (cantidad_empleados == 0) {
        printf("No hay empleados para mostrar.\n");
        return;
    }
    printf("-- EMPLEADOS --");
    for (int i = 0; i < cantidad_empleados; i++) {
        printf("\nEmpleado: %s\n", empleados[i].nombre);
        printf("Edad: %d\n", empleados[i].edad);
        printf("Salario: $%f\n", empleados[i].salario);
    }
}

void procesarDatos(struct empleado empleados[], int cantidad_empleados) {
    if (cantidad_empleados == 0) {
        printf("No hay empleados para procesar.\n");
        return;
    }

    float suma_salarios = 0;
    float salario_maximo = empleados[0].salario;
    char nombre_maximo[MAX_TXT];
    strcpy(nombre_maximo, empleados[0].nombre);

    for (int i = 0; i < cantidad_empleados; i++) {
        suma_salarios += empleados[i].salario;
        if (empleados[i].salario > salario_maximo) {
            salario_maximo = empleados[i].salario;
            strcpy(nombre_maximo, empleados[i].nombre);
        }
    }

    float promedio_salarios = suma_salarios / cantidad_empleados;
    printf("Promedio de salarios: $%f\n", promedio_salarios);
    printf("Empleado con el salario más alto: %s ($%f)\n", nombre_maximo, salario_maximo);
}