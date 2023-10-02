#include <iostream>
#include <string>
using namespace std;

struct NodoArbol {
    int valor;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
    NodoArbol(int val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
};

NodoArbol* insertar(NodoArbol* raiz, int val) {
    if (raiz == nullptr) {
        return new NodoArbol(val);
    }

    if (val < raiz->valor) {
        raiz->izquierdo = insertar(raiz->izquierdo, val);
    } else if (val > raiz->valor) {
        raiz->derecho = insertar(raiz->derecho, val);
    }

    return raiz;
}

bool buscar(NodoArbol* raiz, int val) {
    if (raiz == nullptr) {
        return false;
    }

    if (val == raiz->valor) {
        return true;
    } else if (val < raiz->valor) {
        return buscar(raiz->izquierdo, val);
    } else {
        return buscar(raiz->derecho, val);
    }
}

NodoArbol* encontrarMinimo(NodoArbol* raiz) {
    while (raiz->izquierdo != nullptr) {
        raiz = raiz->izquierdo;
    }
    return raiz;
}

NodoArbol* eliminar(NodoArbol* raiz, int val) {
    if (raiz == nullptr) {
        return raiz;
    }

    if (val < raiz->valor) {
        raiz->izquierdo = eliminar(raiz->izquierdo, val);
    } else if (val > raiz->valor) {
        raiz->derecho = eliminar(raiz->derecho, val);
    } else {
        if (raiz->izquierdo == nullptr) {
            NodoArbol* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            NodoArbol* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }

        NodoArbol* temp = encontrarMinimo(raiz->derecho);
        raiz->valor = temp->valor;
        raiz->derecho = eliminar(raiz->derecho, temp->valor);
    }

    return raiz;
}

void imprimirEnOrden(NodoArbol* raiz) {
    if (raiz != nullptr) {
        imprimirEnOrden(raiz->izquierdo);
        cout << raiz->valor << " ";
        imprimirEnOrden(raiz->derecho);
    }
}

void imprimirPreOrden(NodoArbol* raiz) {
    if (raiz != nullptr) {
        cout << raiz->valor << " ";
        imprimirPreOrden(raiz->izquierdo);
        imprimirPreOrden(raiz->derecho);
    }
}

void imprimirPostOrden(NodoArbol* raiz) {
    if (raiz != nullptr) {
        imprimirPostOrden(raiz->izquierdo);
        imprimirPostOrden(raiz->derecho);
        cout << raiz->valor << " ";
    }
}

int calcularPeso(NodoArbol* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    return 1 + calcularPeso(raiz->izquierdo) + calcularPeso(raiz->derecho);
}
void encontrarRamaMayorPeso(NodoArbol* raiz, int& mayorPeso, int& pesoActual, string& rama) {
    if (raiz == nullptr) {
        return;
    }
    
    pesoActual += 1;
    if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
        if (pesoActual > mayorPeso) {
            mayorPeso = pesoActual;
            rama = "";
            NodoArbol* temp = raiz;
            while (temp != nullptr) {
                rama = to_string(temp->valor) + " " + rama;
                temp = (temp == raiz->izquierdo) ? raiz->derecho : raiz->izquierdo;
            }
        }
    }
    
    encontrarRamaMayorPeso(raiz->izquierdo, mayorPeso, pesoActual, rama);
    encontrarRamaMayorPeso(raiz->derecho, mayorPeso, pesoActual, rama);
    
    pesoActual -= 1;
}

// Función para imprimir el árbol de manera vertical
void imprimirVertical(NodoArbol* raiz, string espaciado) {
    if (raiz == nullptr) {
        return;
    }
    
    string espacioAdicional = "   ";

    imprimirVertical(raiz->derecho, espaciado + espacioAdicional);
    cout << espaciado << raiz->valor << endl;
    imprimirVertical(raiz->izquierdo, espaciado + espacioAdicional);
}

int main() {
    NodoArbol* raiz = nullptr;
    int cantidadValores;

    cout << "Ingrese la cantidad de valores que desea insertar en el arbol: ";
    cin >> cantidadValores;

    for (int i = 0; i < cantidadValores; i++) {
        int valorInsertar;
        cout << "Ingrese el valor " << i + 1 << ": ";
        cin >> valorInsertar;
        raiz = insertar(raiz, valorInsertar);
    }

    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Buscar un valor" << endl;
        cout << "2. Eliminar un valor" << endl;
        cout << "3. Mostrar el árbol" << endl;
        cout << "4. Mostrar peso del árbol" << endl;
        cout << "5. Encontrar rama con mayor peso" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                int valorBuscar;
                cout << "Ingrese el valor a buscar: ";
                cin >> valorBuscar;
                if (buscar(raiz, valorBuscar)) {
                    cout << "El valor " << valorBuscar << " está en el arbol." << endl;
                } else {
                    cout << "El valor " << valorBuscar << " no está en el arbol." << endl;
                }
                break;
            case 2:
                int valorEliminar;
                cout << "Ingrese el valor a eliminar: ";
                cin >> valorEliminar;
                raiz = eliminar(raiz, valorEliminar);
                break;
            case 3:
                cout << "Árbol:" << endl;
                imprimirVertical(raiz, "");
                break;
            case 4:
                cout << "Peso del árbol: " << calcularPeso(raiz) << endl;
                break;
            case 5:
                int mayorPeso = 0;
                int pesoActual = 0;
                string ramaMayorPeso;
                encontrarRamaMayorPeso(raiz, mayorPeso, pesoActual, ramaMayorPeso);
                if (mayorPeso > 0) {
                    cout << "Rama con mayor peso: " << ramaMayorPeso << " (Peso: " << mayorPeso << ")" << endl;
                } else {
                    cout << "El árbol está vacío." << endl;
                }
                break;
        }
    } while (opcion != 6);

    return 0;
}