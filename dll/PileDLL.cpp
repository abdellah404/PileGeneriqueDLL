#define PILE_DLL_EXPORTS

#include "PileDLL.hpp"
#include "../include/PileTableau.hpp"
#include "../include/PileListe.hpp"

#include <string>
#include <cctype>

// =====================================================
// API de base : Pile Tableau
// =====================================================

extern "C" {

void* pileTableauCreer()
{
    return new PileTableau<int>();
}

void pileTableauDetruire(void* pile)
{
    delete static_cast<PileTableau<int>*>(pile);
}

void pileTableauPush(void* pile, int valeur)
{
    static_cast<PileTableau<int>*>(pile)->push(valeur);
}

int pileTableauPop(void* pile)
{
    return static_cast<PileTableau<int>*>(pile)->pop();
}

int pileTableauVide(void* pile)
{
    return static_cast<PileTableau<int>*>(pile)->isEmpty() ? 1 : 0;
}


// =====================================================
// API de base : Pile Liste
// =====================================================

void* pileListeCreer()
{
    return new PileListe<int>();
}

void pileListeDetruire(void* pile)
{
    delete static_cast<PileListe<int>*>(pile);
}

void pileListePush(void* pile, int valeur)
{
    static_cast<PileListe<int>*>(pile)->push(valeur);
}

int pileListePop(void* pile)
{
    return static_cast<PileListe<int>*>(pile)->pop();
}

int pileListeVide(void* pile)
{
    return static_cast<PileListe<int>*>(pile)->isEmpty() ? 1 : 0;
}

} // extern "C"


// =====================================================
// Validation d'expressions
// Même principe que dans le rapport 1
// =====================================================

bool estOperateurDLL(char c)
{
    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/';
}


template <class Pile>
bool verifierExpressionDLL(const std::string& expression)
{
    Pile pile;

    bool attendOperande = true;
    bool contientElement = false;

    for (std::size_t i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c)))
            continue;

        // -----------------------------
        // Opérande
        // -----------------------------
        if (std::isalnum(static_cast<unsigned char>(c)) ||
            c == '_' ||
            c == '.')
        {
            if (!attendOperande)
                return false;

            contientElement = true;

            while (i + 1 < expression.size())
            {
                char suivant = expression[i + 1];

                if (std::isalnum(
                        static_cast<unsigned char>(suivant)) ||
                    suivant == '_' ||
                    suivant == '.')
                {
                    ++i;
                }
                else
                {
                    break;
                }
            }

            attendOperande = false;
        }

        // -----------------------------
        // Parenthèse ouvrante
        // -----------------------------
        else if (c == '(')
        {
            if (!attendOperande)
                return false;

            pile.push(c);
            attendOperande = true;
        }

        // -----------------------------
        // Parenthèse fermante
        // -----------------------------
        else if (c == ')')
        {
            if (attendOperande || pile.isEmpty())
                return false;

            pile.pop();
            attendOperande = false;
        }

        // -----------------------------
        // Opérateur
        // -----------------------------
        else if (estOperateurDLL(c))
        {
            if (attendOperande)
                return false;

            attendOperande = true;
        }

        // Caractère invalide
        else
        {
            return false;
        }
    }

    return contientElement &&
           !attendOperande &&
           pile.isEmpty();
}


// =====================================================
// Fonctions exportées
// =====================================================

extern "C" {

int expressionValideTableau(const char* expression)
{
    if (expression == nullptr)
        return 0;

    return verifierExpressionDLL<PileTableau<char>>(
        std::string(expression)
    ) ? 1 : 0;
}


int expressionValideListe(const char* expression)
{
    if (expression == nullptr)
        return 0;

    return verifierExpressionDLL<PileListe<char>>(
        std::string(expression)
    ) ? 1 : 0;
}

}