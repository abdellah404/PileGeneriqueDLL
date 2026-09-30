#include "PileTableau.hpp"

template <class T>
PileTableau<T>::PileTableau(int capaciteInitiale)
    : sommet(-1),
      capacite(capaciteInitiale > 0 ? capaciteInitiale : 10) {

    elements = new T[capacite];
}

template <class T>
PileTableau<T>::~PileTableau() {
    delete[] elements;
}

template <class T>
void PileTableau<T>::agrandir() {

    int nouvelleCapacite = capacite * 2;

    T* nouveauTableau = new T[nouvelleCapacite];

    for (int i = 0; i <= sommet; ++i) {
        nouveauTableau[i] = elements[i];
    }

    delete[] elements;

    elements = nouveauTableau;
    capacite = nouvelleCapacite;
}

template <class T>
void PileTableau<T>::push(const T& valeur) {

    if (sommet + 1 == capacite) {
        agrandir();
    }

    elements[++sommet] = valeur;
}

template <class T>
T PileTableau<T>::pop() {

    if (isEmpty()) {
        throw std::runtime_error("Impossible de depiler : pile vide.");
    }

    return elements[sommet--];
}

template <class T>
bool PileTableau<T>::isEmpty() const {
    return sommet == -1;
}

template <class T>
int PileTableau<T>::size() const {
    return sommet + 1;
}