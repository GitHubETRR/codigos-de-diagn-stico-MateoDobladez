#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOMBRE 50

typedef struct jugador {
    char nombre[MAX_NOMBRE];
    int numero;
    int tarjetasAmarillas;
    int tarjetasRojas;
    struct jugador *sig;
} jugador_t;

typedef struct equipo {
    char nombre[MAX_NOMBRE];
    jugador_t *jugadores;
    struct equipo *sig;
} equipo_t;

typedef struct partido {
    equipo_t *equipo1;
    equipo_t *equipo2;
    int goles1;
    int goles2;
    struct partido *sig;
} partido_t;

typedef struct torneo {
    char nombre[MAX_NOMBRE];
    equipo_t *equipos;
    partido_t *partidos;
} torneo_t;

torneo_t torneoGlobal;

typedef enum {
    MENU_CREAR_TORNEO = 1,
    MENU_AGREGAR_EQUIPO,
    MENU_AGREGAR_JUGADOR,
    MENU_MOSTRAR_EQUIPOS,
    MENU_MOSTRAR_JUGADORES,
    MENU_ASIGNAR_TARJETA,
    MENU_SORTEAR_SEMIFINALES,
    MENU_JUGAR_PARTIDO,
    MENU_MOSTRAR_PARTIDOS,
    MENU_SALIR
} menu_opcion_t;

void crearTorneo();
equipo_t* crearEquipo();
void agregarEquipo();
jugador_t* crearJugador();
void agregarJugador();
void mostrarEquipos();
void mostrarJugadores();
void asignarTarjeta();
void sortearSemifinales();
void jugarPartido();
equipo_t* sortearGanador(equipo_t* e1, equipo_t* e2);
void mostrarPartidos();
void menu();

int main() {
    menu();
    return 0;
}

void crearTorneo() {
    printf("Ingrese el nombre del torneo: ");
    fgets(torneoGlobal.nombre, MAX_NOMBRE, stdin);
    torneoGlobal.equipos = NULL;
    torneoGlobal.partidos = NULL;
    printf("Torneo '%s' creado.\n", torneoGlobal.nombre);
}

equipo_t* crearEquipo() {
    equipo_t *nuevo = (equipo_t*) malloc(sizeof(equipo_t));
    printf("Ingrese el nombre del equipo: ");
    fgets(nuevo->nombre, MAX_NOMBRE, stdin);
    nuevo->jugadores = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

void agregarEquipo() {
    equipo_t *nuevo = crearEquipo();
    if (torneoGlobal.equipos == NULL) {
        torneoGlobal.equipos = nuevo;
    } else {
        equipo_t *temp = torneoGlobal.equipos;
        int contador = 1;
        while (temp->sig) {
            contador++;
            temp = temp->sig;
        }
        if (contador >= 4) {
            printf("Ya hay 4 equipos registrados.\n");
            free(nuevo);
            return;
        }
        temp->sig = nuevo;
    }
    printf("Equipo '%s' agregado.\n", nuevo->nombre);
}

jugador_t* crearJugador() {
    jugador_t *nuevo = (jugador_t*) malloc(sizeof(jugador_t));
    printf("Nombre del jugador: ");
    fgets(nuevo->nombre, MAX_NOMBRE, stdin);
    printf("Número del jugador: ");
    scanf("%d", &nuevo->numero);
    getchar();
    nuevo->tarjetasAmarillas = 0;
    nuevo->tarjetasRojas = 0;
    nuevo->sig = NULL;
    return nuevo;
}

void agregarJugador() {
    char nombreEquipo[MAX_NOMBRE];
    printf("Ingrese el nombre del equipo al que desea agregar un jugador: ");
    fgets(nombreEquipo, MAX_NOMBRE, stdin);

    equipo_t *equipoActual = torneoGlobal.equipos;
    while (equipoActual && strcmp(equipoActual->nombre, nombreEquipo) != 0) {
        equipoActual = equipoActual->sig;
    }

    if (!equipoActual) {
        printf("Equipo no encontrado.\n");
        return;
    }

    jugador_t *nuevo = crearJugador();
    if (!equipoActual->jugadores) {
        equipoActual->jugadores = nuevo;
    } else {
        jugador_t *actual = equipoActual->jugadores;
        while (actual->sig) actual = actual->sig;
        actual->sig = nuevo;
    }
    printf("Jugador agregado al equipo '%s'.\n", equipoActual->nombre);
}

void mostrarEquipos() {
    equipo_t *actual = torneoGlobal.equipos;
    printf("Equipos en el torneo '%s':\n", torneoGlobal.nombre);
    while (actual) {
        printf("- %s\n", actual->nombre);
        actual = actual->sig;
    }
}

void mostrarJugadores() {
    char nombreEquipo[MAX_NOMBRE];
    printf("Ingrese el nombre del equipo: ");
    fgets(nombreEquipo, MAX_NOMBRE, stdin);

    equipo_t *equipoActual = torneoGlobal.equipos;
    while (equipoActual && strcmp(equipoActual->nombre, nombreEquipo) != 0) {
        equipoActual = equipoActual->sig;
    }

    if (!equipoActual) {
        printf("Equipo no encontrado.\n");
        return;
    }

    jugador_t *jugadorActual = equipoActual->jugadores;
    printf("Jugadores del equipo '%s':\n", equipoActual->nombre);
    while (jugadorActual) {
        printf("  #%d - %s | Amarillas: %d | Rojas: %d\n", jugadorActual->numero, jugadorActual->nombre, jugadorActual->tarjetasAmarillas, jugadorActual->tarjetasRojas);
        jugadorActual = jugadorActual->sig;
    }
}

void asignarTarjeta() {
    char nombreEquipo[MAX_NOMBRE];
    int numero;
    printf("Ingrese nombre del equipo: ");
    fgets(nombreEquipo, MAX_NOMBRE, stdin);

    equipo_t *equipoActual = torneoGlobal.equipos;
    while (equipoActual && strcmp(equipoActual->nombre, nombreEquipo) != 0)
        equipoActual = equipoActual->sig;
    if (!equipoActual) {
        printf("Equipo no encontrado.\n");
        return;
    }

    printf("Número del jugador: ");
    scanf("%d", &numero);
    getchar();

    jugador_t *jugadorActual = equipoActual->jugadores;
    while (jugadorActual && jugadorActual->numero != numero)
        jugadorActual = jugadorActual->sig;
    if (!jugadorActual) {
        printf("Jugador no encontrado.\n");
        return;
    }

    int tipo;
    printf("1. Tarjeta amarilla\n2. Tarjeta roja\nSeleccione tipo de tarjeta: ");
    scanf("%d", &tipo);
    getchar();
    if (tipo == 1) jugadorActual->tarjetasAmarillas++;
    else if (tipo == 2) jugadorActual->tarjetasRojas++;
    else printf("Opción inválida.\n");

    printf("Tarjeta asignada a %s.\n", jugadorActual->nombre);
}

equipo_t* sortearGanador(equipo_t* e1, equipo_t* e2) {
    if (rand() % 2 == 0) {
        printf("Empate! El ganador por sorteo es: %s\n", e1->nombre);
        return e1;
    } else {
        printf("Empate! El ganador por sorteo es: %s\n", e2->nombre);
        return e2;
    }
}

void sortearSemifinales() {
    equipo_t *vector[4];
    equipo_t *equipoActual = torneoGlobal.equipos;
    int i = 0;
    while (equipoActual && i < 4) {
        vector[i++] = equipoActual;
        equipoActual = equipoActual->sig;
    }
    if (i < 4) {
        printf("Debe haber 4 equipos para sortear semifinales.\n");
        return;
    }

    srand(time(NULL));
    for (int j = 0; j < 4; j++) {
        int k = rand() % 4;
        equipo_t *temp = vector[j];
        vector[j] = vector[k];
        vector[k] = temp;
    }

    partido_t *p1 = (partido_t*) malloc(sizeof(partido_t));
    partido_t *p2 = (partido_t*) malloc(sizeof(partido_t));
    p1->equipo1 = vector[0]; p1->equipo2 = vector[1];
    p1->goles1 = p1->goles2 = -1;
    p1->sig = p2;
    p2->equipo1 = vector[2]; p2->equipo2 = vector[3];
    p2->goles1 = p2->goles2 = -1;
    p2->sig = NULL;
    torneoGlobal.partidos = p1;

    printf("Semifinales sorteadas:\n");
    printf("  1) %s vs %s\n", p1->equipo1->nombre, p1->equipo2->nombre);
    printf("  2) %s vs %s\n", p2->equipo1->nombre, p2->equipo2->nombre);
}

void jugarPartido() {
    partido_t *partido = torneoGlobal.partidos;

    while (partido && partido->goles1 != -1) {
        partido = partido->sig;
    }

    if (partido) {
        printf("Partido: %s vs %s\n", partido->equipo1->nombre, partido->equipo2->nombre);
        printf("Goles de %s: ", partido->equipo1->nombre);
        scanf("%d", &partido->goles1);
        printf("Goles de %s: ", partido->equipo2->nombre);
        scanf("%d", &partido->goles2);
        getchar();
        printf("Resultado guardado.\n");
        return;
    }

    partido_t *p1 = torneoGlobal.partidos;
    partido_t *p2 = p1 ? p1->sig : NULL;
    if (p1 && p2 && p1->goles1 != -1 && p2->goles1 != -1 && p2->sig == NULL) {
        equipo_t *ganador1 = (p1->goles1 == p1->goles2) ? sortearGanador(p1->equipo1, p1->equipo2)
            : (p1->goles1 > p1->goles2 ? p1->equipo1 : p1->equipo2);
        equipo_t *ganador2 = (p2->goles1 == p2->goles2) ? sortearGanador(p2->equipo1, p2->equipo2)
            : (p2->goles1 > p2->goles2 ? p2->equipo1 : p2->equipo2);
        partido_t *final = (partido_t*) malloc(sizeof(partido_t));
        final->equipo1 = ganador1;
        final->equipo2 = ganador2;
        final->goles1 = final->goles2 = -1;
        final->sig = NULL;
        p2->sig = final;

        printf("Final creada entre %s y %s.\n", ganador1->nombre, ganador2->nombre);
        jugarPartido();
    } else {
        printf("No hay partidos pendientes por jugar.\n");
    }
}

void mostrarPartidos() {
    partido_t *partido = torneoGlobal.partidos;
    int i = 1;
    while (partido) {
        printf("Partido %d: %s [%d] vs [%d] %s\n", i++, partido->equipo1->nombre, partido->goles1, partido->goles2, partido->equipo2->nombre);
        partido = partido->sig;
    }
}

void menu() {
    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Crear torneo\n");
        printf("2. Agregar equipo\n");
        printf("3. Agregar jugador\n");
        printf("4. Mostrar equipos\n");
        printf("5. Mostrar jugadores\n");
        printf("6. Asignar tarjeta\n");
        printf("7. Sortear semifinales\n");
        printf("8. Jugar partido\n");
        printf("9. Mostrar partidos\n");
        printf("0. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar();

        switch ((menu_opcion_t)opcion) {
            case MENU_CREAR_TORNEO: crearTorneo(); break;
            case MENU_AGREGAR_EQUIPO: agregarEquipo(); break;
            case MENU_AGREGAR_JUGADOR: agregarJugador(); break;
            case MENU_MOSTRAR_EQUIPOS: mostrarEquipos(); break;
            case MENU_MOSTRAR_JUGADORES: mostrarJugadores(); break;
            case MENU_ASIGNAR_TARJETA: asignarTarjeta(); break;
            case MENU_SORTEAR_SEMIFINALES: sortearSemifinales(); break;
            case MENU_JUGAR_PARTIDO: jugarPartido(); break;
            case MENU_MOSTRAR_PARTIDOS: mostrarPartidos(); break;
            case MENU_SALIR: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n"); break;
        }
    } while (opcion != MENU_SALIR);
}
