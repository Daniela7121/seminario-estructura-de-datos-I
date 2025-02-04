#include <iostream>
#include <string>
using namespace std;

class Empleado {
private:
    int claveEmpleado;
    string nombre;
    string domicilio;
    float sueldo;
    string reportaA;

public:
    Empleado(int clave, const string& nom, const string& dom, float suel, const string& rep)
        : claveEmpleado(clave), nombre(nom), domicilio(dom), sueldo(suel), reportaA(rep) {}

    void cambiaDomicilio(const string& nuevoDomicilio) {
        domicilio = nuevoDomicilio;
    }

    void cambiaReportaA(const string& nuevoReportaA) {
        reportaA = nuevoReportaA;
    }

    void actualizaSueldo(float porcentaje) {
        sueldo += sueldo * (porcentaje / 100.0);
    }

    void imprimirDatos() const {
        cout << "Clave: " << claveEmpleado << "\nNombre: " << nombre
             << "\nDomicilio: " << domicilio << "\nSueldo: " << sueldo
             << "\nReporta a: " << reportaA << "\n\n";
    }

    bool operator==(const Empleado& otro) const {
        return claveEmpleado == otro.claveEmpleado;
    }

    bool operator!=(const Empleado& otro) const {
        return !(*this == otro);
    }

    bool operator<(const Empleado& otro) const {
        return claveEmpleado < otro.claveEmpleado;
    }

    bool operator>(const Empleado& otro) const {
        return claveEmpleado > otro.claveEmpleado;
    }

    Empleado operator+(const Empleado& otro) const {
        return Empleado(claveEmpleado, nombre, domicilio, sueldo + otro.sueldo, reportaA);
    }

    friend ostream& operator<<(ostream& os, const Empleado& emp) {
        os << "Clave: " << emp.claveEmpleado << "\nNombre: " << emp.nombre
           << "\nDomicilio: " << emp.domicilio << "\nSueldo: " << emp.sueldo
           << "\nReporta a: " << emp.reportaA << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Empleado& emp) {
        cout << "Ingrese clave: ";
        is >> emp.claveEmpleado;
        is.ignore();
        cout << "Ingrese nombre: ";
        getline(is, emp.nombre);
        cout << "Ingrese domicilio: ";
        getline(is, emp.domicilio);
        cout << "Ingrese sueldo: ";
        is >> emp.sueldo;
        is.ignore();
        cout << "Ingrese reporta a: ";
        getline(is, emp.reportaA);
        return is;
    }

    int getClave() const {
        return claveEmpleado;
    }
};

int main() {
    Empleado JefePlanta(1, "Juan Perez", "Calle 123", 5000, "Director");
    Empleado JefePersonal(2, "Maria Lopez", "Avenida 456", 5500, "Gerente");

    int opcion, clave;
    float porcentaje;
    string nuevoDato;

    do {
        cout << "\nMenu:\n1. Cambiar domicilio\n2. Actualizar sueldo\n3. Imprimir datos\n4. Cambiar reporta a\n5. Salir\nOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese clave del empleado: ";
                cin >> clave;
                cin.ignore();
                cout << "Ingrese nuevo domicilio: ";
                getline(cin, nuevoDato);
                if (clave == JefePlanta.getClave()) {
                    JefePlanta.cambiaDomicilio(nuevoDato);
                } else if (clave == JefePersonal.getClave()) {
                    JefePersonal.cambiaDomicilio(nuevoDato);
                } else {
                    cout << "Clave de empleado no encontrada.\n";
                }
                break;

            case 2:
                cout << "Ingrese clave del empleado: ";
                cin >> clave;
                cout << "Ingrese porcentaje de incremento: ";
                cin >> porcentaje;
                if (clave == JefePlanta.getClave()) {
                    JefePlanta.actualizaSueldo(porcentaje);
                } else if (clave == JefePersonal.getClave()) {
                    JefePersonal.actualizaSueldo(porcentaje);
                } else {
                    cout << "Clave de empleado no encontrada.\n";
                }
                break;

            case 3:
                cout << "Ingrese clave del empleado: ";
                cin >> clave;
                if (clave == JefePlanta.getClave()) {
                    cout << JefePlanta;
                } else if (clave == JefePersonal.getClave()) {
                    cout << JefePersonal;
                } else {
                    cout << "Clave de empleado no encontrada.\n";
                }
                break;

            case 4:
                cout << "Ingrese clave del empleado: ";
                cin >> clave;
                cin.ignore();
                cout << "Ingrese nuevo nombre de la persona a quien reporta: ";
                getline(cin, nuevoDato);
                if (clave == JefePlanta.getClave()) {
                    JefePlanta.cambiaReportaA(nuevoDato);
                } else if (clave == JefePersonal.getClave()) {
                    JefePersonal.cambiaReportaA(nuevoDato);
                } else {
                    cout << "Clave de empleado no encontrada.\n";
                }
                break;

            case 5:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}
