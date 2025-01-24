#include <iostream>
using namespace std;

class Empleado {
private:
    int ClaveEmpleado;
    string Nombre;
    string Domicilio;
    float Sueldo;
    string ReportaA;

public:
    Empleado(int clave, string nombre, string domicilio, float sueldo, string reporta)
        : ClaveEmpleado(clave), Nombre(nombre), Domicilio(domicilio), Sueldo(sueldo), ReportaA(reporta) {}

    void Imprime() {
        cout << "\nClave: " << ClaveEmpleado
             << "\nNombre: " << Nombre
             << "\nDomicilio: " << Domicilio
             << "\nSueldo: " << Sueldo
             << "\nReporta a: " << ReportaA << "\n";
    }

    void CambiaDomicilio(const string& nuevoDomicilio) {
        Domicilio = nuevoDomicilio;
    }

    void ActualizaSueldo(float porcentaje) {
        if (porcentaje > 0) {
            Sueldo += Sueldo * (porcentaje / 100);
        }
    }

    void CambiaReportaA(const string& nuevoReporta) {
        ReportaA = nuevoReporta;
    }
};

int main() {
    Empleado empleado(1, "Juan camargo", "san luis", 15000, "estefani");
    int opcion;
    string nuevoDomicilio, nuevoReporta;
    float porcentaje;

    do {
        cout << "\nMenu:\n1. Cambiar domicilio\n2. Actualizar sueldo\n3. Imprimir datos\n4. Cambiar ReportaA\n5. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << "Nuevo domicilio: ";
            getline(cin, nuevoDomicilio);
            empleado.CambiaDomicilio(nuevoDomicilio);
            break;
        case 2:
            cout << "Porcentaje de aumento: ";
            cin >> porcentaje;
            empleado.ActualizaSueldo(porcentaje);
            break;
        case 3:
            empleado.Imprime();
            break;
        case 4:
            cout << "Nuevo ReportaA: ";
            getline(cin, nuevoReporta);
            empleado.CambiaReportaA(nuevoReporta);
            break;
        case 5:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
