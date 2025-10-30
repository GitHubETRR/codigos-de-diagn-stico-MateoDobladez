import datetime
from typing import List, Optional
import os

class Cancha:
    """Representa una cancha deportiva."""
    def __init__(self, nombre: str, tipo: str, capacidad: int):
        self.nombre = nombre
        self.tipo = tipo
        self.capacidad = capacidad
        self.reservas: List['Reserva'] = []

    def esta_disponible(self, fecha: str, hora: str) -> bool:
        for reserva in self.reservas:
            if reserva.fecha == fecha and reserva.hora == hora:
                return False
        return True

class Reserva:
    """Representa una reserva de cancha."""
    def __init__(self, usuario: str, cancha: Cancha, fecha: str, hora: str):
        self.usuario = usuario
        self.cancha = cancha
        self.fecha = fecha  # formato: 'YYYY-MM-DD'
        self.hora = hora    # formato: 'HH:MM'

class SistemaReservas:
    ARCHIVO_RESERVAS = "reservas.txt"

    @staticmethod
    def limpiar_pantalla():
        os.system('cls' if os.name == 'nt' else 'clear')

    def __init__(self):
        self.canchas: List[Cancha] = [
            Cancha('Pádel 1', 'Pádel', 4),
            Cancha('Pádel 2', 'Pádel', 4),
            Cancha('Fútbol', 'Fútbol', 10)
        ]
        self.reservas: List[Reserva] = []
        self.cargar_reservas_desde_archivo()

    def mostrar_menu(self):
        while True:
            self.limpiar_pantalla()
            print("\n--- Sistema de Reserva de Canchas ---")
            print("1. Nueva reserva")
            print("2. Ver todas las reservas agendadas")
            print("3. Cancelar una reserva")
            print("4. Consultar disponibilidad")
            print("5. Salir")
            opcion = input("Seleccione una opción: ")
            if opcion == '1':
                self.nueva_reserva()
            elif opcion == '2':
                self.mostrar_reservas()
            elif opcion == '3':
                self.cancelar_reserva()
            elif opcion == '4':
                self.consultar_disponibilidad()
            elif opcion == '5':
                print("Saliendo... ¡Hasta luego!")
                break
            else:
                print("Opción no válida. Intente nuevamente.")
                input("Presione ENTER para continuar...")

    def nueva_reserva(self):
        self.limpiar_pantalla()
        usuario = input("Ingrese su nombre: ")
        print("Tipos de cancha disponibles:")
        for idx, cancha in enumerate(self.canchas):
            print(f"{idx + 1}. {cancha.nombre} ({cancha.tipo})")
        try:
            idx_cancha = int(input("Seleccione el número de la cancha: ")) - 1
            cancha = self.canchas[idx_cancha]
        except (ValueError, IndexError):
            print("Selección no válida.")
            input("Presione ENTER para continuar...")
            return
        fecha = input("Ingrese la fecha de la reserva (AAAA-MM-DD): ")
        hora = input("Ingrese la hora de la reserva (HH:MM, formato 24hs): ")
        # Validar fecha y hora
        if not self.validar_fecha_hora(fecha, hora):
            print("Fecha u hora con formato incorrecto.")
            input("Presione ENTER para continuar...")
            return
        if not cancha.esta_disponible(fecha, hora):
            print("La cancha seleccionada NO está disponible en ese horario.")
            input("Presione ENTER para continuar...")
            return
        reserva = Reserva(usuario, cancha, fecha, hora)
        cancha.reservas.append(reserva)
        self.reservas.append(reserva)
        self.guardar_reservas_en_archivo()
        print(f"Reserva creada exitosamente para {usuario} en {cancha.nombre} el {fecha} a las {hora} hs.")
        input("Presione ENTER para continuar...")

    def mostrar_reservas(self):
        self.limpiar_pantalla()
        if not self.reservas:
            print("No hay reservas agendadas.")
            input("Presione ENTER para continuar...")
            return
        print("\n--- Reservas agendadas ---")
        for reserva in self.reservas:
            print(f"Usuario: {reserva.usuario} | Cancha: {reserva.cancha.nombre} | Fecha: {reserva.fecha} | Hora: {reserva.hora}")
        input("Presione ENTER para continuar...")

    def cancelar_reserva(self):
        self.limpiar_pantalla()
        usuario = input("Ingrese su nombre para cancelar su reserva: ")
        reservas_usuario = [r for r in self.reservas if r.usuario == usuario]
        if not reservas_usuario:
            print("No se encontraron reservas a nombre de ese usuario.")
            input("Presione ENTER para continuar...")
            return
        print("Sus reservas:")
        for idx, reserva in enumerate(reservas_usuario):
            print(f"{idx + 1}. {reserva.cancha.nombre} | {reserva.fecha} | {reserva.hora}")
        try:
            idx_reserva = int(input("Seleccione el número de la reserva a cancelar: ")) - 1
            reserva_a_cancelar = reservas_usuario[idx_reserva]
        except (ValueError, IndexError):
            print("Selección no válida.")
            input("Presione ENTER para continuar...")
            return
        reserva_a_cancelar.cancha.reservas.remove(reserva_a_cancelar)
        self.reservas.remove(reserva_a_cancelar)
        self.guardar_reservas_en_archivo()
        print("Reserva cancelada correctamente.")
        input("Presione ENTER para continuar...")

    def consultar_disponibilidad(self):
        self.limpiar_pantalla()
        for cancha in self.canchas:
            print(f"\nDisponibilidad de {cancha.nombre} ({cancha.tipo}):")
            horarios_posibles = [f"{h:02}:00" for h in range(8, 23)]
            for fecha_dia in self.proximos_dias(5):
                libres = [h for h in horarios_posibles if cancha.esta_disponible(fecha_dia, h)]
                print(f"  Día {fecha_dia}: {' | '.join(libres) if libres else 'Sin turnos libres'}")
        input("Presione ENTER para continuar...")

    def cargar_reservas_desde_archivo(self):
        if not os.path.isfile(self.ARCHIVO_RESERVAS):
            return
        with open(self.ARCHIVO_RESERVAS, 'r', encoding='utf-8') as f:
            for linea in f:
                partes = linea.strip().split(',')
                if len(partes) != 4:
                    continue
                usuario, nombre_cancha, fecha, hora = partes
                # Buscar cancha por nombre
                cancha = next((c for c in self.canchas if c.nombre == nombre_cancha), None)
                if cancha:
                    reserva = Reserva(usuario, cancha, fecha, hora)
                    cancha.reservas.append(reserva)
                    self.reservas.append(reserva)

    def guardar_reservas_en_archivo(self):
        with open(self.ARCHIVO_RESERVAS, 'w', encoding='utf-8') as f:
            for reserva in self.reservas:
                linea = f"{reserva.usuario},{reserva.cancha.nombre},{reserva.fecha},{reserva.hora}\n"
                f.write(linea)

    @staticmethod
    def validar_fecha_hora(fecha: str, hora: str) -> bool:
        try:
            datetime.datetime.strptime(fecha, "%Y-%m-%d")
            datetime.datetime.strptime(hora, "%H:%M")
            return True
        except ValueError:
            return False

    @staticmethod
    def proximos_dias(cantidad: int = 7) -> List[str]:
        hoy = datetime.date.today()
        return [(hoy + datetime.timedelta(days=i)).strftime("%Y-%m-%d") for i in range(cantidad)]

if __name__ == "__main__":
    sistema = SistemaReservas()
    sistema.mostrar_menu()
