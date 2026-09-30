#ifndef PILE_DLL_HPP
#define PILE_DLL_HPP

#ifdef _WIN32
    #ifdef PILE_DLL_EXPORTS
        #define PILE_API __declspec(dllexport)
    #else
        #define PILE_API __declspec(dllimport)
    #endif
#else
    #define PILE_API
#endif

extern "C" {

PILE_API void* pileTableauCreer();
PILE_API void pileTableauDetruire(void* pile);
PILE_API void pileTableauPush(void* pile, int valeur);
PILE_API int pileTableauPop(void* pile);
PILE_API int pileTableauVide(void* pile);

PILE_API void* pileListeCreer();
PILE_API void pileListeDetruire(void* pile);
PILE_API void pileListePush(void* pile, int valeur);
PILE_API int pileListePop(void* pile);
PILE_API int pileListeVide(void* pile);

// Validation d'expressions via la DLL
PILE_API int expressionValideTableau(const char* expression);
PILE_API int expressionValideListe(const char* expression);

}

#endif