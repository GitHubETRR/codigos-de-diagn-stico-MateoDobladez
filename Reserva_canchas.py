from enum import Enum
from typing import List, Dict
from datetime import datetime, date, timedelta

class Menu(Enum):
    NUEVA = "1"
    MOSTRAR = "2"
    CANCELAR = "3"
    DISPONIBILIDAD = "4"
    GUARDAR = "5"
    SALIR = "6"

canchas = [
    {"nombre": "Pádel 1", "tipo": "Pádel", "capacidad": 4},
    {"nombre": "Pádel 2", "tipo": "Pádel", "capacidad": 4},
    {"nombre": "Fútbol",  "tipo": "Fútbol", "capacidad": 10}
]

reservas: List[Dict] = []


def cargar_reservas():
    global reservas
    try:
        with open(DATA_FILE, "r", encoding="utf-8") as f:
            reservas = json.load(f)
    except FileNotFoundError:
        reservas = []
    except:
        reservas = []


def guardar_reservas():
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump(reservas, f, ensure_ascii=False, indent=2)
    print("Reservas guardadas correctamente.")


def mostrar_menu():
    print("\n--- SISTEMA DE RESERVA DE CANCHAS ---")
    for item in Menu:
        nombre = item.name.capitalize()
        print(f"{item.value}. {nombre}")


def validar_fecha_hora(fecha: str, hora: str) -> bool:
    try:
        datetime.strptime(fecha, "%Y-%m-%d")
        datetime.strptime(hora, "%H:%M")
        return True
    except:
        return False


def cancha_disponible(nombre_cancha: str, fecha: str, hora: str) -> bool:
    for r in reservas:
        if r["cancha"] == nombre_cancha and r["fecha"] == fecha and r["hora"] == hora:
            return False
    return True


def nueva_reserva():
    usuario = input("Ingrese su nombre: ").strip()
    print("Canchas disponibles:")
    for i, c in enumerate(canchas, start=1):
        print(f"{i}. {c['nombre']} ({c['tipo']})")

    try:
        idx = int(input("Seleccione la cancha: ")) - 1
        cancha = canchas[idx]
    except:
        print("Selección inválida.")
        return

    fecha = input("Ingrese fecha (AAAA-MM-DD): ").strip()
    hora = input("Ingrese hora (HH:MM): ").strip()

    if not validar_fecha_hora(fecha, hora):
        print("Formato de fecha u hora incorrecto.")
        return

    if not cancha_disponible(cancha["nombre"], fecha, hora):
        print("La cancha no está disponible en ese horario.")
        return

    reservas.append({
        "usuario": usuario,
        "cancha": cancha["nombre"],
        "fecha": fecha,
        "hora": hora
    })

    print("Reserva creada exitosamente.")


def mostrar_reservas():
    if not reservas:
        print("No hay reservas registradas.")
        return
    print("\n--- Reservas agendadas ---")
    for r in reservas:
        print(f"{r['usuario']} | {r['cancha']} | {r['fecha']} | {r['hora']}")


def cancelar_reserva():
    usuario = input("Ingrese su nombre: ").strip()
    lista = [r for r in reservas if r["usuario"] == usuario]

    if not lista:
        print("No hay reservas asociadas.")
        return

    print("Sus reservas:")
    for i, r in enumerate(lista, start=1):
        print(f"{i}. {r['cancha']} | {r['fecha']} | {r['hora']}")

    try:
        idx = int(input("Seleccione número: ")) - 1
        reserva_obj = lista[idx]
    except:
        print("Selección inválida.")
        return

    reservas.remove(reserva_obj)
    print("Reserva cancelada.")


def proximos_dias(n: int) -> List[str]:
    hoy = date.today()
    return [(hoy + timedelta(days=i)).strftime("%Y-%m-%d") for i in range(n)]


def consultar_disponibilidad():
    for c in canchas:
        print(f"\nDisponibilidad {c['nombre']} ({c['tipo']}):")
        for f in proximos_dias(5):
            libres = []
            for h in range(8, 23):
                hora = f"{h:02}:00"
                if cancha_disponible(c["nombre"], f, hora):
                    libres.append(hora)
            lista = " | ".join(libres) if libres else "Sin turnos"
            print(f"{f}: {lista}")


def main():
    cargar_reservas()
    while True:
        mostrar_menu()
        opcion = input("Seleccione opción: ").strip()

        if opcion == Menu.NUEVA.value:
            nueva_reserva()
        elif opcion == Menu.MOSTRAR.value:
            mostrar_reservas()
        elif opcion == Menu.CANCELAR.value:
            cancelar_reserva()
        elif opcion == Menu.DISPONIBILIDAD.value:
            consultar_disponibilidad()
        elif opcion == Menu.GUARDAR.value:
            guardar_reservas()
        elif opcion == Menu.SALIR.value:
            guardar_reservas()
            print("Hasta luego.")
            break
        else:
            print("Opción inválida.")


if __name__ == "__main__":
    main()
