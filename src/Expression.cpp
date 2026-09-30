#include "../include/Expression.hpp"
#include "../include/PileTableau.hpp"
#include "../include/PileListe.hpp"

#include <cctype>

bool estOperateur(char c) {
    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/';
}

template <class Pile>
bool verifierExpression(const std::string& expression) {

    Pile pile;

    bool attendOperande = true;
    bool contientElement = false;

    for (std::size_t i = 0; i < expression.size(); ++i) {

        char c = expression[i];

        // Ignorer les espaces
        if (std::isspace(static_cast<unsigned char>(c))) {
            continue;
        }

        /*
         * Un nombre ou un identificateur est considéré
         * comme un opérande.
         */
        if (std::isalnum(static_cast<unsigned char>(c)) ||
            c == '_' || c == '.') {

            if (!attendOperande) {
                return false;
            }

            contientElement = true;

            /*
             * Consommer tout l'opérande.
             * Exemple : variable12 ou 123.45
             */
            while (i + 1 < expression.size()) {

                char suivant = expression[i + 1];

                if (std::isalnum(static_cast<unsigned char>(suivant)) ||
                    suivant == '_' || suivant == '.') {

                    ++i;
                }
                else {
                    break;
                }
            }

            attendOperande = false;
        }

        /*
         * Parenthèse ouvrante :
         * elle est autorisée lorsqu'on attend un opérande.
         */
        else if (c == '(') {

            if (!attendOperande) {
                return false;
            }

            pile.push(c);

            attendOperande = true;
        }

        /*
         * Parenthèse fermante :
         * il faut avoir un opérande avant elle
         * et une parenthèse ouvrante dans la pile.
         */
        else if (c == ')') {

            if (attendOperande || pile.isEmpty()) {
                return false;
            }

            pile.pop();

            attendOperande = false;
        }

        /*
         * Opérateur :
         * il doit se trouver après un opérande
         * ou une parenthèse fermante.
         */
        else if (estOperateur(c)) {

            if (attendOperande) {
                return false;
            }

            attendOperande = true;
        }

        /*
         * Tout autre caractère est refusé.
         */
        else {
            return false;
        }
    }

    /*
     * Expression valide si :
     *
     * 1. elle contient au moins un élément ;
     * 2. elle ne termine pas par un opérateur ;
     * 3. toutes les parenthèses ont été fermées.
     */
    return contientElement &&
           !attendOperande &&
           pile.isEmpty();
}

bool expressionValideTableau(const std::string& expression) {

    return verifierExpression<PileTableau<char>>(expression);
}

bool expressionValideListe(const std::string& expression) {

    return verifierExpression<PileListe<char>>(expression);
}