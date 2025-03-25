#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


template <typename T>
class Cola {
private:
    vector<T> elementos;

public:
    void encolar(const T& elemento) {
        elementos.push_back(elemento);
    }

    T desencolar() {
        if (estaVacia()) {
            throw runtime_error("La cola esta vacia");
        }
        T elemento = elementos.front();
        elementos.erase(elementos.begin());
        return elemento;
    }

    const T& frente() const {
        if (estaVacia()) {
            throw runtime_error("La cola esta vacia");
        }
        return elementos.front();
    }

    bool estaVacia() const {
        return elementos.empty();
    }

    size_t tamano() const {
        return elementos.size();
    }


    int buscarLineal(const string& nombre) const {
        int posicion = 0;
        for (const auto& elemento : elementos) {
            if (elemento.getNombreAlumno() == nombre) {
                return posicion;
            }
            posicion++;
        }
        return -1;
    }
};

class Solicitud {
private:
    string nombreAlumno;
    string nombreCarrera;
    int totalMateriasAprobadas;
    float promedioGeneral;

public:
    Solicitud(string nombre, string carrera, int materias, float promedio)
        : nombreAlumno(nombre), nombreCarrera(carrera),
          totalMateriasAprobadas(materias), promedioGeneral(promedio) {}


    string getNombreAlumno() const { return nombreAlumno; }
    string getNombreCarrera() const { return nombreCarrera; }
    int getTotalMateriasAprobadas() const { return totalMateriasAprobadas; }
    float getPromedioGeneral() const { return promedioGeneral; }


    bool operator<(const Solicitud& otra) const {
        return nombreAlumno < otra.nombreAlumno;
    }
};

class SistemaConstancias {
private:
    Cola<Solicitud> colaSolicitudes;


    int busquedaBinaria(const vector<Solicitud>& solicitudes, const string& nombre) const {
        int izquierda = 0;
        int derecha = solicitudes.size() - 1;

        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            if (solicitudes[medio].getNombreAlumno() == nombre) {
                return medio;
            }

            if (solicitudes[medio].getNombreAlumno() < nombre) {
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }
        return -1;
    }

public:
    void altaSolicitud() {
        string nombre, carrera;
        int materias;
        float promedio;

        cout << "Ingrese nombre del alumno: ";
        getline(cin >> ws, nombre);

        cout << "Ingrese nombre de la carrera: ";
        getline(cin >> ws, carrera);

        cout << "Ingrese total de materias aprobadas: ";
        while (!(cin >> materias) || materias < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero positivo: ";
        }

        cout << "Ingrese promedio general: ";
        while (!(cin >> promedio) || promedio < 0 || promedio > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un valor entre 0 y 10: ";
        }

        colaSolicitudes.encolar(Solicitud(nombre, carrera, materias, promedio));
        cout << "Solicitud registrada exitosamente.\n";
    }

    void elaborarConstancia() {
        if (colaSolicitudes.estaVacia()) {
            cout << "No hay solicitudes pendientes.\n";
            return;
        }

        Solicitud solicitud = colaSolicitudes.desencolar();

        cout << "\n=== CONSTANCIA ===\n";
        cout << "Alumno: " << solicitud.getNombreAlumno() << "\n";
        cout << "Carrera: " << solicitud.getNombreCarrera() << "\n";
        cout << "Materias aprobadas: " << solicitud.getTotalMateriasAprobadas() << "\n";
        cout << "Promedio general: " << solicitud.getPromedioGeneral() << "\n";
        cout << "=================\n\n";
    }

    void buscarSolicitud() {
        if (colaSolicitudes.estaVacia()) {
            cout << "No hay solicitudes registradas.\n";
            return;
        }

        string nombre;
        cout << "Ingrese nombre del alumno a buscar: ";
        getline(cin >> ws, nombre);


        int posLineal = colaSolicitudes.buscarLineal(nombre);

        if (posLineal != -1) {
            cout << "Hay " << posLineal
                 << " solicitudes antes de la de " << nombre << ".\n";
        } else {
            cout << "No se encontro la solicitud. Debe darla de alta.\n";
        }


        vector<Solicitud> solicitudes;
        Cola<Solicitud> copia = colaSolicitudes;
        while (!copia.estaVacia()) {
            solicitudes.push_back(copia.desencolar());
        }
        sort(solicitudes.begin(), solicitudes.end());

        int posBinaria = busquedaBinaria(solicitudes, nombre);
        if (posBinaria != -1) {
            cout << "(Busqueda binaria) La solicitud existe en el sistema.\n";
        } else {
            cout << "(Busqueda binaria) La solicitud no fue encontrada.\n";
        }
    }
};

void mostrarMenu() {
    cout << "\nSistema de Constancias Escolares\n";
    cout << "1. Dar de alta solicitud\n";
    cout << "2. Elaborar constancia\n";
    cout << "3. Buscar solicitud\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    SistemaConstancias sistema;
    int opcion;

    do {
        mostrarMenu();
        while (!(cin >> opcion) || opcion < 1 || opcion > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion no válida. Intente nuevamente: ";
        }

        switch(opcion) {
            case 1:
                sistema.altaSolicitud();
                break;
            case 2:
                sistema.elaborarConstancia();
                break;
            case 3:
                sistema.buscarSolicitud();
                break;
            case 4:
                cout << "Saliendo del sistema...\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
