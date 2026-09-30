#include "PileListe.hpp"


template <class T>
PileListe<T>::PileListe()
    : sommet(nullptr), nombreElements(0) {
}

template <class T>
PileListe<T>::~PileListe() {

    while (!isEmpty()) {
        pop();
    }
}

template <class T>
void PileListe<T>::push(const T& valeur) {

    sommet = new Noeud(valeur, sommet);
    ++nombreElements;
}

template <class T>
T PileListe<T>::pop() {

    if (isEmpty()) {
        throw std::runtime_error("Impossible de depiler : pile vide.");
    }

    Noeud* ancienSommet = sommet;

    T valeur = ancienSommet->valeur;

    sommet = sommet->suivant;

    delete ancienSommet;

    --nombreElements;

    return valeur;
}
template <class T>
bool PileListe<T>::isEmpty() const {
    return sommet == nullptr;
}

template <class T>
int PileListe<T>::size() const {
    return nombreElements;
}