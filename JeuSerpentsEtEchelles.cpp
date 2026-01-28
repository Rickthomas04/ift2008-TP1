/////////////////////////////////////////////////////////////////////////////
//Fichier JeuSerpentsEtEchelles.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file JeuSerpentsEtEchelles.cpp
 * \brief Ce fichier contient une implémentation de la classe JeuSerpentsEtEchelles
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

#include "JeuSerpentsEtEchelles.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{
    /**
     * \brief constructeur de la classe du jeu de serpent et échelle
     */
    JeuSerpentsEtEchelles::JeuSerpentsEtEchelles() {}

    /**
     * \brief fonction qui effectue tous les tours d'un jeu de serpent et échelle
     * \param[in] maximumDeTours le nombre maximum de tours que l'on peut effectuer dans le jeu
     * \return le résultat du jeu
     */
    Resultat JeuSerpentsEtEchelles::jouer(unsigned int maximumDeTours)
    {
        int posCouleur = 1;
        // boucle qui effectue les tours
        for (unsigned int i = 1; i < maximumDeTours; i++)
        {
            unsigned int nbrJoueurs = m_joueurs.taille();
            // Impossible de déterminer un gagnant s'il n'y a aucun joueur, aucune case ou aucune couleurs à choisir
            if (m_choix.estVide()) return Resultat(maximumDeTours);
            if (m_cases.estVide()) return Resultat(maximumDeTours);
            if (m_joueurs.taille() == 0) return Resultat(maximumDeTours);
            // boucle qui effectue le tour d'un seul joueur
            for (unsigned int j = 1; j <= nbrJoueurs; j++)
            {
                Joueur joueur = m_joueurs.defiler();
                Case::Couleur couleur = m_choix.element(posCouleur);
                posCouleur++;
                if (posCouleur > m_choix.taille()) posCouleur = 1; // on revient au début de la liste de couleur
                // si la prochaine case de même couleur existe, on avance le joueur à celle-ci
                if (joueur.position.existeCaseSuivante(couleur))
                {
                   joueur.position.caseSuivante(couleur);
                   if (joueur.position.caseCourante().decoration == 2) // si le joueur tombe sur une échelle
                   {
                       couleur = m_choix.element(posCouleur); // on repige une nouvelle couleur
                       posCouleur++;
                       if (posCouleur > m_choix.taille()) posCouleur = 1; // on revient au début de la liste de couleur
                       if (joueur.position.existeCaseSuivante(couleur)) joueur.position.caseSuivante(couleur); // on fait avancer le joueur
                   }
                   else if (joueur.position.caseCourante().decoration == 1) // si le joueur tombe sur un serpent
                   {
                       couleur = m_choix.element(posCouleur); // on repige une nouvelle couleur
                       posCouleur++;
                       if (posCouleur > m_choix.taille()) posCouleur = 1; // on revient au début de la liste de couleur
                       if (joueur.position.existeCasePrecedente(couleur)) joueur.position.casePrecedente(couleur); // on fait reculer le joueur
                   }
                }
                if (joueur.position.estADerniereCase()) // si le joueur à atteint la dernière case à la fin de son tour
                {
                    m_joueurs.enfiler(joueur);
                    return Resultat(i, joueur.nom);
                }
                m_joueurs.enfiler(joueur); // on remet le joueur à la fin de la file
            }
        }
       return Resultat(maximumDeTours); // si on trouve aucun gagnant après le nombre max de tours
    }

    //Les quatre méthodes suivantes sont utilisées par le générateur jeu.
    //Normalement, vous ne devriez pas avoir besoin de les appeler.

    //Ne pas modifier cette méthode.
    /**
     * \brief efface le contenu de la liste de case, de choix de couleurs et de la file de joueur
     */
    void JeuSerpentsEtEchelles::effacer()
    {
       while ( m_cases.taille() > 0 )
          m_cases.enleverCase(1);
       while ( m_choix.taille() > 0 )
          m_choix.enleverPos(1);
       while ( m_joueurs.taille() > 0 )
          m_joueurs.defiler();
    }

    //Ne pas modifier cette méthode.
    /**
     * \brief on ajoute une case à la liste de case
     * \param[in] _case la case à ajouter
     */
    void JeuSerpentsEtEchelles::ajouterCase( Case &_case )
    {
       m_cases.ajouterCaseALaFin( _case );
    }

    //Ne pas modifier cette méthode.
    /**
     * \brief on ajoute une couleur à la liste de couleur
     * \param[in] couleur la couleur à ajouter
     */
    void JeuSerpentsEtEchelles::ajouterChoix( Case::Couleur couleur )
    {
       m_choix.ajouterFin( couleur );
    }

    //Ne pas modifier cette méthode.
    /**
     * \brief on ajoute un joueur à la file de joueur
     * \param[in] joueur le joueur à ajouter
     */
    void JeuSerpentsEtEchelles::ajouterJoueur( Joueur joueur )
    {
       m_joueurs.enfiler( joueur );
    }

    //Ne pas modifier cette méthode.
    /**
     * \brief permet de commencer à la première case du jeu
     * \return un itérateur sur la première case du jeu
     */
    ListeDeCases::Iterateur JeuSerpentsEtEchelles::premiereCase()
    {
       return m_cases.debut();
    }


    //Ne pas modifier cette fonction.
    /**
     * \brief permet un affichage formaté de la position du joueur
     * \param[in] os ostream_char utilisé pour l'affichage formaté
     * \param[in] joueur le joueur que l'on veut affiché la position
     * \return la position du joueur formaté
     */
    ostream& operator<<(ostream& os, const Joueur & joueur)
    {
       os << joueur.nom << " : " << joueur.position.positionCourante();
       return os;
    }

    //Ne pas modifier cette méthode.
    /**
     * \brief affiche le résultat d'un jeu formaté
     * \param[in] gagnant le gagnant du jeu
     */
    void JeuSerpentsEtEchelles::afficheResultats(Resultat gagnant)
    {

       if (gagnant.nom != "")
          cout << "Gagnant : " << gagnant.nom << endl;
       else
          cout << "Aucun gagnant" << endl;
       cout << "Nombre de tours realises : " << gagnant.nombreDeTours << endl;
       cout << "Position des joueurs : " << endl;
       cout << m_joueurs << endl;

       cout << "Plateau de jeu:" << endl;
       cout << m_cases << endl;

       cout << "Liste de choix:" << endl;
       cout << m_choix << endl;
    }

}
