#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* sig;
    Nodo* ant;
};

Nodo* first = nullptr;
Nodo* last = nullptr;

void insertar(int n) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = n;
    if (first == nullptr) {
        first = nuevo;
        first->sig = nullptr;
        first->ant = nullptr;
        last = first;
    }
    else {
        last->sig = nuevo;
        nuevo->sig = nullptr;
        nuevo->ant = last;
        last = nuevo;
    }
}

void imprimir() {
    Nodo* actual = first;
    while (actual != nullptr) {
        cout << actual->dato << " -> ";
        actual = actual->sig;
    }
    cout << "NULL";
}

void cambiar(Nodo* a, Nodo* b) {
    int temp = a->dato;
    a->dato = b->dato;
    b->dato = temp;
}

Nodo* partir(Nodo* low, Nodo* high) {
    int pivot = high->dato;
    Nodo* i = low->ant;

    for (Nodo* j = low; j != high; j = j->sig) {
        if (j->dato <= pivot) {
            if (i == nullptr) {
    i = low;
        } else {
    i = i->sig;
}
            cambiar(i, j);
        }
    }

    if (i == nullptr) {
    i = low;
        } else {
    i = i->sig;
}
    cambiar(i, high);
    return i;
}
int busquedaBinaria(int valor) {
    Nodo* low = first;
    Nodo* high = last;
    int position = 0;

    while (low != nullptr && high != nullptr && low != high->sig) {
        Nodo* medio = partir(low, high);
        if (medio->dato == valor) {
            return position; // Return the position when the value is found
        }
        if (medio->dato < valor) {
            low = medio->sig;
        } else {
            high = medio->ant;
        }
        position++;
    }
    return -1; // Return -1 if the value is not found
}

int main() {
    int n;
    for (int i = 0; i < 10; i++) {
        cout << "inserte un dato:";
        cin >> n;
        insertar(n);
    }

    cout << "Lista original: ";
    imprimir();
    cout << endl;

    int valorBuscado;
    cout << "Ingrese un valor a buscar: ";
    cin >> valorBuscado;

    int posicion = busquedaBinaria(valorBuscado);

    if (posicion != -1) {
        cout << "El valor " << valorBuscado << " se encontró en la posición " << posicion << " de la lista." << endl;
    } else {
        cout << "-1";
    }

    return 0;
}

