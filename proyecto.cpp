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

/*
PUNTOS EXTRA = EN PROCESO
Mostrar el historial de operaciones realizadas
en la estructura de pila, cola y la lista doblemente enlazada
*/

/*
CARACTERISTICAS IMPLEMENTADAS (por orden de entrada o prioridad)
- Animación de entrada
- Menú de opciones
    - Menú de la Pila
        - Ingreso de datos de un estudiante
            - Mostrar de forma resumida los datos de la pila
            - Guardar el historial
        - Mostrar los datos de todos los estudiantes
            - Mostrar de forma detallada los datos de la pila
        - Eliminar el primer estudiante de la Pila
            - Mostrar de forma resumida los datos de la pila
            - Guardar el historial
        - Vaciar la Pila
            - Guardar el historial
    - Menú de la Cola
        - Ingreso de datos de un profesor
            - Mostrar de forma resumida los datos de la cola
			- Guardar el historial
        - Mostrar los datos de todos los profesores
            - Mostrar de forma detallada los datos de la cola
        - Eliminar el primer profesor de la Cola
            - Mostrar de forma resumida los datos de la cola
			- Guardar el historial
        - Vaciar la Cola
            - Guardar el historial

================================================================
Funciones generales o de estética
- Función para centrar texto en el historial
- Función para mostrar una animación de entrada
*/

/*
POR HACER ALTA PRIORIDAD
- HECHO - Animacion de entrada
- Hacer que al salir del programa se guarde la pila, cola y lista en un archivo llamado "backup".
- Hacer que al volver a entrar al programa, identifique si hay un archivo "backup"
- Hacer que pida al usuario si desea cargar los datos desde el archivo "backup"
  caso contrario eliminar el contenido del archivo y eliminar el historial.

POR HACER BAJA PRIORIDAD
- En el historial, debajo de la fecha y operacion mostrar el nodo ingresado o eliminado
*/

/*
BUGS ENCONTRADOS


BUGS SOLUCIONADOS
- Al ejecutar la funcion de vaciado de datos guardaba aún
  los nodos resultantes de una eliminación en el historial
      - se halló que la funcion de vaciado ejecuta la funcion de eliminacion,
        por lo que se guarda cada nodo resultante de la funcion, se soluciono copiando el
        código de la eliminacion y eliminando la ejecución de la funcion del Historial.

*/

// Declaramos las bibliotecas necesarias
#include <iostream>
#include <iomanip>
#include <Windows.h>        // Para usar la función Sleep()
#include <ctime>			// Para usar la función time()
#include <fstream>			// Para trabajar con archivos
#include <string>			// Para trabajar con cadenas de texto
#include <conio.h>			// Para usar la función _getch() y menu interactivo
using namespace std;

// Definición de la estructura para el ingreso de datos del estudiante
struct Estudiante {
    string nombre;
    string apellido;
    string carrera;
    string email;
    int edad;
    long telefono;
};

// Definición de la estructura para los nodos de la Cola (Profesores)
struct Profesor {
    string nombre;
    string apellido;
    string departamento;
    string email;
    int edad;
    long telefono;
};

// Nodo para la Pila
struct NodoPila {
    Estudiante estudiante;
    NodoPila* siguiente;
};

// Nodo para la Cola        PROXIMAMENTE
struct NodoCola {
    Profesor profesor;
    NodoCola* siguiente;
};

// Nodo para la Lista Doblemente Enlazada   PROXIMAMENTE
//struct NodoLista {
//    Estudiante estudiante;
//    NodoLista* siguiente;
//    NodoLista* anterior;
//};

// Funciones Prototipo Generales
// Función para centrar texto
string centrarTexto(const string& texto, int anchoCampo);
// Función que pide el Nodo de la pila a escribir y el tipo de escritura de datos
void historialPila(NodoPila* top, const string& tipoEscritura);
// Función para guardar el historial de operaciones de la Cola
void historialCola(NodoCola* frente, NodoCola* final, const string& tipoEscritura);
// Función para mostrar el historial de operaciones de la Pila y Cola
void mostrarHistorial();
// Funcion para mostrar una animación de entrada
void animacionEntrada();

// Funciones Prototipo de la Pila
// Funcion para ingresar un estudiante a la Pila por medio de PUSH
void ingresarEstudiantes(NodoPila*& top);
// Funcion para mostrar los datos de todos los estudiantes
void mostrarEstudiantes(NodoPila* top);
// Funcion para mostrar los datos de todos los estudiantes de forma resumida
void mostrarEstudiantesResumido(NodoPila* top);
// Funcion para eliminar el primer estudiante de la Pila
void eliminarEstudiantes(NodoPila*& top);
// Funcion para vaciar la Pila
void vaciarEstudiantes(NodoPila*& top);
// Funcion para mostrar el menú de la Pila
void menuPila(NodoPila*& top);


// Funciones Prototipo de la Cola
// Funcion para ingresar un estudiante a la Cola por medio de ENQUEUE
void ingresarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion para mostrar los datos de todos los profesores
void mostrarProfesores(NodoCola* frente, NodoCola* final);
// Funcion para eliminar el primer profesor de la Cola
void eliminarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion para vaciar la Cola
void vaciarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion para mostrar el menú de la Cola
void menuCola(NodoCola*& frente, NodoCola*& final);

// Menú principal
int main() {
    animacionEntrada(); // Mostrar la animación de entrada
    system("cls"); // Limpiar la pantalla
    system("color e"); // Cambiar el color de la pantalla

    NodoPila* pilaEstudiantes = NULL;
    NodoCola* frente = NULL;
    NodoCola* final = NULL;

    int opcion = 0;
    int tecla;

    do {
        system("cls");
        cout << "------ Sistema de Manejo de Estudiantes ------" << endl << endl;
        cout << (opcion == 0 ? "=> " : "   ") << "1- Lista de Estudiantes (PILA)" << endl;
        cout << (opcion == 1 ? "=> " : "   ") << "2- Lista de Profesores (COLA)" << endl;
        cout << (opcion == 2 ? "=> " : "   ") << "3- Servicios de la Universidad (LISTA DOBLE. ENLAZADA)" << endl;
        cout << (opcion == 3 ? "=> " : "   ") << "4- Mostrar Historial de Operaciones" << endl;
        cout << (opcion == 4 ? "=> " : "   ") << "5- Salir" << endl;

        do {
            tecla = _getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13);

        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : 4;
            break;
        case 80: // Flecha abajo
            opcion = (opcion < 4) ? opcion + 1 : 0;
            break;
        case 13: // Enter
            switch (opcion) {
            case 0:
                menuPila(pilaEstudiantes);
                break;
            case 1:
                menuCola(frente, final);
                break;
            case 2:
                cout << "La opción 3: Servicios de la Universidad (LISTA DOBLE. ENLAZADA) aún no está implementada." << endl;
                _getch(); // Esperar a que el usuario presione una tecla antes de continuar
                break;
            case 3:
                mostrarHistorial();
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                _getch(); // Esperar a que el usuario presione una tecla antes de continuar
                break;
            }
            break;
        }
    } while (tecla != 13 || opcion != 4); // Salir si se presiona Enter en la opción 5

    // Liberar memoria de la pila
    vaciarEstudiantes(pilaEstudiantes);

    return 0;
}

// ########################## FUNCIONES GENERALES ##################################
string centrarTexto(const string& texto, int anchoCampo) {
    int espacios = anchoCampo - texto.size();
    int espaciosIzquierda = espacios / 2;
    int espaciosDerecha = espacios - espaciosIzquierda;

    return string(espaciosIzquierda, ' ') + texto + string(espaciosDerecha, ' ');
}

void historialPila(NodoPila* top, const string& tipoEscritura) {

    // Verificar si la pila está vacía
 //   if (!top) {
    //	cout << "La pila esta vacia." << endl;
    //	return;
    //}

    // Crear un archivo de texto para guardar el historial de operaciones
    ofstream archivo("historial.txt", ios::app); // Modo de escritura al final del archivo

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        // Recorrer la pila
        NodoPila* temp = top;

        // Obtener la fecha y hora actual
        time_t now = time(0);
        char dt[30];
        ctime_s(dt, sizeof dt, &now);

        archivo << "Fecha y Hora: " << dt;
        archivo << "Operacion: " << tipoEscritura << endl << endl;

        archivo << centrarTexto("----- FIN DE LA PILA -----", 30) << endl;

        // Mientras no sea el final de la pila
        while (temp != NULL) {
            // Guardar los datos del estudiante en el archivo
            archivo << "================================" << endl;
            archivo << left << setw(30) << ("|| Nombre: " + temp->estudiante.nombre) << "||" << endl;
            archivo << left << setw(30) << ("|| Apellido: " + temp->estudiante.apellido) << "||" << endl;
            archivo << left << setw(30) << ("|| Edad: " + to_string(temp->estudiante.edad)) << "||" << endl;
            archivo << left << setw(30) << ("|| Carrera: " + temp->estudiante.carrera) << "||" << endl;
            archivo << left << setw(30) << ("|| Email: " + temp->estudiante.email) << "||" << endl;
            archivo << left << setw(30) << ("|| Telefono: " + to_string(temp->estudiante.telefono)) << "||" << endl;
            archivo << "================================" << endl;

            temp = temp->siguiente;
        }
        archivo << centrarTexto("----- INICIO DE LA PILA -----", 30) << endl;
        archivo << endl;

        archivo.close(); // Cerrar el archivo
    }
    else {
        cout << "Error al abrir el archivo de historial de operaciones de la Pila." << endl;
    }
}

void historialCola(NodoCola* frente, NodoCola* final, const string& tipoEscritura) {
    // Crear un archivo de texto para guardar el historial de operaciones
    ofstream archivo("historial.txt", ios::app); // Modo de escritura al final del archivo

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        // Obtener la fecha y hora actual
        time_t now = time(0);
        char dt[30];
        ctime_s(dt, sizeof dt, &now);

        archivo << "Fecha y Hora: " << dt;
        archivo << "Operacion: " << tipoEscritura << endl << endl;

        NodoCola* temp = frente;

        // Calcular el tamaño de la cola para determinar cuantos structs tenemos
        int tamanoCola = 0;
        while (temp != NULL) {
			tamanoCola++;
			temp = temp->siguiente;
		}
        temp = frente;

        // Asignamos memoria dinamica para almacenar las cadenas de cada struct
        string ** datos = new string*[tamanoCola];
        for (int i = 0; i < tamanoCola; ++i) {
            datos[i] = new string[6];
        }

        int indice = 0;
        while (temp != NULL) {
            datos[indice][0] = "|| Nombre: " + temp->profesor.nombre;
            datos[indice][1] = "|| Apellido: " + temp->profesor.apellido;
            datos[indice][2] = "|| Edad: " + to_string(temp->profesor.edad);
            datos[indice][3] = "|| Departamento: " + temp->profesor.departamento;
            datos[indice][4] = "|| Email: " + temp->profesor.email;
            datos[indice][5] = "|| Telefono: " + to_string(temp->profesor.telefono);

            temp = temp -> siguiente;
            indice++;
        }

        // Escribir las líneas horizontales para los structs
        for (int i = 0; i < tamanoCola; ++i) {
            archivo << "===============================" << "\t\t";
        }
        archivo << endl;

        // Escribir los datos de cada campo para todos los structs
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < tamanoCola; ++j) {
                archivo << left << setw(30) << datos[j][i] << "||\t";
            }
            archivo << endl;
        }

        // Escribir las líneas horizontales para los structs
        for (int i = 0; i < tamanoCola; ++i) {
            archivo << "===============================" << "\t\t";
        }
        archivo << endl << endl;

        // Liberar la memoria dinámica
        for (int i = 0; i < tamanoCola; ++i) {
            delete[] datos[i];
        }
        delete[] datos;

        archivo.close(); // Cerrar el archivo
    }
    else {
        cout << "Error al abrir el archivo de historial de operaciones de la Cola." << endl;
    }
}

void mostrarHistorial() {
    // Leer el archivo de historial de operaciones
    ifstream archivo("historial.txt");

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close(); // Cerrar el archivo
    }
    else {
        cout << "Error al abrir el archivo de historial de operaciones." << endl;
    }
}

void animacionEntrada() {        // Intro Animada
    system("color 9");
    cout << " *  *  *  *****  *     *****  ***    * * *    *****   " << endl;
    Sleep(300);
    cout << " *  *  *  *      *     *     *   *  *  *  *   *        " << endl;
    Sleep(300);
    cout << " *  *  *  *****  *     *     *   *  *  *  *   *****    " << endl;
    Sleep(300);
    cout << " *  *  *  *      *     *     *   *  *  *  *   *         " << endl;
    Sleep(300);
    cout << "  * * *   *****  ****  *****  ***   *  *  *   *****     " << endl;
    Sleep(300);
    cout << "=============================================" << endl;
    Sleep(500);
    cout << "SISTEMA DE MANEJO DE ESTUDIANTES" << endl;
    Sleep(500);
    _getch();
}

// ########################## PILA ##################################

void ingresarEstudiantes(NodoPila*& top) {
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
    cout << "Telefono: ";
    cin >> nuevo->estudiante.telefono;

    // Enlazar el nuevo nodo con el nodo superior
    nuevo->siguiente = top;
    // El nuevo nodo se convierte en el nodo superior
    top = nuevo;

    cout << "Estudiante ingresado con EXITO." << endl;
    historialPila(top, "Ingreso de Datos - PUSH"); // Guardar el historial de operaciones de la Pila
}

void mostrarEstudiantesResumido(NodoPila* top) {
    // Verificar si la pila está vacía
    if (!top) {
        cout << endl;
        cout << "La pila esta vacia." << endl;
        return;
    }

    cout << endl;
    cout << "----- Fin de la Lista de Estudiantes -----" << endl << endl;
    // Recorrer la pila
    NodoPila* temp = top;

    // Mientras no sea el final de la pila
    while (temp != NULL) {
        // Mostramos la dirección de memoria del nodo y los datos del estudiante
        cout << "DIRECCION DEL NODO: " << "\t| " << temp << endl;

        cout << "Nombre: " << temp->estudiante.nombre << " \t\t| " << &temp->estudiante.nombre << endl;
        cout << endl;
        temp = temp->siguiente;
    }
    cout << "----- Inicio de la Lista de Estudiantes -----" << endl;
    cout << endl;
    system("pause"); // Pausar la pantalla
}

void mostrarEstudiantes(NodoPila* top) {
    // Verificar si la pila está vacía
    if (!top) {
        cout << endl;
        cout << "La pila esta vacia." << endl;
        system("pause"); // Pausar la pantalla
        return;
    }

    cout << endl;
    cout << "----- Fin de la Lista de Estudiantes -----" << endl << endl;
    // Recorrer la pila
    NodoPila* temp = top;

    // Mientras no sea el final de la pila
    while (temp != NULL) {
        // Mostramos la dirección de memoria del nodo y los datos del estudiante
        cout << "DIRECCION DEL NODO: " << "\t| " << temp << endl;

        cout << "Nombre: " << temp->estudiante.nombre << " \t\t| " << &temp->estudiante.nombre << endl;
        cout << "Apellido: " << temp->estudiante.apellido << " \t\t| " << &temp->estudiante.apellido << endl;
        cout << "Edad: " << temp->estudiante.edad << " \t\t| " << &temp->estudiante.edad << endl;
        cout << "Carrera: " << temp->estudiante.carrera << " \t\t| " << &temp->estudiante.carrera << endl;
        cout << "Email: " << temp->estudiante.email << " \t\t| " << &temp->estudiante.email << endl;
        cout << "Telefono: " << temp->estudiante.telefono << " \t\t| " << &temp->estudiante.telefono << endl;
        cout << endl;

        temp = temp->siguiente;
    }
    cout << "----- Inicio de la Lista de Estudiantes -----" << endl;

    system("pause"); // Pausar la pantalla
}

void eliminarEstudiantes(NodoPila*& top) {
    if (top != NULL) {
        cout << "Eliminando el estudiante: \t " << top->estudiante.nombre << " ..." << endl;
        NodoPila* temp = top;
        top = top->siguiente;
        delete temp;
        Sleep(2000); // Esperar 2 segundo
        cout << "Estudiante eliminado con EXITO." << endl;

        historialPila(top, "Eliminacion de Datos - POP"); // Guardar el historial de operaciones de la Pila

    }
    else {
        cout << "La lista de estudiantes está vacia. No hay estudiantes para eliminar." << endl;
    }
}

void vaciarEstudiantes(NodoPila*& top) {
    if (top != NULL) {
        cout << "Vaciando la lista de estudiantes..." << endl;
        while (top != NULL) {
            // Misma lógica que en la función eliminarEstudiantes
            cout << "Eliminando el estudiante: \t " << top->estudiante.nombre << " ..." << endl;
            NodoPila* temp = top;
            top = top->siguiente;
            delete temp;
            Sleep(2000); // Esperar 2 segundo
            cout << "Estudiante eliminado con EXITO." << endl;
        }
        Sleep(2000); // Esperar 2 segundo
        cout << "La lista de estudiantes ha sido vaciada con EXITO." << endl;

        // Reiniciar el puntero de la pila
        top = NULL;

        // Guardar el historial de operaciones de la Pila
        // RESOLVER : No se guarda el historial de operaciones de la Pila sino que guarda el ultimo nodo
        historialPila(top, "Vaciado de Datos");

        system("pause"); // Pausar la pantalla
    }
    else {
        cout << "La lista de estudiantes ya esta vacia." << endl;
    }
}

void menuPila(NodoPila*& top) {
    int opcion = 0;
    int tecla;
    do {
        system("cls"); // Limpiar la pantalla (para sistemas UNIX)
        cout << "----- Listado de Estudiantes -----" << endl << endl;
        cout << (opcion == 0 ? "=> " : "   ") << "1- Ingresar datos de nuevo estudiante (PUSH)" << endl;
        cout << (opcion == 1 ? "=> " : "   ") << "2- Mostrar todos los estudiantes (PILA)" << endl;
        cout << (opcion == 2 ? "=> " : "   ") << "3- Eliminar el ultimo estudiante ingresado (POP)" << endl;
        cout << (opcion == 3 ? "=> " : "   ") << "4- Vaciar el listado" << endl;
        cout << (opcion == 4 ? "=> " : "   ") << "5- Regresar al Menu Principal" << endl;

        do {
            tecla = _getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13);

        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : 4;
            break;
        case 80: // Flecha abajo
            opcion = (opcion < 4) ? opcion + 1 : 0;
            break;
        case 13: // Enter
            switch (opcion) {
            case 0:
                ingresarEstudiantes(top);
                mostrarEstudiantesResumido(top); // Mostrar el listado de estudiantes después de ingresar los datos
                break;
            case 1:
                mostrarEstudiantes(top);
                break;
            case 2:
                eliminarEstudiantes(top);
                mostrarEstudiantesResumido(top); // Mostrar el listado de estudiantes después de eliminar un estudiante
                break;
            case 3:
                vaciarEstudiantes(top);
                break;
            case 4:
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
            break;
        }
    } while (tecla != 13 || opcion != 4); // Salir si se presiona Enter en la opción 5
}


// ########################## COLA ##################################

void ingresarProfesores(NodoCola*& frente, NodoCola*& final) {
    // Reservar memoria para un nuevo nodo
    NodoCola* nuevo = new NodoCola;

    system("cls"); // Limpiar la pantalla
    cout << "###### INGRESO DE DATOS DEL PROFESOR ######" << endl << endl;

    cout << "Nombre: ";
    cin >> nuevo->profesor.nombre;
    cout << "Apellido: ";
    cin >> nuevo->profesor.apellido;
    cout << "Edad: ";
    cin >> nuevo->profesor.edad;
    cout << "Departamento: ";
    cin >> nuevo->profesor.departamento;
    cout << "Email: ";
    cin >> nuevo->profesor.email;
    cout << "Telefono: ";
    cin >> nuevo->profesor.telefono;

    // Enlazar el nuevo nodo con el nodo superior
    nuevo->siguiente = NULL;

    // El nuevo nodo se convierte en el nodo superior
    if (frente == NULL) {
        frente = nuevo;
    }
    // Si la cola no está vacía
    else {
        final->siguiente = nuevo;
    }

    // El nuevo nodo se convierte en el nodo final
    final = nuevo;

    // Guardar en el historial
    historialCola(frente, final, "Ingreso de Datos - ENQUEUE");

    Sleep(1000); // Esperar 1 segundo
    cout << "Profesor ingresado con EXITO." << endl;
}

void mostrarProfesores(NodoCola* frente, NodoCola* final) {
    // Verificar si la cola está vacía
    if (frente == NULL) {
        cout << endl;
        cout << "La cola esta vacia." << endl;
        return;
    }

    cout << endl;

    // Recorrer la cola
    NodoCola* temp = frente;

    // Calcular el tamaño de la cola para determinar cuantos structs tenemos
    int tamanoCola = 0;
    while (temp != NULL) {
        tamanoCola++;
        temp = temp->siguiente;
    }
    temp = frente;

    // Asignamos memoria dinamica para almacenar las cadenas de cada struct
    string** datos = new string * [tamanoCola];
    for (int i = 0; i < tamanoCola; ++i) {
        datos[i] = new string[6];
    }

    int indice = 0;
    while (temp != NULL) {
        datos[indice][0] = "|| Nombre: " + temp->profesor.nombre;
        datos[indice][1] = "|| Apellido: " + temp->profesor.apellido;
        datos[indice][2] = "|| Edad: " + to_string(temp->profesor.edad);
        datos[indice][3] = "|| Departamento: " + temp->profesor.departamento;
        datos[indice][4] = "|| Email: " + temp->profesor.email;
        datos[indice][5] = "|| Telefono: " + to_string(temp->profesor.telefono);

        temp = temp->siguiente;
        indice++;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "====================================================" << "\t";
    }
    cout << endl;

    // Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < tamanoCola; ++j) {
            cout << left << setw(30) << datos[j][i] << "\t| " << &datos[j][i] << "||\t";
        }
        cout << endl;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "====================================================" << "\t";
    }
    cout << endl << endl;

    system("pause"); // Pausar la pantalla

    /*
        La forma en la que mostramos los datos en la consola es la siguiente:
        Para mostrar datos usamos:      <<
        Para guardar datos usamos:      >>

        Al momento de cambiar esta función de escribir un archivo de texto a mostrar en consola
        solo era cambiarle la variable del archivo a cout, por lo que quizás se hizo para que
        primero, visualicemos el cómo queramos que se formatee la salida, ya luego solo es cambiarle el
        cout por la variable y listo, se formateará de la misma forma en que se muestra en consola.
    */
}

void mostrarProfesoresResumido(NodoCola* frente, NodoCola* final) {
    // Verificar si la cola está vacía
    if (frente == NULL) {
        cout << endl;
        cout << "La cola esta vacia." << endl;
        return;
    }

    cout << endl;

    cout << "----- Inicio de la Lista de Profesores -----" << endl << endl;
    // Recorrer la cola
    NodoCola* temp = frente;

    // Mientras no sea el final de la cola
    while (temp != NULL) {
        // Mostramos la dirección de memoria del nodo y los datos del profesor
        cout << "DIRECCION DEL NODO: " << "\t| " << temp << endl;

        cout << "Nombre: " << temp->profesor.nombre << " \t\t| " << &temp->profesor.nombre << endl;
        cout << endl;

        temp = temp->siguiente;
    }

    cout << "----- Fin de la Lista de Profesores -----" << endl;

    system("pause"); // Pausar la pantalla
}

void eliminarProfesores(NodoCola*& frente, NodoCola*& final) {
    if (frente != NULL) {
        cout << "Eliminando el profesor: \t " << frente->profesor.nombre << " ..." << endl;

        // Guardar en una variable temporal el nodo a eliminar
        NodoCola* temp = frente;

        // Si la cola tiene un solo nodo
        if (frente == final) {
            frente = NULL;
            final = NULL;
        }
        else {
            frente = frente->siguiente;
        }

        // Ahora el frente de la cola es el siguiente nodo
        //frente = frente->siguiente;

        // Liberar la memoria del nodo eliminado
        delete temp;

        // Guardar el historial de operaciones de la Cola
        historialCola(frente, final, "Eliminacion de Datos - DEQUEUE");

        Sleep(2000); // Esperar 2 segundo
        cout << "Profesor eliminado con EXITO." << endl;
    }
    else {
        cout << "La lista de profesores está vacia. No hay profesores para eliminar." << endl;
    }
}

void vaciarProfesores(NodoCola*& frente, NodoCola*& final) {
    // Verificar si la cola está vacía
    if (frente != NULL) {
        cout << "Vaciando la lista de profesores..." << endl;

        // Mientras la cola no esté vacía
        while (frente != NULL) {
            cout << "Eliminando el profesor: \t " << frente->profesor.nombre << " ..." << endl;

            // Guardar en una variable temporal el nodo a eliminar
            NodoCola* temp = frente;

            // Si la cola tiene un solo nodo
            if (frente == final) {
                // Reiniciar los punteros de la cola
                frente = NULL;
                final = NULL;
            }
            else {
                // Ahora el frente de la cola es el siguiente nodo
                frente = frente->siguiente;
            }


            // Liberar la memoria del nodo eliminado
            delete temp;

            Sleep(2000); // Esperar 2 segundo
            cout << "Profesor eliminado con EXITO." << endl;
        }

        // Guardar el historial de operaciones de la Cola
        historialCola(frente, final, "Vaciado de Datos");

        Sleep(2000); // Esperar 2 segundo
        cout << "La lista de profesores ha sido vaciada con EXITO." << endl;

        system("pause"); // Pausar la pantalla
    }
    else {
        cout << "La lista de profesores ya esta vacia." << endl;
    }
}

void menuCola(NodoCola*& frente, NodoCola*& final) {
    int opcion = 0;
    int tecla;
    do {
        system("cls"); // Limpiar la pantalla
        cout << "----- Listado de Profesores -----" << endl << endl;
        cout << (opcion == 0 ? "=> " : "   ") << "1- Ingresar datos de nuevo profesor (ENQUEUE)" << endl;
        cout << (opcion == 1 ? "=> " : "   ") << "2- Mostrar todos los profesores (COLA)" << endl;
        cout << (opcion == 2 ? "=> " : "   ") << "3- Eliminar el primer profesor ingresado (DEQUEUE)" << endl;
        cout << (opcion == 3 ? "=> " : "   ") << "4- Vaciar el listado" << endl;
        cout << (opcion == 4 ? "=> " : "   ") << "5- Regresar al Menu Principal" << endl;

        do {
            tecla = _getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13);

        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : 4;
            break;
        case 80: // Flecha abajo
            opcion = (opcion < 4) ? opcion + 1 : 0;
            break;
        case 13: // Enter
            switch (opcion) {
            case 0:
                ingresarProfesores(frente, final);
                mostrarProfesoresResumido(frente, final); // Mostrar el listado de profesores después de ingresar los datos
                break;
            case 1:
                mostrarProfesores(frente, final);
                break;
            case 2:
                eliminarProfesores(frente, final);
                mostrarProfesoresResumido(frente, final); // Mostrar el listado de profesores después de eliminar un profesor
                break;
            case 3:
                vaciarProfesores(frente, final);
                break;
            case 4:
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
            break;
        }
    } while (tecla != 13 || opcion != 4); // Salir si se presiona Enter en la opción 5
}