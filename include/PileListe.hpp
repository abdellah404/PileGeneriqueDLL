#ifndef PILE_LISTE_HPP
#define PILE_LISTE_HPP

#include <stdexcept>

template <class T>
class PileListe {
public:
    PileListe();
    ~PileListe();

    PileListe(const PileListe&) = delete;
    PileListe& operator=(const PileListe&) = delete;

    void push(const T& valeur);
    T pop();

    bool isEmpty() const;
    int size() const;

private:
    struct Noeud {
        T valeur;
        Noeud* suivant;

        Noeud(const T& v, Noeud* s = nullptr)
            : valeur(v), suivant(s) {}
    };

    Noeud* sommet;
    int nombreElements;
};

#include "PileListe.tpp"

#endif