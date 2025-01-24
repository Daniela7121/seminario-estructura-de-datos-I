#include <iostream>
#include <string>
using namespace std;

class Materia {
private:
    int Clave;
    string Nombre;
    string ProfesorTit;
    string LibroTexto;

public:
    Materia(int clave, string nombre, string profesor, string libro)
        : Clave(clave), Nombre(nombre), ProfesorTit(profesor), LibroTexto(libro) {}

    void Imprime() {
        cout << "\nClave: " << Clave
             << "\nNombre: " << Nombre
             << "\nProfesor: " << ProfesorTit
             << "\nLibro: " << LibroTexto << "\n";
    }

    void CambiaClave(int nuevaClave) {
        Clave = nuevaClave;
    }

    void CambiaProfe(const string& nuevoProfe) {
        ProfesorTit = nuevoProfe;
    }
};

int main() {
    Materia programacion(101, "Programacion", "Panfilo", "C++");
    Materia basesDatos(102, "Bases de Datos", "patroclo", "SQL Workbench");
    int opcion;
    string nuevoProfe;
    int nuevaClave;

    do {
        cout << "\nMenu:\n1. Cambiar clave de Programación\n2. Cambiar nombre del maestro de Bases de Datos\n3. Imprimir datos de Bases de Datos\n4. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << "Nueva clave para Programacion: ";
            cin >> nuevaClave;
            programacion.CambiaClave(nuevaClave);
            break;
        case 2:
            cout << "Nuevo nombre del maestro para Bases de Datos: ";
            getline(cin, nuevoProfe);
            basesDatos.CambiaProfe(nuevoProfe);
            break;
        case 3:
            basesDatos.Imprime();
            break;
        case 4:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
