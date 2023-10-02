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
void quicksort(Nodo* low, Nodo* high) {
    if (high != NULL && low != high && low != high->sig) {
        Nodo* pivot = partir(low, high);
        quicksort(low, pivot->ant);
        quicksort(pivot->sig, high);
    }
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

    quicksort(first, last);

    cout << "Lista ordenada: ";
    imprimir();
    cout << endl;

    return 0;
}
