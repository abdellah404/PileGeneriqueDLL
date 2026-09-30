#include <iostream>
#include "../dll/PileDLL.hpp"

int main() {

    std::cout << "=== Test DLL : Pile Tableau ===\n";

    void* tableau = pileTableauCreer();

    pileTableauPush(tableau, 10);
    pileTableauPush(tableau, 20);
    pileTableauPush(tableau, 30);

    std::cout << "Pop : "
              << pileTableauPop(tableau)
              << '\n';

    std::cout << "Pop : "
              << pileTableauPop(tableau)
              << '\n';

    pileTableauDetruire(tableau);


    std::cout << "\n=== Test DLL : Pile Liste ===\n";

    void* liste = pileListeCreer();

    pileListePush(liste, 10);
    pileListePush(liste, 20);
    pileListePush(liste, 30);

    std::cout << "Pop : "
              << pileListePop(liste)
              << '\n';

    std::cout << "Pop : "
              << pileListePop(liste)
              << '\n';

    pileListeDetruire(liste);

    return 0;
}