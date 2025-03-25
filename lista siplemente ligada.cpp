#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

// Clase SocioClub
class SocioClub {
private:
    int numeroSocio;
    char nombreSocio[50];
    char domicilio[100];
    int anoIngreso;

public:
    // Constructores
    SocioClub() : numeroSocio(0), anoIngreso(0) {
        nombreSocio[0] = '\0';
        domicilio[0] = '\0';
    }

    SocioClub(int num, const char* nom, const char* dom, int ano) : numeroSocio(num), anoIngreso(ano) {
        strncpy(nombreSocio, nom, 49);
        nombreSocio[49] = '\0';
        strncpy(domicilio, dom, 99);
        domicilio[99] = '\0';
    }

    // Operadores
    bool operator==(const SocioClub& otro) const {
        return numeroSocio == otro.numeroSocio;
    }

    bool operator<(const SocioClub& otro) const {
        return numeroSocio < otro.numeroSocio;
    }

    bool operator>(const SocioClub& otro) const {
        return numeroSocio > otro.numeroSocio;
    }

    friend ostream& operator<<(ostream& os, const SocioClub& socio) {
        os << "Número: " << socio.numeroSocio << "\nNombre: " << socio.nombreSocio
           << "\nDomicilio: " << socio.domicilio << "\nAño ingreso: " << socio.anoIngreso << "\n";
        return os;
    }

    // Métodos de acceso
    int getNumero() const { return numeroSocio; }
    const char* getNombre() const { return nombreSocio; }
    const char* getDomicilio() const { return domicilio; }
    int getAnoIngreso() const { return anoIngreso; }
};

// Nodo para la lista simplemente ligada
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& dato) : dato(dato), siguiente(nullptr) {}
};

// Lista simplemente ligada
template <typename T>
class ListaSimplementeLigada {
private:
    Nodo<T>* cabeza;
    int tam;

public:
    ListaSimplementeLigada() : cabeza(nullptr), tam(0) {}

    ~ListaSimplementeLigada() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void insertarOrdenado(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);

        if (cabeza == nullptr || dato < cabeza->dato) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr && actual->siguiente->dato < dato) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        tam++;
    }

    bool eliminar(const T& dato) {
        if (cabeza == nullptr) return false;

        if (cabeza->dato == dato) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tam--;
            return true;
        }

        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr && !(actual->siguiente->dato == dato)) {
            actual = actual->siguiente;
        }

        if (actual->siguiente != nullptr) {
            Nodo<T>* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            tam--;
            return true;
        }

        return false;
    }

    void imprimir() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << endl;
            actual = actual->siguiente;
        }
    }

    Nodo<T>* buscarPorNombreYDomicilio(const char* nombre, const char* domicilio) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (strcmp(actual->dato.getNombre(), nombre) == 0 &&
                strcmp(actual->dato.getDomicilio(), domicilio) == 0) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    int getTam() const { return tam; }

    Nodo<T>* getCabeza() const { return cabeza; }  // Agregado el getter para la cabeza
};

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función principal
int main() {
    ListaSimplementeLigada<SocioClub> listaSocios;
    int opcion;

    do {
        cout << "\nMENU DEL CLUB DEPORTIVO\n";
        cout << "1. Registrar nuevo socio\n";
        cout << "2. Dar de baja un socio\n";
        cout << "3. Generar reporte de socios\n";
        cout << "4. Buscar socio por nombre y domicilio\n";
        cout << "5. Mostrar total de socios\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: {
                int num, ano;
                char nombre[50], dom[100];

                cout << "Número de socio: ";
                cin >> num;
                limpiarBuffer();

                cout << "Nombre: ";
                cin.getline(nombre, 50);

                cout << "Domicilio: ";
                cin.getline(dom, 100);

                cout << "Año de ingreso: ";
                cin >> ano;
                limpiarBuffer();

                // Verificar si el número de socio ya existe
                bool existe = false;
                Nodo<SocioClub>* actual = listaSocios.getCabeza();
                while (actual != nullptr) {
                    if (actual->dato.getNumero() == num) {
                        existe = true;
                        break;
                    }
                    actual = actual->siguiente;
                }

                if (existe) {
                    cout << "Error: Ya existe un socio con ese número.\n";
                } else {
                    SocioClub nuevo(num, nombre, dom, ano);
                    listaSocios.insertarOrdenado(nuevo);
                    cout << "Socio registrado exitosamente.\n";
                }
                break;
            }
            case 2: {
                int num;
                cout << "Número de socio a dar de baja: ";
                cin >> num;
                limpiarBuffer();

                SocioClub temp(num, "", "", 0);
                if (listaSocios.eliminar(temp)) {
                    cout << "Socio eliminado exitosamente.\n";
                } else {
                    cout << "No se encontró el socio con ese número.\n";
                }
                break;
            }
            case 3:
                cout << "\nREPORTE DE SOCIOS:\n";
                listaSocios.imprimir();
                break;
            case 4: {
                char nombre[50], dom[100];
                cout << "Nombre a buscar: ";
                cin.getline(nombre, 50);

                cout << "Domicilio a buscar: ";
                cin.getline(dom, 100);

                Nodo<SocioClub>* encontrado = listaSocios.buscarPorNombreYDomicilio(nombre, dom);
                if (encontrado != nullptr) {
                    cout << "\nSOCIO ENCONTRADO:\n" << encontrado->dato << endl;
                } else {
                    cout << "No se encontró ningún socio con esos datos.\n";
                }
                break;
            }
            case 5:
                cout << "Total de socios registrados: " << listaSocios.getTam() << endl;
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 0);

    return 0;
}

