#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

#include "../dll/PileDLL.hpp"

using Clock = std::chrono::steady_clock;


// =====================================================
// Benchmark Tableau
// =====================================================

double benchmarkTableau(
    const char* expression,
    long long repetitions)
{
    int nombreValides = 0;

    auto debut = Clock::now();

    for (long long i = 0; i < repetitions; ++i)
    {
        nombreValides +=
            expressionValideTableau(expression);
    }

    auto fin = Clock::now();

   
    if (nombreValides != repetitions)
    {
        std::cerr << "Erreur validation Tableau\n";
    }

    return std::chrono::duration<double, std::milli>(
        fin - debut
    ).count();
}


// =====================================================
// Benchmark Liste
// =====================================================

double benchmarkListe(
    const char* expression,
    long long repetitions)
{
    int nombreValides = 0;

    auto debut = Clock::now();

    for (long long i = 0; i < repetitions; ++i)
    {
        nombreValides +=
            expressionValideListe(expression);
    }

    auto fin = Clock::now();

    if (nombreValides != repetitions)
    {
        std::cerr << "Erreur validation Liste\n";
    }

    return std::chrono::duration<double, std::milli>(
        fin - debut
    ).count();
}


int main()
{
    // Expression valide utilisée pour les mesures
    const char* expression =
   "((a + b) * (c - d) + (e * f)) / (g + h)";
    const std::vector<long long> repetitions = {
        1000,
        10000,
        100000,
        1000000,
        10000000
    };

    const int nombreEssais = 5;


    // =================================================
    // Vérification fonctionnelle avant benchmark
    // =================================================

    std::cout << "Expression testee : "
              << expression << "\n";

    std::cout << "Tableau : "
              << (expressionValideTableau(expression)
                      ? "valide"
                      : "invalide")
              << "\n";

    std::cout << "Liste   : "
              << (expressionValideListe(expression)
                      ? "valide"
                      : "invalide")
              << "\n\n";


    std::cout << std::fixed
              << std::setprecision(3);

    std::cout
        << "Repetitions\t"
        << "Tableau_DLL(ms)\t"
        << "Liste_DLL(ms)\n";


    // =================================================
    // Échauffement
    // =================================================

    benchmarkTableau(expression, 1000);
    benchmarkListe(expression, 1000);


    // =================================================
    // Mesures
    // =================================================

    for (long long n : repetitions)
    {
        double totalTableau = 0.0;
        double totalListe = 0.0;

        for (int essai = 0;
             essai < nombreEssais;
             ++essai)
        {
            // Alterner l'ordre des tests
            if (essai % 2 == 0)
            {
                totalTableau +=
                    benchmarkTableau(expression, n);

                totalListe +=
                    benchmarkListe(expression, n);
            }
            else
            {
                totalListe +=
                    benchmarkListe(expression, n);

                totalTableau +=
                    benchmarkTableau(expression, n);
            }
        }

        double moyenneTableau =
            totalTableau / nombreEssais;

        double moyenneListe =
            totalListe / nombreEssais;

        std::cout
            << n << '\t'
            << moyenneTableau << '\t'
            << moyenneListe << '\n';
    }

    return 0;
}