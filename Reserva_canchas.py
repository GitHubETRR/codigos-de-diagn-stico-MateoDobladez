from datetime import datetime, date, timedelta
import os


MENU_OPCIONES = [
    ("1", "Nueva"),
    ("2", "Mostrar"),
    ("3", "Cancelar"),
    ("4", "Disponibilidad"),
    ("5", "Salir"),
]


def limpiar_pantalla() -> None:
    """Limpia la pantalla de la consola según el sistema operativo."""
    os.system("cls" if os.name == "nt" else "clear")


def pausar_e_limpiar() -> None:
    """Espera que el usuario presione Enter y luego limpia la pantalla."""
    input("\nPresione Enter para continuar...")
    limpiar_pantalla()

canchas = [
    {"nombre": "Pádel 1", "tipo": "Pádel", "capacidad": 4},
    {"nombre": "Pádel 2", "tipo": "Pádel", "capacidad": 4},
    {"nombre": "Fútbol",  "tipo": "Fútbol", "capacidad": 10}
]

reservas = []


def mostrar_menu():
    print("\n--- SISTEMA DE RESERVA DE CANCHAS ---")
    for valor, nombre in MENU_OPCIONES:
        print(f"{valor}. {nombre}")


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
    except Exception:
        print("Selección inválida.")
        return

    fecha = input("Ingrese fecha (AAAA-MM-DD): ").strip()

    # Validar solo la fecha
    try:
        datetime.strptime(fecha, "%Y-%m-%d")
    except ValueError:
        print("Formato de fecha incorrecto.")
        return

    # Mostrar horarios ya reservados para esa cancha y fecha
    horarios_ocupados = sorted(
        {r["hora"] for r in reservas if r["cancha"] == cancha["nombre"] and r["fecha"] == fecha}
    )

    if horarios_ocupados:
        print("\nHorarios ya reservados para esa cancha en ese día:")
        print(" | ".join(horarios_ocupados))
    else:
        print("\nNo hay reservas previas para esa cancha en ese día.")

    hora = input("Ingrese hora (HH:MM): ").strip()

    # Validar solo la hora
    try:
        datetime.strptime(hora, "%H:%M")
    except ValueError:
        print("Formato de hora incorrecto.")
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


def proximos_dias(n):
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
    while True:
        mostrar_menu()
        opcion = input("Seleccione opción: ").strip()

        if opcion == "1":
            nueva_reserva()
        elif opcion == "2":
            mostrar_reservas()
        elif opcion == "3":
            cancelar_reserva()
        elif opcion == "4":
            consultar_disponibilidad()
        elif opcion == "5":
            print("Hasta luego.")
            break
        else:
            print("Opción inválida.")
            pausar_e_limpiar()
            continue

        # Después de cada acción válida, pausar y limpiar pantalla
        pausar_e_limpiar()


if __name__ == "__main__":
    main()
