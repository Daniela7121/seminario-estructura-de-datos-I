
#include <iostream>
#include <string>
using namespace std;

class Materia {
private:
    int clave;
    string nombre;
    string profesorTit;
    string libroTexto;

public:
    Materia(int c, const string& n, const string& p, const string& l)
        : clave(c), nombre(n), profesorTit(p), libroTexto(l) {}

    void cambiaClave(int nuevaClave) {
        clave = nuevaClave;
    }

    void cambiaProfesor(const string& nuevoProfesor) {
        profesorTit = nuevoProfesor;
    }

    void imprimir() const {
        cout << "Clave: " << clave << "\nNombre: " << nombre
             << "\nProfesor: " << profesorTit << "\nLibro de texto: " << libroTexto << "\n\n";
    }

    bool operator==(const Materia& otra) const {
        return clave == otra.clave;
    }

    bool operator!=(const Materia& otra) const {
        return !(*this == otra);
    }

    bool operator<(const Materia& otra) const {
        return clave < otra.clave;
    }

    bool operator>(const Materia& otra) const {
        return clave > otra.clave;
    }

    Materia operator+(const Materia& otra) const {
        return Materia(clave, nombre, profesorTit, otra.libroTexto);
    }

    friend ostream& operator<<(ostream& os, const Materia& mat) {
        os << "Clave: " << mat.clave << "\nNombre: " << mat.nombre
           << "\nProfesor: " << mat.profesorTit << "\nLibro de texto: " << mat.libroTexto << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Materia& mat) {
        cout << "Ingrese clave: ";
        is >> mat.clave;
        is.ignore();
        cout << "Ingrese nombre: ";
        getline(is, mat.nombre);
        cout << "Ingrese profesor titular: ";
        getline(is, mat.profesorTit);
        cout << "Ingrese libro de texto: ";
        getline(is, mat.libroTexto);
        return is;
    }
};

int main() {
    Materia Programacion(101, "Programacion", "Dr. Perez", "C++ Basico");
    Materia BasesDatos(102, "Bases de Datos", "Ing. López", "SQL Avanzado");

    int opcion, clave;
    string nuevoDato;

    do {
        cout << "\nMenu:\n1. Cambiar clave de Programacion\n2. Cambiar profesor de Bases de Datos\n3. Imprimir datos de Bases de Datos\n4. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese nueva clave: ";
                cin >> clave;
                Programacion.cambiaClave(clave);
                break;

            case 2:
                cout << "Ingrese nuevo nombre del profesor: ";
                getline(cin, nuevoDato);
                BasesDatos.cambiaProfesor(nuevoDato);
                break;

            case 3:
                cout << BasesDatos;
                break;

            case 4:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
