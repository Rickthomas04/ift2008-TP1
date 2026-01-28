/////////////////////////////////////////////////////////////////////////////
//Fichier Case.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Case.cpp
 * \brief Ce fichier contient une implémentation de la classe Case
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

#include "Case.h"

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{
    /**
     * \brief constructeur avec paramètre de la classe Case
     * \param couleur la couleur de la case
     * \param decoration la décoration qui se trouve sur la case
     */
    Case::Case(Case::Couleur couleur, Case::Decoration decoration) : couleur(couleur), decoration(decoration) {}

    /**
     * \brief le destructeur de la classe Case
     */
    Case::~Case() {}

    //Fonction pour aider à afficher plus naturellement une case à l'écran.
    /**
     * \brief permet l'affichage formaté de la décoration d'une case
     * \param[in] decoration la décoration de la case qu'on veut afficher
     * \return la décoration de la case formaté
     */
    std::string decorationEnLettre(Case::Decoration decoration)
    {
       switch (decoration)
       {
          case Case::Serpent:
             return "S";
          case Case::Echelle:
             return "E";
          default:
             return "A";
       }
    }

    //Ne touchez pas à cette fonction.
    /**
     * \brief permet l'affichage formatée d'une case
     * \param[in] os ostream_char qui sera utilisé pour l'affichage formaté
     * \param[in] uneCase la case que l'on veut afficher
     * \return ostream_char qui contient la case formaté
     */
    std::ostream& operator<<(std::ostream& os, const Case & uneCase)
    {
       os << "(" << uneCase.couleur << "," << decorationEnLettre(uneCase.decoration) << ")";

       return os;
    }

}
