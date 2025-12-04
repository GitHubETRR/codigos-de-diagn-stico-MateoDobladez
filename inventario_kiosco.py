def agregar_producto(inventario, nombre, precio, cantidad):
    """Agrega un nuevo producto o actualiza la cantidad si ya existe"""
    nombre_lower = nombre.lower()
    
    if nombre_lower in inventario:
        inventario[nombre_lower]['cantidad'] += cantidad
        print(f"Se agregaron {cantidad} unidades de {nombre}. Stock total: {inventario[nombre_lower]['cantidad']}")
    else:
        inventario[nombre_lower] = {
            'nombre': nombre,
            'precio': precio,
            'cantidad': cantidad
        }
        print(f"Producto '{nombre}' agregado al inventario")


def mostrar_inventario(inventario):
    """Muestra todos los productos en el inventario"""
    if not inventario:
        print("\nEl inventario esta vacio")
        return
    
    print("\n" + "="*60)
    print("INVENTARIO DEL KIOSCO")
    print("="*60)
    print(f"{'Producto':<25} {'Precio':<15} {'Stock':<10}")
    print("-"*60)
    
    for producto in inventario.values():
        print(f"{producto['nombre']:<25} ${producto['precio']:<14.2f} {producto['cantidad']:<10}")
    
    print("="*60)


def buscar_producto(inventario, nombre):
    """Busca un producto por nombre (case-insensitive)"""
    nombre_lower = nombre.lower()
    return inventario.get(nombre_lower)


def realizar_compra(inventario, nombre, cantidad):
    """Realiza una compra eliminando productos del inventario"""
    producto = buscar_producto(inventario, nombre)
    
    if not producto:
        print(f"Error: El producto '{nombre}' no existe en el inventario")
        return False
    
    if cantidad > producto['cantidad']:
        print(f"Error: No hay suficiente stock. Disponible: {producto['cantidad']}, Solicitado: {cantidad}")
        return False
    
    if cantidad <= 0:
        print("Error: La cantidad debe ser mayor a 0")
        return False
    
    # Actualizar cantidad
    producto['cantidad'] -= cantidad
    total = producto['precio'] * cantidad
    
    print(f"\nCompra realizada exitosamente:")
    print(f"  Producto: {producto['nombre']}")
    print(f"  Cantidad: {cantidad}")
    print(f"  Precio unitario: ${producto['precio']:.2f}")
    print(f"  Total: ${total:.2f}")
    print(f"  Stock restante: {producto['cantidad']}")
    
    # Si el stock llega a 0, eliminar el producto del inventario
    if producto['cantidad'] == 0:
        nombre_lower = nombre.lower()
        del inventario[nombre_lower]
        print(f"  El producto '{producto['nombre']}' se ha agotado y fue eliminado del inventario")
    
    return True


def eliminar_producto(inventario, nombre):
    """Elimina completamente un producto del inventario"""
    producto = buscar_producto(inventario, nombre)
    
    if not producto:
        print(f"Error: El producto '{nombre}' no existe en el inventario")
        return False
    
    nombre_lower = nombre.lower()
    del inventario[nombre_lower]
    print(f"Producto '{nombre}' eliminado completamente del inventario")
    return True


def mostrar_menu():
    """Muestra el menú principal del sistema"""
    print("\n" + "="*60)
    print("SISTEMA DE INVENTARIO - KIOSCO")
    print("="*60)
    print("1. Agregar producto")
    print("2. Ver inventario")
    print("3. Realizar compra")
    print("4. Eliminar producto del inventario")
    print("5. Salir")
    print("="*60)


def obtener_entero(mensaje):
    """Obtiene un número entero válido del usuario"""
    while True:
        try:
            valor = int(input(mensaje))
            if valor < 0:
                print("Error: El valor debe ser positivo")
                continue
            return valor
        except ValueError:
            print("Error: Por favor ingrese un numero valido")


def obtener_decimal(mensaje):
    """Obtiene un número decimal válido del usuario"""
    while True:
        try:
            valor = float(input(mensaje))
            if valor < 0:
                print("Error: El valor debe ser positivo")
                continue
            return valor
        except ValueError:
            print("Error: Por favor ingrese un numero valido")


def main():
    """Función principal del programa"""
    inventario = {}
    
    print("Bienvenido al Sistema de Inventario del Kiosco")
    
    while True:
        mostrar_menu()
        opcion = input("\nSeleccione una opcion: ").strip()
        
        if opcion == "1":
            print("\n--- AGREGAR PRODUCTO ---")
            nombre = input("Nombre del producto: ").strip()
            
            if not nombre:
                print("Error: El nombre no puede estar vacio")
                continue
            
            precio = obtener_decimal("Precio del producto: $")
            cantidad = obtener_entero("Cantidad inicial: ")
            
            agregar_producto(inventario, nombre, precio, cantidad)
        
        elif opcion == "2":
            mostrar_inventario(inventario)
        
        elif opcion == "3":
            if not inventario:
                print("\nEl inventario esta vacio. No se pueden realizar compras.")
                continue
            
            print("\n--- REALIZAR COMPRA ---")
            mostrar_inventario(inventario)
            nombre = input("\nNombre del producto a comprar: ").strip()
            cantidad = obtener_entero("Cantidad a comprar: ")
            
            realizar_compra(inventario, nombre, cantidad)
        
        elif opcion == "4":
            if not inventario:
                print("\nEl inventario esta vacio.")
                continue
            
            print("\n--- ELIMINAR PRODUCTO ---")
            mostrar_inventario(inventario)
            nombre = input("\nNombre del producto a eliminar: ").strip()
            
            confirmar = input(f"Esta seguro de eliminar '{nombre}'? (s/n): ").strip().lower()
            if confirmar == 's':
                eliminar_producto(inventario, nombre)
            else:
                print("Operacion cancelada")
        
        elif opcion == "5":
            print("\nGracias por usar el Sistema de Inventario del Kiosco!")
            break
        
        else:
            print("Opcion no valida. Por favor seleccione una opcion del 1 al 5.")


if __name__ == "__main__":
    main()
