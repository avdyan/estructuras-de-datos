/*
Cada estructura tiene una forma especial del tratamiento de los datos, 
es necesario conocer a profundida cada una de las estructuras que se trabajarán.  
Tomar en cuenta que este programa debe cumplir obligatoriamente con los siguientes requisitos:

-El programa tienen que tener un menú de elección por medio uso de flechas 
y la tecla enter para cada opción o sub opción

-Cada formulario de datos, pantalla de menú o petición de datos 
debe ser debidamente formateado con color de pantalla, 
color de fuente y centrado de cada formulario, menú o submenú

-Cada vez que se elimine o inserte información se debe mostrar la estructura actualizada 
en el formato requerido es decir si es una PILA en forma vertical, 
si es una COLA en formato horizontal y si es una LISTA en formato horizonal

-Cada estructura debe mostrar su inicio y fin de datos

-Cuando se visualice todos la estructura sera de forma resuminda 
y ser capaza de poder alinear correctamente 10 nodos mínimo

-Se debe poder visualizar las información de cada nodo de forma completa

-6 variables mínimo por cada nodo

-Cuando se muestra toda la estructra cada nodo debe poseer su dirección de memoria 
y la dirección de memoria de su enlaace o sus enlaces.

-Se debe crear un video con por lo menos 10 nodos por estructura, 3 eliminaciones, 
2 consultas de información, y 1 vaciado de información de cada estructura.
*/


// Declaramos las bibliotecas necesarias
#include <iostream>
#include <iomanip>
// Para usar la función Sleep
#include <Windows.h>

using namespace std;

// Definición de la estructura para el ingreso de datos del estudiante
struct Estudiante {
    string nombre;
    string apellido;
    int edad;
    string carrera;
    string email;
    long telefono;
};

// Nodo para la Pila
struct NodoPila {
    Estudiante estudiante;
    NodoPila* siguiente;
};

// Nodo para la Cola        PROXIMAMENTE
//struct NodoCola {
//    Estudiante estudiante;
//    NodoCola* siguiente;
//};

// Nodo para la Lista Doblemente Enlazada   PROXIMAMENTE
//struct NodoLista {
//    Estudiante estudiante;
//    NodoLista* siguiente;
//    NodoLista* anterior;
//};

// Función para agregar un estudiante a la Pila por medio de PUSH
void pushEstudiante(NodoPila*& top) {
    // Reservar memoria para un nuevo nodo
    NodoPila* nuevo = new NodoPila;

    system("cls"); // Limpiar la pantalla
    cout << "###### INGRESO DE DATOS DEL ESTUDIANTE ######" << endl << endl;

    cout << "Nombre: ";
    cin >> nuevo->estudiante.nombre;
    cout << "Apellido: ";
    cin >> nuevo->estudiante.apellido;
    cout << "Edad: ";
    cin >> nuevo->estudiante.edad;
    cout << "Carrera: ";
    cin >> nuevo->estudiante.carrera;
    cout << "Email: ";
    cin >> nuevo->estudiante.email;
    cout << "Teléfono: ";
    cin >> nuevo->estudiante.telefono;

    // Enlazar el nuevo nodo con el nodo superior
    nuevo->siguiente = top;
    // El nuevo nodo se convierte en el nodo superior
    top = nuevo;
}

// Función para mostrar todos los estudiantes de la Pila
void mostrarEstudiantesPila(NodoPila* top) {
    // Verificar si la pila está vacía
    if (!top) {
        cout << endl;
        cout << "La pila esta vacia." << endl;
        return;
    }

    cout << endl;
    cout << "----- Inicio de la Lista de Estudiantes -----" << endl << endl;
    // Recorrer la pila
    NodoPila* temp = top;

    // Mientras no sea el final de la pila
    while (temp != nullptr) {
        // Mostramos la dirección de memoria del nodo y los datos del estudiante
        cout << "DIRECCION DEL NODO: " << "\t|" << temp << endl;

        cout << "Nombre: " << temp->estudiante.nombre << " \t\t| " << &temp->estudiante.nombre << endl;
        cout << "Apellido: " << temp->estudiante.apellido << " \t\t| " << &temp->estudiante.apellido << endl;
        cout << "Edad: " << temp->estudiante.edad << " \t\t| " << &temp->estudiante.edad << endl;
        cout << "Carrera: " << temp->estudiante.carrera << " \t\t| " << &temp->estudiante.carrera << endl;
        cout << "Email: " << temp->estudiante.email << " \t\t| " << &temp->estudiante.email << endl;
        cout << "Telefono: " << temp->estudiante.telefono << " \t\t| " << &temp->estudiante.telefono << endl;
        cout << endl;

        if (temp->siguiente != nullptr) {
            cout << "DIRECCION DEL NODO SIGUIENTE: " << temp->siguiente << endl;
        }
        temp = temp->siguiente;
    }
    cout << "----- Fin de la Lista de Estudiantes -----" << endl;
}


// Función para eliminar el primer estudiante de la Pila
void popEstudiante(NodoPila*& top) {
    if (top != nullptr) {
        cout << "Eliminando el estudiante: \t " << top->estudiante.nombre << " ..." << endl;
        NodoPila* temp = top;
        top = top->siguiente;
        delete temp;
        Sleep(2000); // Esperar 2 segundo
        cout << "Estudiante eliminado con EXITO." << endl;
    }
    else {
        cout << "La lista de estudiantes está vacia. No hay estudiantes para eliminar." << endl;
    }
}


// Función para vaciar la Pila
void vaciarPila(NodoPila*& top) {
    if (top != nullptr) {
        cout << "Vaciando la lista de estudiantes..." << endl;
        while (top != nullptr) {
            popEstudiante(top);
        }
        Sleep(2000); // Esperar 2 segundo
        cout << "La lista de estudiantes ha sido vaciada con EXITO." << endl;
    }
    else {
        cout << "La lista de estudiantes ya esta vacia." << endl;
    }
}


// Menú de la Pila
void menuPila(NodoPila*& top) {
    int opcion;
    do {
        system("cls"); // Limpiar la pantalla (para sistemas UNIX)
        cout << "----- Listado de Estudiantes -----" << endl << endl;
        cout << "1- Ingresar datos de nuevo estudiante (PUSH)" << endl;
        cout << "2- Mostrar todos los estudiantes (PILA)" << endl;
        cout << "3- Eliminar el ultimo estudiante ingresado (POP)" << endl;
        cout << "4- Vaciar el listado" << endl;
        cout << "5- Regresar al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            pushEstudiante(top);
            mostrarEstudiantesPila(top); // Mostrar el listado de estudiantes después de ingresar los datos
            break;
        case 2:
            mostrarEstudiantesPila(top);
            break;
        case 3:
            popEstudiante(top);
            mostrarEstudiantesPila(top); // Mostrar el listado de estudiantes después de eliminar un estudiante
            break;
        case 4:
            vaciarPila(top);
            break;
        case 5:
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

        cout << "Presione Enter para continuar...";
        cin.ignore();
        cin.get();
    } while (opcion != 5);
}

// Menú principal
int main() {
    NodoPila* pilaEstudiantes = nullptr;
    int opcion;
    do {
        system("cls"); // Limpiar la pantalla (para sistemas UNIX)
        cout << "------ Sistema de Mantenimiento de Estudiantes ------" << endl;
        cout << "1- Lista de Estudiantes (PILA)" << endl;
        cout << "2- Lista de Profesores (COLA) ||| PROXIMAMENTE" << endl;
        cout << "3- Servicios de la Universidad (LISTA DOBLE. ENLAZADA) ||| PROXIMAMENTE" << endl;
        cout << "4- Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPila(pilaEstudiantes);
            break;
        case 2:
            // Falta mplementar lista de profesores (cola)
            break;
        case 3:
            // Falta implementar servicios de la universidad (lista doblemente enlazada)
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

        cout << "Presione Enter para continuar...";
        cin.ignore();
        cin.get();
    } while (opcion != 4);

    // Liberar memoria de la pila
    vaciarPila(pilaEstudiantes);

    return 0;
}
