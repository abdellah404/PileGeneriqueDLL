#ifndef PILE_TABLEAU_HPP
#define PILE_TABLEAU_HPP

#include <stdexcept>

template <class T>
class PileTableau {
public:
    explicit PileTableau(int capaciteInitiale = 10);
    ~PileTableau();

    PileTableau(const PileTableau&) = delete;
    PileTableau& operator=(const PileTableau&) = delete;

    void push(const T& valeur);
    T pop();

    bool isEmpty() const;
    int size() const;

private:
    T* elements;
    int sommet;
    int capacite;

    void agrandir();
};

#include "PileTableau.tpp"

#endif