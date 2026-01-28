/////////////////////////////////////////////////////////////////////////////
//Fichier GenerateurNombresAleatoires.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file GenerateurNombresAleatoires.cpp
 * \brief Ce fichier contient une implémentation de la classe GenerateurNombresAleatoires
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

#include "GenerateurNombresAleatoires.h"

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{
    /**
     * \brief le constructeur de la classe qui permet de générer des nombres aléatoirement
     * \param init la valeur minimale de la génération de nombre
     * \param max la valeur maximale de la génération de nombre
     */
    GenerateurNombresAleatoires::GenerateurNombresAleatoires( unsigned int init, unsigned int max ):
          m_etat( init ), m_maxPlusUn( max + 1 )
    {
    }

    /**
     * \brief génère un nouveau nombre aléatoirement
     * \return le nombre généré
     */
    int GenerateurNombresAleatoires::pige()
    {
        m_etat *= ENTROPIE;
        return m_etat % m_maxPlusUn;
    }

}
