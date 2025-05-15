#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_TXT 50
#define AGREGAR 1
#define MOSTRAR 2 
#define TOMAR 3
#define LIBERAR 4
#define PRESENTE 1

typedef struct Alumno {
    char nombre[TAM_TXT];
    bool asistencia;
    struct Alumno* siguiente;
} Alumno_t;

Alumno_t* agregarAlumno(Alumno_t* lista);
void mostrarLista(Alumno_t* lista);
void tomarAsistencia(Alumno_t* lista);
void liberarMemoria(Alumno_t* lista);

int main() {
    Alumno_t* lista = NULL;
    int opcion;

    do {
        printf("\nMenu de opciones:\n");
        printf("1. Agregar alumno\n");
        printf("2. Mostrar lista de alumnos\n");
        printf("3. Tomar asistencia\n");
        printf("4. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch(opcion) {
            case AGREGAR:
                lista = agregarAlumno(lista);
                break;
            case MOSTRAR:
                mostrarLista(lista);
                break;
            case TOMAR:
                tomarAsistencia(lista);
                break;
            case LIBERAR:
                liberarMemoria(lista);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
        }
    } while(opcion != 4);

    return 0;
}

Alumno_t* agregarAlumno(Alumno_t* lista) {
    Alumno_t* nuevo = (Alumno_t*) malloc(sizeof(Alumno_t));
    if (!nuevo) {
        printf("Memoria insuficiente\n");
        return lista;
    }
    printf("Ingrese el nombre del alumno: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->asistencia = false;
    if (lista == NULL) {
        nuevo->siguiente = NULL;
        lista = nuevo;
    } else {
        Alumno_t* aux = lista;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo->siguiente = NULL;
    }

    printf("Alumno agregado exitosamente!\n");
    return lista;
}

void mostrarLista(Alumno_t* lista) {
    if (lista == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
    Alumno_t* aux = lista;
    while (aux != NULL) {
        printf("Nombre: %s\n", aux->nombre);
        printf("Asistencia: %s\n", aux->asistencia ? "Presente" : "Ausente");
        printf("------------------------\n");
        aux = aux->siguiente;
    }
}

void tomarAsistencia(Alumno_t* lista) {
    if (lista == NULL) {
        printf("La lista esta vacia\n");
        return;
    }

    Alumno_t* aux = lista;
    while (aux != NULL) {
        printf("Alumno: %s\n", aux->nombre);
        printf("Ingrese 1 si esta presente o 0 si esta ausente: ");
        int respuesta;
        scanf("%d", &respuesta);
        getchar();
        if (respuesta == PRESENTE) {
            aux->asistencia = true;
        } else {
            aux->asistencia = false;
        }
        aux = aux->siguiente;
    }
    printf("Asistencia registrada exitosamente!\n");
}

void liberarMemoria(Alumno_t* lista) {
    Alumno_t* aux = lista;
    while (aux != NULL) {
        Alumno_t* siguiente = aux->siguiente;
        free(aux);
        aux = siguiente;
    }
    lista = NULL;
}
