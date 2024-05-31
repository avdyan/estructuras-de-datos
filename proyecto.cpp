// Declaramos las bibliotecas necesarias
#include <iostream>
#include <iomanip>
#include <Windows.h>        // Para usar la función Sleep()
#include <ctime>			// Para usar la función time()
#include <fstream>			// Para trabajar con archivos
#include <string>			// Para trabajar con cadenas de texto
#include <conio.h>			// Para usar la función _getch() y menu interactivo
#include "colors.h"         // Para usar los colores en la consola
using namespace std;

// Struct que usaremos en la PILA y COLA
// Definición de la estructura para el ingreso de datos del estudiante
struct Estudiante {
    string nombre;
    string apellido;
    string carrera;
    string email;
    int edad;
    long telefono;
};

struct Servicios {
    string nombre;
    string ubicacion;
    string horario;
    string contacto;
    string descripcion;
    string disponible;
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

// Nodo para la Lista Doblemente Enlazada en ordenamiento natural   PROXIMAMENTE
struct NodoLista {
    Servicios servicios;
    NodoLista* siguiente;
    NodoLista* anterior;
};

// Funciones Prototipo Generales
// Función para centrar texto
string centrarTexto(const string& texto, int anchoCampo);
//Funcion que verifica si existe el archivo "historial.txt", si existe pregunta si desea eliminarlo
// o si desea conservarlo, si no existe el archivo, lo crea.
void verificarArchivoHistorial();
// Función que pide el Nodo de la pila a escribir y el tipo de escritura de datos
void historialPila(NodoPila* top, const string& tipoEscritura);
// Función para guardar el historial de operaciones de la Cola
void historialCola(NodoCola* frente, NodoCola* final, const string& tipoEscritura);
// Función para guardar el historial de operaciones de la Lista
void historialLista(NodoLista* inicio, NodoLista* final, const string& tipoEscritura);
// Función para mostrar el historial de operaciones de la Pila y Cola
void mostrarHistorial();
// Funcion para mostrar una animación de entrada
void animacionEntrada();
// Funcion que muestre el menú principal centrado
void mostrarMenuCentrado(int opcionSeleccionada);
// Funcion para verificar si una cadena es un número
bool esNumero(const string& str);
// Funcion para solicitar los datos
string solicitarDato(const string& mensaje, bool esNum);


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
// Funcion para mostrar el menú de la Pila de forma Centrada y con Colores
void mostrarMenuCentradoPila(int opcionSeleccionada);
// Funcion para mostrar el menú de la Pila
void menuPila(NodoPila*& top);


// Funciones Prototipo de la Cola
// Funcion para ingresar un estudiante a la Cola por medio de ENQUEUE
void ingresarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion que le muestre al usuario el listado completo de los nombres y 
// un mensaje en el que el usuario ingresa el nombre del profesor a buscar
// luego, la funcion debe buscar el nombre en la cola y mostrar los datos del profesor junto con la
// posicion en la que se encuentra en la cola y su direccion de memoria
void buscarProfesor(NodoCola* frente, NodoCola* final);
// Funcion para mostrar los datos de todos los profesores
void mostrarProfesores(NodoCola* frente, NodoCola* final);
// Funcion para eliminar el primer profesor de la Cola
void eliminarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion para vaciar la Cola
void vaciarProfesores(NodoCola*& frente, NodoCola*& final);
// Funcion para mostrar el menú de la Cola de forma Centrada y con Colores
void mostrarMenuCentradoCola(int opcionSeleccionada);
// Funcion para mostrar el menú de la Cola
void menuCola(NodoCola*& frente, NodoCola*& final);

// Fciones Prototipo de la Lista Doblemente Enlazada con ordenamiento de forma natural
// Funcion para ingresar un servicio a la Lista
void ingresarServicios(NodoLista*& inicio, NodoLista*& final);
// Funcion para mostrar los datos de todos los servicios de forma resumida
void mostrarServiciosResumido(NodoLista* inicio, NodoLista* final);
// Funcion para mostrar los datos de todos los servicios
void mostrarServicios(NodoLista* inicio, NodoLista* final);
// Funcion que le muestre al usuario el listado completo de los nombres y
// un mensaje en el que el usuario ingresa el nombre del servicio a buscar
// luego, la funcion debe buscar el nombre en la lista y mostrar los datos del servicio junto con la
// posicion en la que se encuentra en la lista y su direccion de memoria
void buscarServicios(NodoLista* inicio, NodoLista* final);
// Funcion para eliminar el primer servicio de la Lista
void eliminarServicios(NodoLista*& inicio, NodoLista*& final);
// Funcion para vaciar la Lista
void vaciarServicios(NodoLista*& inicio, NodoLista*& final);
// Funcion para mostrar el menú de la Lista de forma Centrada y con Colores
void mostrarMenuCentradoLista(int opcionSeleccionada);
// Funcion para mostrar el menú de la Lista
void menuLista(NodoLista*& inicio, NodoLista*& final);


// Menú principal
int main() {
    animacionEntrada(); // Mostrar la animación de entrada
    verificarArchivoHistorial(); // Verificar si el archivo de historial de operaciones existe
    system("cls"); // Limpiar la pantalla

    NodoPila* pilaEstudiantes = NULL;
    NodoCola* frente = NULL;
    NodoCola* final = NULL;
    NodoLista* inicio = NULL;
    NodoLista* finalLista = NULL;

    int opcion = 0;
    int tecla;

    do {
        system("cls");
        cout << centrarTexto("------ SISTEMA DE MANEJO DE ESTUDIANTES ------", 120) << endl << endl;

        mostrarMenuCentrado(opcion);

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
                menuLista(inicio, finalLista);
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
void verificarArchivoHistorial() {
	// Verificar si el archivo de historial de operaciones existe
	ifstream archivo("historial.txt");
    if (archivo.is_open()) {
		archivo.close(); // Cerrar el archivo
		// Preguntar al usuario si desea eliminar el archivo de historial de operaciones
		cout << endl << "El archivo de historial de operaciones ya existe." << endl;
		cout << "Desea eliminar el archivo de historial de operaciones? (S/N): ";
		char respuesta;
		cin >> respuesta;
        if (respuesta == 'S' || respuesta == 's') {
			remove("historial.txt"); // Eliminar el archivo de historial de operaciones
			cout << "El archivo de historial de operaciones ha sido eliminado." << endl;
		}
        else {
			cout << "El archivo de historial de operaciones no ha sido eliminado." << endl;
		}
	}
    else {
		cout << "El archivo de historial de operaciones no existe." << endl;
		ofstream archivo("historial.txt"); // Crear el archivo de historial de operaciones
        if (archivo.is_open()) {
			cout << "El archivo de historial de operaciones ha sido creado." << endl;
			archivo.close(); // Cerrar el archivo
		}
        else {
			cout << "Error al crear el archivo de historial de operaciones." << endl;
		}
	}
}

void mostrarMenuCentrado(int opcionSeleccionada) {
    // Definir el ancho del campo o de la terminal
    int anchoCampo = 120;
    // Definimos las opciones que mostraremos en el menú
    string opciones[] = {
        "Lista de Estudiantes (PILA)",
        "Lista de Profesores (COLA)",
        "Servicios de la Universidad (LISTA DOBLE. ENLAZADA)",
        "Mostrar Historial de Operaciones",
        "Salir"
    };

    // Para cada opción, mostramos el texto centrado en la terminal
    for (int i = 0; i < 5; i++) {
        // Calcular la cantidad de espacios a la izquierda y a la derecha
        int espacios = anchoCampo - opciones[i].size();
        // Dividir los espacios entre la izquierda y la derecha
        int espaciosIzquierda = espacios / 2;
        // Si la opción es la última, los espacios a la derecha serán mayores
        int espaciosDerecha = espacios - espaciosIzquierda;

        if (i == 4) // Antes de la última opción
            cout << endl; // Inserta un salto de línea


        // Mostrar el texto centrado en la terminal
        cout << string(espaciosIzquierda, ' ');
        if (i == opcionSeleccionada) {
            cout << (i == 4 ? "\033[0;30;41m" : "\033[0;30;44m"); // Cambia el color de fondo a rojo para la opción de salida
        }
        // Mostrar el texto de la opción
        cout << opciones[i] << "\033[0m";
        cout << string(espaciosDerecha, ' ') << endl;
    }
}

string centrarTexto(const string& texto, int anchoCampo) {
    int espacios = static_cast<int>(anchoCampo - texto.size());
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

void historialLista(NodoLista* inicio, NodoLista* final, const string& tipoEscritura) {
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

		NodoLista* temp = inicio;

		// Calcular el tamaño de la lista para determinar cuantos structs tenemos
		int tamanoLista = 0;
        while (temp != NULL) {
			tamanoLista++;
			temp = temp->siguiente;
		}
		temp = inicio;

		// Asignamos memoria dinamica para almacenar las cadenas de cada struct
		string** datos = new string * [tamanoLista];
        for (int i = 0; i < tamanoLista; ++i) {
			datos[i] = new string[6];
		}

		int indice = 0;
        while (temp != NULL) {
			datos[indice][0] = "|| Nombre: " + temp->servicios.nombre;
			datos[indice][1] = "|| Ubicacion: " + temp->servicios.ubicacion;
			datos[indice][2] = "|| Horario: " + temp->servicios.horario;
			datos[indice][3] = "|| Contacto: " + temp->servicios.contacto;
			datos[indice][4] = "|| Descripcion: " + temp->servicios.descripcion;
			datos[indice][5] = "|| Disponible: " + temp->servicios.disponible;

			temp = temp->siguiente;
			indice++;
		}

		// Escribir las líneas horizontales para los structs
        for (int i = 0; i < tamanoLista; ++i) {
			archivo << "===============================" << "\t\t";
		}
		archivo << endl;

		// Escribir los datos de cada campo para todos los structs
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < tamanoLista; ++j) {
                archivo << left << setw(30) << datos[j][i] << "||\t";
            }
            archivo << endl;
        }

        // Escribir las líneas horizontales para los structs
        for (int i = 0; i < tamanoLista; ++i) {
			archivo << "===============================" << "\t\t";
		}
        archivo << endl << endl;

        // Liberar la memoria dinámica
        for (int i = 0; i < tamanoLista; ++i) {
            delete[] datos[i];
        }
        delete[] datos;

        archivo.close(); // Cerrar el archivo
    }

    else {
		cout << "Error al abrir el archivo de historial de operaciones de la Lista." << endl;
    }
}

void mostrarHistorial() {
    system("cls"); // Limpiar la pantalla

    cout << "\033[40;34m" << centrarTexto("------ HISTORIAL DE OPERACIONES ------", 120) << "\033[0m" << endl << endl;

    // Leer el archivo de historial de operaciones
    ifstream archivo("historial.txt");

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close(); // Cerrar el archivo

        system("pause"); // Pausar la pantalla
    }
    else {
        cout << "Error al abrir el archivo de historial de operaciones." << endl;
    }
}

void animacionEntrada() {        // Intro Animada
    system("color 9");
    int espacios = 35;

    cout << string(espacios, ' ') << " *  *  *  *****  *     *****  ***    * * *    *****   " << endl;
    Sleep(300);
    cout << string(espacios, ' ') << " *  *  *  *      *     *     *   *  *  *  *   *        " << endl;
    Sleep(300);
    cout << string(espacios, ' ') << " *  *  *  *****  *     *     *   *  *  *  *   *****    " << endl;
    Sleep(300);
    cout << string(espacios, ' ') << " *  *  *  *      *     *     *   *  *  *  *   *         " << endl;
    Sleep(300);
    cout << string(espacios, ' ') << "  * * *   *****  ****  *****  ***   *  *  *   *****     " << endl;
    Sleep(300);
    cout << string(espacios, ' ') << "=============================================" << endl;
    Sleep(500);
    cout << string(espacios, ' ') << "SISTEMA DE MANEJO DE ESTUDIANTES" << endl;
    Sleep(500);
    _getch();
}

bool esNumero(const string& str) {
    return !str.empty() && find_if(str.begin(),
        str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end();
}

string solicitarDato(const string& mensaje, bool esNum) {
    while (true) {
        int espacios = 35;
        cout << string(espacios, ' ') << mensaje;
        string dato;
        cin >> dato;
        if (dato == "C" || dato == "c") {
            cout << "\033[1;31m" << string(espacios, ' ') << "Operacion cancelada." << "\033[0m" << endl;
            throw std::runtime_error("Operacion cancelada");
        }
        if (!esNum || (esNum && esNumero(dato))) {
            return dato;
        }
        cout << string(espacios, ' ') << "\033[1;31mPor favor, ingrese un NUMERO.\033[0m" << endl;
    }
}

// ########################## PILA ##################################

void ingresarEstudiantes(NodoPila*& top) {
    // Reservar memoria para un nuevo nodo
    NodoPila* nuevo = nullptr;

    int espacios = 35;

    try {
        nuevo = new NodoPila;

        system("cls"); // Limpiar la pantalla
        cout << centrarTexto("\033[1;34m###### INGRESO DE DATOS DEL ESTUDIANTE ######\033[0m", 120) << endl << endl;
        cout << centrarTexto("Presione 'C' para cancelar la operacion", 110) << endl << endl;

        nuevo->estudiante.nombre = solicitarDato("Nombre: ", false);
        nuevo->estudiante.apellido = solicitarDato("Apellido: ", false);
        nuevo->estudiante.edad = stoi(solicitarDato("Edad: ", true));
        nuevo->estudiante.carrera = solicitarDato("Carrera: ", false);
        nuevo->estudiante.email = solicitarDato("Email: ", false);
        nuevo->estudiante.telefono = stol(solicitarDato("Telefono: ", true));

        // Enlazar el nuevo nodo con el nodo superior
        nuevo->siguiente = top;
        // El nuevo nodo se convierte en el nodo superior
        top = nuevo;

        cout << endl << "\033[1;34m" << string(espacios, ' ') << "Estudiante ingresado con EXITO." << "\033[0m" << endl;

        historialPila(top, "Ingreso de Datos - PUSH"); // Guardar el historial de operaciones de la Pila
    }
    catch (const std::runtime_error& e) {
        // Si el usuario cancela la operación, se libera la memoria reservada para el nuevo nodo
        if (nuevo) {
            delete nuevo;
        }
    }
}

void mostrarEstudiantesResumido(NodoPila* top) {
    // Verificar si la pila está vacía
    if (!top) {
        cout << endl;
        cout << endl << centrarTexto("\033[1;31mLa pila esta vacia.\033[0m", 120) << endl;
        return;
    }

    cout << endl;
    // Recorrer la pila
    NodoPila* temp = top;

    // Mientras no sea el final de la pila
    int anchoCampo = 120;
    int anchoTexto = 30;
    int espacios = (anchoCampo - anchoTexto) / 2;

    cout << endl << centrarTexto("\033[1;32m----- Fin de la Lista de Estudiantes -----\033[0m", 140) << endl;

    while (temp != NULL) {
        // Guardar los datos del estudiante en el archivo
        cout << string(espacios, ' ') << "================================" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Nombre: " + temp->estudiante.nombre) << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Apellido: " + temp->estudiante.apellido) << " ||" << endl;
        cout << string(espacios, ' ') << "================================" << endl;

        temp = temp->siguiente;
    }

    cout << endl << centrarTexto("\033[1;32m----- Inicio de la Lista de Estudiantes -----\033[0m", 140) << endl;

    system("pause"); // Pausar la pantalla
}

void mostrarEstudiantes(NodoPila* top) {
    // Limpiar pantalla
    system("cls");

    // Verificar si la pila está vacía
    if (!top) {
        cout << endl << centrarTexto("\033[1;31mLa pila esta vacia.\033[0m", 120) << endl;
        system("pause"); // Pausar la pantalla
        return;
    }

    // TITULO
    cout << centrarTexto("\033[1;34m##### LISTADO DE ESTUDIANTES #####\033[0m", 140) << endl;

    cout << endl << centrarTexto("\033[1;32m----- Fin de la Lista de Estudiantes -----\033[0m", 140) << endl;

    // Recorrer la pila
    NodoPila* temp = top;

    // Mientras no sea el final de la pila
    int anchoCampo = 120;
    int anchoTexto = 48;
    int espacios = (anchoCampo - anchoTexto) / 2;

    while (temp != NULL) {
        // Guardar los datos del estudiante en el archivo
        cout << string(espacios, ' ') << "==================================================" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Nombre: " + temp->estudiante.nombre) << "| " << &temp->estudiante.nombre << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Apellido: " + temp->estudiante.apellido) << "| " << &temp->estudiante.apellido << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Edad: " + to_string(temp->estudiante.edad)) << "| " << &temp->estudiante.edad << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Carrera: " + temp->estudiante.carrera) << "| " << &temp->estudiante.carrera << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Email: " + temp->estudiante.email) << "| " << &temp->estudiante.email << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Telefono: " + to_string(temp->estudiante.telefono)) << "| " << &temp->estudiante.telefono << " ||" << endl;
        cout << string(espacios, ' ') << "==================================================" << endl;

        temp = temp->siguiente;
    }

    cout << endl << centrarTexto("\033[1;32m----- Inicio de la Lista de Estudiantes -----\033[0m", 140) << endl;

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

void mostrarMenuCentradoPila(int opcionSeleccionada) {
    // Definir el ancho del campo o de la terminal
    int anchoCampo = 120;
    // Definimos las opciones que mostraremos en el menú
    string opciones[] = {
        "Ingresar datos de un nuevo estudiante (PUSH)",
        "Mostrar todos los estudiantes (PILA)",
        "Eliminar el ultimo estudiante ingresado (POP)",
        "Vaciar la Pila",
        "Regresar al Menu Principal"
    };

    // Para cada opción, mostramos el texto centrado en la terminal
    for (int i = 0; i < 5; i++) {
        // Calcular la cantidad de espacios a la izquierda y a la derecha
        int espacios = anchoCampo - opciones[i].size();
        // Dividir los espacios entre la izquierda y la derecha
        int espaciosIzquierda = espacios / 2;
        // Si la opción es la última, los espacios a la derecha serán mayores
        int espaciosDerecha = espacios - espaciosIzquierda;

        if (i == 4) // Antes de la última opción
            cout << endl; // Inserta un salto de línea

        // Mostrar el texto centrado en la terminal
        cout << string(espaciosIzquierda, ' ');
        if (i == opcionSeleccionada) {
            cout << (i == 4 ? "\033[0;30;41m" : "\033[0;30;42m"); // Cambia el color de fondo a rojo para la opción de salida
        }
        // Mostrar el texto de la opción
        cout << opciones[i] << "\033[0m";
        cout << string(espaciosDerecha, ' ') << endl;
    }
}

void menuPila(NodoPila*& top) {
    int opcion = 0;
    int tecla;
    do {
        system("cls");
        cout << centrarTexto("----- LISTADO DE ESTUDIANTES - PILA -----", 120) << endl << endl;

        mostrarMenuCentradoPila(opcion);

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
    NodoCola* nuevo = nullptr;

    try {
        nuevo = new NodoCola;

        int espacios = 35;

        system("cls"); // Limpiar la pantalla
        cout << centrarTexto("\033[1;34m###### INGRESO DE DATOS DEL PROFESOR ######\033[0m", 120) << endl << endl;
        cout << centrarTexto("\033[1;34mPresione 'C' para cancelar la operacion\033[0m", 120) << endl << endl;

        nuevo->profesor.nombre = solicitarDato("Nombre: ", false);
        nuevo->profesor.apellido = solicitarDato("Apellido: ", false);
        nuevo->profesor.edad = stoi(solicitarDato("Edad: ", true));
        nuevo->profesor.departamento = solicitarDato("Departamento: ", false);
        nuevo->profesor.email = solicitarDato("Email: ", false);
        nuevo->profesor.telefono = stol(solicitarDato("Telefono: ", true));

        nuevo->siguiente = NULL;

        if (frente == NULL) {
            frente = nuevo;
        }
        else {
            final->siguiente = nuevo;
        }

        final = nuevo;

        historialCola(frente, final, "Ingreso de Datos - ENQUEUE");

        Sleep(1000); // Esperar 1 segundo
        cout << endl << "\033[1;34m" << string(espacios, ' ') << "Profesor ingresado con EXITO." << "\033[0m" << endl;
    }
    catch (const runtime_error& e) {
        if (nuevo) {
            delete nuevo;
        }
    }
}

void buscarProfesor(NodoCola* frente, NodoCola* final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m###### BUSQUEDA DE PROFESOR ######\033[0m", 120) << endl << endl;

    if (frente == NULL) {
        cout << endl << centrarTexto("\033[1;31mLa pila esta vacia.\033[0m", 120) << endl;
        system("pause"); // Pausar la pantalla
		return;
	}

    int espacios = 35;

    cout << string(espacios, ' ') << "Listado de Profesores:" << endl;

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
		datos[i] = new string[2];
	}

	int indice = 0;
    while (temp != NULL) {
		datos[indice][0] = temp->profesor.nombre;
		datos[indice][1] = temp->profesor.apellido;

		temp = temp->siguiente;
		indice++;
	}

	// Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << string(espacios, ' ') << (i + 1) << ". " << datos[i][0] << endl;
    }

	cout << endl;

	string nombreProfesor = solicitarDato("Ingrese el nombre del profesor a buscar: ", false);

	temp = frente;
	int posicion = 0;
	bool encontrado = false;

    while (temp != NULL) {
        if (temp->profesor.nombre == nombreProfesor) {
			encontrado = true;
			break;
		}
		temp = temp->siguiente;
		posicion++;
	}

    cout << endl;

    if (encontrado) {
        cout << string(espacios, ' ') << "Profesor encontrado en la posicion: " << posicion << endl << endl;

        cout << string(espacios, ' ') << "==================================================" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Nombre: " + temp->profesor.nombre) << "| " << &temp->profesor.nombre << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Apellido: " + temp->profesor.apellido) << "| " << &temp->profesor.apellido << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Edad: " + to_string(temp->profesor.edad)) << "| " << &temp->profesor.edad << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Carrera: " + temp->profesor.departamento) << "| " << &temp->profesor.departamento << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Email: " + temp->profesor.email) << "| " << &temp->profesor.email << " ||" << endl;
        cout << string(espacios, ' ') << left << setw(30) << ("|| Telefono: " + to_string(temp->profesor.telefono)) << "| " << &temp->profesor.telefono << " ||" << endl;
        cout << string(espacios, ' ') << "==================================================" << endl;
    }
    else {
        cout << "\033[1;31m" << string(espacios, ' ') << "Profesor no encontrado." << "\033[0m" << endl << endl;
    }

	// Liberar la memoria dinámica
    for (int i = 0; i < tamanoCola; ++i) {
		delete[] datos[i];
	}
	delete[] datos;

    system("pause"); // Pausar la pantalla
}

void mostrarProfesores(NodoCola* frente, NodoCola* final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m##### LISTADO DE PROFESORES #####\033[0m", 140) << endl;

    cout << centrarTexto("Modelo de Datos: ", 120) << endl;
    cout << centrarTexto("|| Nombre || Apellido || Edad || Departamento || Email || Telefono ||", 120) << endl;

    // Verificar si la cola está vacía
    if (frente == NULL) {
        cout << endl;
        cout << endl << centrarTexto("\033[1;31mLa pila esta vacia.\033[0m", 120) << endl;
        system("pause"); // Pausar la pantalla
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
        datos[indice][0] = "|| " + temp->profesor.nombre;
        datos[indice][1] = "|| " + temp->profesor.apellido;
        datos[indice][2] = "|| " + to_string(temp->profesor.edad);
        datos[indice][3] = "|| " + temp->profesor.departamento;
        datos[indice][4] = "|| " + temp->profesor.email;
        datos[indice][5] = "|| " + to_string(temp->profesor.telefono);

        temp = temp->siguiente;
        indice++;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "=====================" << "\t";
    }
    cout << endl;

    // Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < tamanoCola; ++j) {
            cout << left << setw(20) << datos[j][i] << "||\t";
        }
        cout << endl;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "=====================" << "\t";
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
        cout << "\033[1;31m" << centrarTexto("La cola esta vacia.", 120) << "\033[0m" << endl;

        system("pause"); // Pausar la pantalla
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
        datos[i] = new string[2];
    }

    int indice = 0;
    while (temp != NULL) {
        datos[indice][0] = "|| " + temp->profesor.nombre;
        datos[indice][1] = "|| " + temp->profesor.apellido;

        temp = temp->siguiente;
        indice++;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "======================" << "\t";
    }
    cout << endl;

    // Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < tamanoCola; ++j) {
            cout << left << setw(20) << datos[j][i] << "||\t";
        }
        cout << endl;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoCola; ++i) {
        cout << "======================" << "\t";
    }
    cout << endl << endl;

    system("pause"); // Pausar la pantalla
}

void eliminarProfesores(NodoCola*& frente, NodoCola*& final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m##### ELIMINACION DE PROFESOR #####\033[0m", 120) << endl << endl;

    if (frente != NULL) {
        cout << centrarTexto("Eliminando el profesor: \t " + frente->profesor.nombre + " ...", 120) << endl;

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
        cout << "\033[1;31m" << centrarTexto("Profesor eliminado con EXITO.", 120) << "\033[0m" << endl;
    }
    else {
        cout << "\033[1;31m" << centrarTexto("La lista de profesores está vacia. No hay profesores para eliminar.", 120) << "\033[0m" << endl;
    }
}

void vaciarProfesores(NodoCola*& frente, NodoCola*& final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m##### VACIADO DE LISTA DE PROFESORES #####\033[0m", 120) << endl << endl;

    int espacios = 35;

    if (frente != NULL) {
        // Mientras la cola no esté vacía
        while (frente != NULL) {
            cout << "\033[1;33m" << string(espacios, ' ') << "Eliminando el profesor: \t " << frente->profesor.nombre << " ..." << "\033[0m" << endl;

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
            cout << "\033[1;31m" << string(espacios, ' ') << "Profesor eliminado con EXITO." << "\033[0m" << endl << endl;
        }

        // Guardar el historial de operaciones de la Cola
        historialCola(frente, final, "Vaciado de Datos");

        Sleep(2000); // Esperar 2 segundo
        cout << "\033[1;32m" << string(espacios, ' ') << "La lista de profesores ha sido vaciada con EXITO." << "\033[0m" << endl;
    }
    else {
        cout << "\033[1;31m" << string(espacios, ' ') << "La lista de profesores ya esta vacia." << "\033[0m" << endl;
    }

    system("pause"); // Pausar la pantalla
}

void mostrarMenuCentradoCola(int opcionSeleccionada) {
    // Definir el ancho del campo o de la terminal
    int anchoCampo = 120;
    // Definimos las opciones que mostraremos en el menú
    string opciones[] = {
        "Ingresar datos de un nuevo profesor (ENQUEUE)",
        "Mostrar todos los profesores (COLA)",
        "Buscar un profesor en la cola (detallado)",
        "Eliminar el primer profesor ingresado (DEQUEUE)",
        "Vaciar la Cola",
        "Regresar al Menu Principal"
    };

    // Para cada opción, mostramos el texto centrado en la terminal
    for (int i = 0; i < 6; i++) {
        // Calcular la cantidad de espacios a la izquierda y a la derecha
        int espacios = anchoCampo - opciones[i].size();
        // Dividir los espacios entre la izquierda y la derecha
        int espaciosIzquierda = espacios / 2;
        // Si la opción es la última, los espacios a la derecha serán mayores
        int espaciosDerecha = espacios - espaciosIzquierda;

        if (i == 5) // Antes de la última opción
            cout << endl; // Inserta un salto de línea

        // Mostrar el texto centrado en la terminal
        cout << string(espaciosIzquierda, ' ');
        if (i == opcionSeleccionada) {
            cout << (i == 5 ? "\033[0;30;41m" : "\033[0;30;45m"); // Cambia el color de fondo a rojo para la opción de salida
        }
        // Mostrar el texto de la opción
        cout << opciones[i] << "\033[0m";
        cout << string(espaciosDerecha, ' ') << endl;
    }
}

void menuCola(NodoCola*& frente, NodoCola*& final) {
    int opcion = 0;
    int tecla;
    do {
        system("cls"); // Limpiar la pantalla
        cout << centrarTexto("----- LISTADO DE PROFESORES - COLA -----", 120) << endl << endl;

        mostrarMenuCentradoCola(opcion);

        do {
            tecla = _getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13);

        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : 5;
            break;
        case 80: // Flecha abajo
            opcion = (opcion < 5) ? opcion + 1 : 0;
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
                buscarProfesor(frente, final);
                break;
            case 3:
                eliminarProfesores(frente, final);
                mostrarProfesoresResumido(frente, final); // Mostrar el listado de profesores después de eliminar un profesor
                break;
            case 4:
                vaciarProfesores(frente, final);
                break;
            case 5:
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
            break;
        }
    } while (tecla != 13 || opcion != 5); // Salir si se presiona Enter en la opción 5
}

// ########################## LISTA ##################################

void ingresarServicios(NodoLista*& inicio, NodoLista*& final) {
    NodoLista* nuevo = nullptr;

    try {
        nuevo = new NodoLista;

        system("cls"); // Limpiar la pantalla
        cout << "\033[1;34m" << centrarTexto("###### INGRESO DE DATOS DEL SERVICIO ######", 120) << "\033[0m" << endl << endl;
        cout << centrarTexto("Presione 'C' para cancelar la operacion", 120) << endl << endl;

        nuevo->servicios.nombre = solicitarDato("Nombre: ", false);
        nuevo->servicios.ubicacion = solicitarDato("Ubicacion: ", false);
        nuevo->servicios.horario = solicitarDato("Horario: ", false);
        nuevo->servicios.contacto = solicitarDato("Contacto: ", false);
        nuevo->servicios.descripcion = solicitarDato("Descripcion: ", false);
        string disponibilidad;
        do {
            disponibilidad = solicitarDato("Disponible (Si, No): ", false);
            if (disponibilidad != "Si" && disponibilidad != "No") {
                string mensaje = "Error: Entrada invalida. Por favor, ingrese 'Si' o 'No'.";
                cout << "\033[1;31m" << centrarTexto(mensaje, 120) << "\033[0m" << endl;
            }
        } while (disponibilidad != "Si" && disponibilidad != "No");
        nuevo->servicios.disponible = disponibilidad;

        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;

        if (inicio == NULL) {
            inicio = nuevo;
        }
        else {
            final->siguiente = nuevo;
            nuevo->anterior = final;
        }

        final = nuevo;

        Sleep(1000); // Esperar 1 segundo
        cout << "\033[1;32m" << centrarTexto("Servicio ingresado con EXITO.", 120) << "\033[0m" << endl;

        // Guardar el historial de operaciones de la Lista
        historialLista(inicio, final, "Ingreso de Datos - INSERT - LISTA");
    }
    catch (const runtime_error& e) {
        if (nuevo) {
            delete nuevo;
        }
    }
}

void mostrarServiciosResumido(NodoLista* inicio, NodoLista* final) {
    // Verificar si la cola está vacía
    if (inicio == NULL) {
        cout << "\033[1;31m" << centrarTexto("La cola esta vacia.", 120) << "\033[0m" << endl;

        system("pause"); // Pausar la pantalla
        return;
    }

    cout << endl;

    // Recorrer la cola
    NodoLista* temp = inicio;

    // Calcular el tamaño de la cola para determinar cuantos structs tenemos
    int tamanoLista = 0;
    while (temp != NULL) {
        tamanoLista++;
        temp = temp->siguiente;
    }
    temp = inicio;

    // Asignamos memoria dinamica para almacenar las cadenas de cada struct
    string** datos = new string * [tamanoLista];
    for (int i = 0; i < tamanoLista; ++i) {
        datos[i] = new string[2];
    }

    int indice = 0;
    while (temp != NULL) {
        datos[indice][0] = "|| " + temp->servicios.nombre;
        datos[indice][1] = "|| " + temp->servicios.descripcion;

        temp = temp->siguiente;
        indice++;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoLista; ++i) {
        cout << "======================" << "\t";
    }
    cout << endl;

    // Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < tamanoLista; ++j) {
            cout << left << setw(20) << datos[j][i] << "||\t";
        }
        cout << endl;
    }

    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoLista; ++i) {
        cout << "======================" << "\t";
    }
    cout << endl << endl;

    system("pause"); // Pausar la pantalla
}

void mostrarServicios(NodoLista* inicio, NodoLista* final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m##### LISTADO DE SERVICIOS #####\033[0m", 140) << endl;
    cout << centrarTexto("Modelo de Datos: ", 120) << endl;
    cout << centrarTexto("|| Nombre || Ubicacion || Horario || Contacto || Descripcion || Disponible ||", 120) << endl;


	// Verificar si la lista está vacía
    if (inicio == NULL) {
		cout << endl;
		cout << "La lista de servicios está vacia." << endl;
        system("pause"); // Pausar la pantalla
		return;
	}

	cout << endl;

	// Recorrer la lista
	NodoLista* temp = inicio;

	// Calcular el tamaño de la lista para determinar cuantos structs tenemos
	int tamanoLista = 0;
    while (temp != NULL) {
		tamanoLista++;
		temp = temp->siguiente;
	}
	temp = inicio;

	// Asignamos memoria dinamica para almacenar las cadenas de cada struct
	string** datos = new string * [tamanoLista];
    for (int i = 0; i < tamanoLista; ++i) {
		datos[i] = new string[6];
	}

	int indice = 0;
    while (temp != NULL) {
		datos[indice][0] = "|| " + temp->servicios.nombre;
		datos[indice][1] = "|| " + temp->servicios.ubicacion;
		datos[indice][2] = "|| " + temp->servicios.horario;
		datos[indice][3] = "|| " + temp->servicios.contacto;
		datos[indice][4] = "|| " + temp->servicios.descripcion;
        datos[indice][5] = "|| " + temp->servicios.disponible;
		
        temp = temp->siguiente;
		indice++;
	}

	// Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoLista; ++i) {
		cout << "=====================" << "\t";
	}
	cout << endl;

	// Escribir los datos de cada campo para todos los structs
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < tamanoLista; ++j) {
			cout << left << setw(20) << datos[j][i]  << "||\t";
		}
        cout << endl;
    }


    // Escribir las líneas horizontales para los structs
    for (int i = 0; i < tamanoLista; ++i) {
        cout << "=====================" << "\t";
    }
    cout << endl << endl;

    system("pause"); // Pausar la pantalla
}

void buscarServicios(NodoLista* inicio, NodoLista* final) {
    system("cls"); // Limpiar la pantalla

    cout << centrarTexto("\033[1;34m##### BUSQUEDA DE SERVICIO #####\033[0m", 120) << endl << endl;

    if (inicio == NULL) {
		cout << endl << centrarTexto("\033[1;31mLa lista de servicios está vacia.\033[0m", 120) << endl;
		system("pause"); // Pausar la pantalla
		return;
    }

    int espacios = 35;

    cout << string(espacios, ' ') << "Listado de Servicios:" << endl;

    NodoLista* temp = inicio;

    // Calcular el tamaño de la lista para determinar cuantos structs tenemos
    int tamanoLista = 0;
    while (temp != NULL) {
        tamanoLista++;
        temp = temp->siguiente;
    }

    temp = inicio;

    // Asignamos memoria dinamica para almacenar las cadenas de cada struct
    string** datos = new string * [tamanoLista];
    for (int i = 0; i < tamanoLista; ++i) {
		datos[i] = new string[2];
	}

    int indice = 0;
    while (temp != NULL) {
		datos[indice][0] = temp->servicios.nombre;
		datos[indice][1] = temp->servicios.descripcion;

		temp = temp->siguiente;
		indice++;
	}

	cout << endl;

    for (int i = 0; i < tamanoLista; ++i) {
		cout << string(espacios, ' ') << (i + 1) << ". " << datos[i][0] << endl;
	}

    cout << endl;

    string nombreServicio = solicitarDato("Ingrese el nombre del servicio a buscar: ", false);

    temp = inicio;

    int posicion = 0;

    bool encontrado = false;

    while (temp != NULL) {
        if (temp->servicios.nombre == nombreServicio) {
            encontrado = true;
            break;
        }
        temp = temp->siguiente;
        posicion++;
    }

    cout << endl;

    if (encontrado) {
        cout << string(espacios, ' ') << "Servicio encontrado en la posicion: " << posicion << endl << endl;

		cout << string(espacios, ' ') << "==================================================" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Nombre: " + temp->servicios.nombre) << "| " << &temp->servicios.nombre << " ||" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Ubicacion: " + temp->servicios.ubicacion) << "| " << &temp->servicios.ubicacion << " ||" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Horario: " + temp->servicios.horario) << "| " << &temp->servicios.horario << " ||" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Contacto: " + temp->servicios.contacto) << "| " << &temp->servicios.contacto << " ||" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Descripcion: " + temp->servicios.descripcion) << "| " << &temp->servicios.descripcion << " ||" << endl;
		cout << string(espacios, ' ') << left << setw(30) << ("|| Disponible: " + temp->servicios.disponible) << "| " << &temp->servicios.disponible << " ||" << endl;
		cout << string(espacios, ' ') << "==================================================" << endl;
	}
    else {
		cout << "\033[1;31m" << string(espacios, ' ') << "Servicio no encontrado." << "\033[0m" << endl << endl;
	}

    // Liberar la memoria dinámica
    for (int i = 0; i < tamanoLista; ++i) {
		delete[] datos[i];
	}

    delete[] datos;

	system("pause"); // Pausar la pantalla
}

void eliminarServicios(NodoLista*& inicio, NodoLista*& final) {
    system("cls"); // Limpiar la pantalla

    cout << "\033[1;34m" << centrarTexto("##### ELIMINACION DE SERVICIO #####", 120) << "\033[0m" << endl << endl;

    int espacios = 35;

    // Si la lista no está vacía
    if (inicio != NULL) {
        NodoLista* temp = inicio;
        int i = 1;

        cout << string(espacios, ' ') << "Listado de Servicios:" << endl;

        // Mostrar los nombres de los servicios
        while (temp != NULL) {
            cout << string(espacios, ' ') << i << ". " << temp->servicios.nombre << endl;
            temp = temp->siguiente;
            i++;
        }

        int opcion;
        cout << string(espacios, ' ') << "Ingrese el numero del servicio a eliminar: ";
        cin >> opcion;

        temp = inicio;
        NodoLista* anterior = NULL;
        i = 1;
        while (temp != NULL && i < opcion) {
            anterior = temp;
            temp = temp->siguiente;
            i++;
        }

        if (temp == NULL) {
            cout << string(espacios, ' ') << "Servicio no encontrado." << endl;
        }
        else {
            if (anterior == NULL) {
                inicio = temp->siguiente;
                if (inicio == NULL) {
                    final = NULL;
                }
            }
            else {
                anterior->siguiente = temp->siguiente;
                if (temp == final) {
                    final = anterior;
                }
            }
            delete temp;
            cout << "\033[1;31m" << string(espacios, ' ') << "Servicio eliminado con EXITO." << "\033[0m" << endl;

            // Guardar el historial de operaciones de la Lista
            historialLista(inicio, final, "Eliminacion de Datos - DELETE - LISTA");
        }
    }
    else {
        cout << endl << "\033[1;31m" << string(espacios, ' ') << "La lista de servicios esta vacia." << "\033[0m" << endl;
    }
}

void vaciarServicios(NodoLista*& inicio, NodoLista*& final) {
    system("cls"); // Limpiar la pantalla

    cout << "\033[1;34m" << centrarTexto("##### VACIADO DE LISTA DE SERVICIOS #####", 120) << "\033[0m" << endl << endl;

    int espacios = 35;

	// Verificar si la lista está vacía
    if (inicio != NULL) {
		// Mientras la lista no esté vacía
        while (inicio != NULL) {
			cout << string(espacios, ' ') << "Eliminando el servicio: \t " << inicio->servicios.nombre << " ..." << endl;

			// Guardar en una variable temporal el nodo a eliminar
			NodoLista* temp = inicio;

			// Si la lista tiene un solo nodo
            if (inicio == final) {
				// Reiniciar los punteros de la lista
				inicio = NULL;
				final = NULL;
			}
            else {
				// Ahora el inicio de la lista es el siguiente nodo
				inicio = inicio->siguiente;
			}

			// Liberar la memoria del nodo eliminado
			delete temp;

			Sleep(2000); // Esperar 2 segundo
            cout << "\033[1;31m" << string(espacios, ' ') << "Servicio eliminado con EXITO." << "\033[0m" << endl;

            // Guardar el historial de operaciones de la Lista
            historialLista(inicio, final, "Vaciado de Datos - DELETE - LISTA");
		}
	}   
    else {
		cout << "\033[1;31m" << string(espacios, ' ') << "La lista de servicios ya esta vacia." << "\033[0m" << endl;
	}
}

void mostrarMenuCentradoLista(int opcionSeleccionada) {
	// Definir el ancho del campo o de la terminal
	int anchoCampo = 120;
	// Definimos las opciones que mostraremos en el menú
    string opciones[] = {
		"Ingresar datos de un nuevo servicio",
		"Mostrar todos los servicios",
        "Buscar un servicio en la lista",
		"Eliminar un servicio",
		"Vaciar el listado",
		"Regresar al Menu Principal"
	};

	// Para cada opción, mostramos el texto centrado en la terminal
    for (int i = 0; i < 6; i++) {
		// Calcular la cantidad de espacios a la izquierda y a la derecha
		int espacios = anchoCampo - opciones[i].size();
		// Dividir los espacios entre la izquierda y la derecha
		int espaciosIzquierda = espacios / 2;
		// Si la opción es la última, los espacios a la derecha serán mayores
		int espaciosDerecha = espacios - espaciosIzquierda;

		if (i == 5) // Antes de la última opción
			cout << endl; // Inserta un salto de línea

		// Mostrar el texto centrado en la terminal
		cout << string(espaciosIzquierda, ' ');
        if (i == opcionSeleccionada) {
			cout << (i == 5 ? "\033[0;30;41m" : "\033[0;30;43m"); // Cambia el color de fondo a rojo para la opción de salida
		}
		// Mostrar el texto de la opción
		cout << opciones[i] << "\033[0m";
		cout << string(espaciosDerecha, ' ') << endl;
	}
}

void menuLista(NodoLista*& inicio, NodoLista*& final) {
    int opcion = 0;
    int tecla;
    do {
        system("cls"); // Limpiar la pantalla
        cout << "\033[1;34m" << centrarTexto("##### LISTADO DE SERVICIOS - LISTA #####", 120) << "\033[0m" << endl << endl;

        mostrarMenuCentradoLista(opcion);

        do {
            tecla = _getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13);

        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : 5;
            break;
        case 80: // Flecha abajo
            opcion = (opcion < 5) ? opcion + 1 : 0;
            break;
        case 13: // Enter
            switch (opcion) {
            case 0:
                ingresarServicios(inicio, final);
                mostrarServiciosResumido(inicio, final); // Mostrar el listado de servicios después de ingresar los datos
                break;
            case 1:
                mostrarServicios(inicio, final);
                break;
            case 2:
                buscarServicios(inicio, final);
				break;
            case 3:
                eliminarServicios(inicio, final);
                mostrarServiciosResumido(inicio, final); // Mostrar el listado de servicios después de eliminar un servicio
                break;
            case 4:
                vaciarServicios(inicio, final);
                mostrarServiciosResumido(inicio, final); // Mostrar el listado de servicios después de vaciar la lista
                break;
            case 5:
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
            break;
        }
    } while (tecla != 13 || opcion != 5); // Salir si se presiona Enter en la opción 5
}