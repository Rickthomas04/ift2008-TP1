/////////////////////////////////////////////////////////////////////////////
//Fichier GenerateurAleatoireJeuSerpentsEtEchelles.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file GenerateurAleatoireJeuSerpentsEtEchelles.cpp
 * \brief Ce fichier contient une implémentation de la classe GenerateurAleatoireJeuSerpentsEtEchelles
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

#include <algorithm>
#include <sstream>
#include "GenerateurAleatoireJeuSerpentsEtEchelles.h"

using std::max;
using std::string;
using std::ostringstream;

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{
    /**
     * \brief constructeur de la classe qui permet de générer un jeu de serpent et échelle aléatoirement
     * \param initAleatoire unsigned int qui rend la création du jeu aléatoire
     */
    GenerateurAleatoireJeuSerpentsEtEchelles::GenerateurAleatoireJeuSerpentsEtEchelles(
          unsigned int initAleatoire) :
       m_compteurNomJoueurs(0), m_generateurNombresAleatoires(initAleatoire)
    {
    }

    /**
     * \brief génère un jeu de serpent et échelle
     * \param[in] jeu le jeu qu'on veut générer
     * \param[in] nombreCases le nombre de cases du jeu
     * \param[in] nombreDeChoix le nombre de choix de couleurs de notre jeu
     * \param[in] nombreDeJoueurs le nombre de joueurs de notre jeu
     */
    void GenerateurAleatoireJeuSerpentsEtEchelles::generer(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases, unsigned int nombreDeChoix, unsigned int nombreDeJoueurs)
    {
       m_compteurNomJoueurs = 0;
       jeu.effacer();
       genererCases(jeu, nombreCases);
       genererChoix(jeu, nombreDeChoix);
       genererJoueurs(jeu, nombreDeJoueurs);
    }

    /**
     * \brief génère les cases d'un jeu de serpent et échelle
     * \param[in] jeu le jeu que l'on veut générer les cases
     * \param[in] nombreCases le nombre de cases que l'on veut générer
     */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererCases(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases)
    {
       for (unsigned int compteurCases = 0; compteurCases < nombreCases; compteurCases++)
       {
          Case nouvelleCase(choisirUneCouleurAleatoirement(), choisirUneDecorationAleatoirement());
          jeu.ajouterCase(nouvelleCase);
       }
    }

    /**
     * \brief permet de choisir une couleur de case aléatoirement
     * \return la couleur choisie
     */
    Case::Couleur GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneCouleurAleatoirement()
    {
       return static_cast<Case::Couleur> (m_generateurNombresAleatoires.pige() % Case::nombreCouleurs);
    }

    /**
     * \brief permet de choisir une décoration de case aléatoirement
     * \return la décoration choisie
     */
    Case::Decoration GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneDecorationAleatoirement()
    {
       return static_cast<Case::Decoration> (m_generateurNombresAleatoires.pige()
             % Case::nombreDecorations);
    }

    /**
     * \brief génère toutes les choix de couleur pour le jeu
     * \param[in] jeu le jeu dont on veut générer les couleurs
     * \param[in] nombreChoix le nombre de choix de couleurs total que l'on veut
     */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererChoix(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreChoix)
    {
       for (unsigned int compteurChoix = 0; compteurChoix < nombreChoix; compteurChoix++)
       {
          jeu.ajouterChoix(choisirUneCouleurAleatoirement());
       }
    }

    /**
     * \brief génère tous les joueurs du jeu
     * \param[in] jeu le jeu dont on veut générer les joueurs
     * \param[in] nombreJoueurs le nombre de joueurs que l'on veut générer
     */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererJoueurs(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreJoueurs)
    {
       for (unsigned int indexJoueur = 0; indexJoueur < nombreJoueurs; indexJoueur++)
       {
          jeu.ajouterJoueur(genererUnJoueurAleatoirement(jeu.premiereCase()));
       }
    }

    /**
     * \brief génère un joueur aléatoirement
     * \param[in] it l'itérateur qui décide le nom du joueur
     * \return le joueur généré
     */
    Joueur GenerateurAleatoireJeuSerpentsEtEchelles::genererUnJoueurAleatoirement(
          ListeDeCases::Iterateur it)
    {
       return Joueur(it, choisirUnNomAleatoirement());
    }

    /**
     * \brief génère le nom d'un joueur
     * \return le nom du joueur
     */
    string GenerateurAleatoireJeuSerpentsEtEchelles::choisirUnNomAleatoirement()
    {
       m_compteurNomJoueurs++;
       ostringstream nom;
       nom << "Joueur " << m_compteurNomJoueurs;
       return nom.str();
    }

}
