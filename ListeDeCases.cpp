/////////////////////////////////////////////////////////////////////////////
//Fichier ListeDeCases.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file ListeDeCases.cpp
 * \brief Ce fichier contient une implémentation de la classe ListeDeCases
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "ListeDeCases.h"

using std::string;
using std::ostringstream;
using std::out_of_range;
using std::range_error;

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{

    /**
     * \brief Constructeur de la liste de cases, crée une liste vide
     */
    ListeDeCases::ListeDeCases() : m_debut(nullptr), m_fin(nullptr), m_taille(0) {}

    /**
     * \brief destructeur de la liste de cases, s'assure d'éffacer tout le contenu de la liste avant de détruire la liste
     */
    ListeDeCases::~ListeDeCases()
    {
        Noeud* temp = m_debut;
        while (temp != nullptr)
        {
            m_debut = temp;
            temp = temp->m_suivant;
            m_debut->m_suivant = nullptr;
            m_debut->m_precedent = nullptr;
            delete m_debut;
        }
        m_debut = nullptr;
        m_fin = nullptr;
        m_taille = 0;
    }

    /**
     * \brief donne la taille de la liste de cases
     * \return la taille de la liste
     */
    int ListeDeCases::taille() const
    {
        return m_taille;
    }

    /**
     * \brief indique si la liste de cases est vide ou non
     * \return VRAI si la liste est vide, FAUX si elle n'est pas vide
     */
    bool ListeDeCases::estVide() const
    {
        return taille() == 0;
    }

    /**
     * \brief ajoute une case dans la liste de cases
     * \param[in] uneCase la case que l'on veut ajouter
     * \param[in] position la position à laquelle on veut ajouter la case
     * \exception range_error si la position donnée est invalide
     */
    void ListeDeCases::ajouterCase(const Case& uneCase, int position)
    {
        if ((position > m_taille + 1) || (position < 1))
        {
            throw std::range_error("La position de la case est invalide");
        }
        if (m_taille == 0) // si la liste était vide avant
        {
            m_debut = m_fin = new Noeud(uneCase);
        }
        else if (position == 1) // si on ajoute au début
        {
            m_debut = new Noeud(uneCase, m_debut);
            m_debut->m_suivant->m_precedent = m_debut;
        }
        else if (position == m_taille + 1) // si on ajoute à la fin
        {
            m_fin = new Noeud(uneCase, nullptr, m_fin);
            m_fin->m_precedent->m_suivant = m_fin;
        }
        else // si on ajoute à une position autre dans la liste
        {
            Noeud* noeud = noeudAt(position - 1);
            noeud = new Noeud(uneCase, noeud->m_suivant, noeud);
            noeud->m_suivant->m_precedent = noeud;
            noeud->m_precedent->m_suivant = noeud;
        }
        m_taille++; // on incrémente l'attribut de taille de la liste
    }

    /**
     * \brief on ajoute une case à la fin de la liste
     * \param[in] uneCase la case à ajouter
     */
    void ListeDeCases::ajouterCaseALaFin(const Case& uneCase)
    {
        ajouterCase(uneCase, m_taille + 1);
    }

    /**
     * \brief on enlève une case de la liste de cases
     * \param[in] position la position de la case qu'on veut enlever
     * \exception logic_error si la position donnée est invalide (n'est pas dans la liste)
     */
    void ListeDeCases::enleverCase(int position)
    {
        if ((position > taille()) || (position < 1))
        {
            throw std::logic_error("Cette position n'existe pas dans la liste");
        }
        Noeud* noeud = noeudAt(position);
        if (taille() == 1) //si on enlève le seul élément de la liste
        {
            m_debut = m_fin = nullptr;
        }
        else if (m_debut == noeud) //si on enlève l'élément du début de la liste
        {
            m_debut = m_debut->m_suivant;
            m_debut->m_precedent = nullptr;
        }
        else if (m_fin == noeud) // si on enlève le dernier élément de la liste
        {
            m_fin = m_fin->m_precedent;
            m_fin->m_suivant = nullptr;
        }
        else // si on enlève un élément à une position autre de la liste
        {
            noeud->m_suivant->m_precedent = noeud->m_precedent;
            noeud->m_precedent->m_suivant = noeud->m_suivant;
        }
        noeud->m_suivant = nullptr; // on détruit les pointeurs du noeud à enlever avant de le détruire
        noeud->m_precedent = nullptr;
        delete noeud;
        m_taille--; // on décrémente l'attribut de taille de la liste
    }

    /**
     * \brief donne la case à une position spécifique
     * \param[in] position la position que l'on veut la case
     * \return la case à la position demandée
     * \exception range_error la position donnée n'est pas valide
     */
    const Case& ListeDeCases::caseA(int position) const
    {
        if ((position > taille() || (position < 1)))
        {
            throw std::range_error("Cette position n'existe pas dans la liste");
        }
        return noeudAt(position)->m_case;
    }

    /**
     * \brief donne un pointeur sur le noeud a une position spécifique
     * \param[in] position la position du noeud voulu
     * \return un pointeur sur le noeud à la position recherchée
     * \exception range_error la position donnée n'est pas dans le domaine de la liste
     */
    ListeDeCases::Noeud* ListeDeCases::noeudAt(int position) const
    {
        if ((position > taille() || (position < 1)))
        {
            throw std::range_error("Cette position n'existe pas dans la liste");
        }
        Noeud* temp = m_debut;
        for (int i = 1; i < position; i++)
        {
            temp = temp->m_suivant;
        }
        return temp;
    }

    // Le reste du code qui utilise surtout l'itérateur est fourni.
    // Ajoutez simplement les balises Doxygen.

    /**
     * \brief donne un itérateur au début de la liste de cases
     * \return un itérateur qui pointe sur la première case de la liste
     */
    ListeDeCases::Iterateur ListeDeCases::debut() const
    {
       return Iterateur(*this);
    }

    /**
     * \brief constructeur de copie de la classe Iterateur
     * \param[in] liste la liste à copier
     */
    ListeDeCases::Iterateur::Iterateur(const ListeDeCases& liste) :
       m_liste(liste), m_courant(liste.m_debut)
    {
    }

    /**
     * \brief destructeur de la classe Iterateur
     */
    ListeDeCases::Iterateur::~Iterateur()
    {
       m_courant = 0;
    }

    /**
     * \brief donne la case du noeud pointé par l'itérateur
     * \return un pointeur sur la case
     */
    const Case& ListeDeCases::Iterateur::caseCourante() const
    {
       return m_courant->m_case;
    }

    /**
     * \brief trouve s'il existe une case après celle qui est pointé par l'itérateur
     * \return VRAI si cette case existe, FAUX s'il n'y a plus d'autres cases après
     */
    bool ListeDeCases::Iterateur::existeCaseSuivante() const
    {
       return (m_courant != 0 && m_courant->m_suivant != 0);
    }

    /**
     * \brief surcharge de l'opérateur d'incrémentation
     * \return un pointeur sur l'élément suivant
     */
    ListeDeCases::Iterateur& ListeDeCases::Iterateur::operator ++()
    {
       if (existeCaseSuivante())
       {
          m_courant = m_courant->m_suivant;
       }
       else
       {
          m_courant = 0;
          throw out_of_range("L'iterateur ne peut pas aller à une case suivante.");
       }
       return *this;
    }

    /**
     * \brief donne le prochain noeud de la même couleur
     * \param[in] couleur la couleur recherché
     * \param[in] distance la distance entre les 2 cases de même couleur
     * \return un pointeur sur le prochain noeud de même couleur
     */
    ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudSuivant(Case::Couleur couleur, int& distance) const
    {
       distance = 0;
       if (m_courant == 0)
       {
          return 0;
       }

       ListeDeCases::Noeud* suivant = m_courant->m_suivant;
       while (noeudMauvaiseCouleur(suivant, couleur))
       {
          suivant = suivant->m_suivant;
          distance++;
       }
       return suivant;
    }

    /**
     * \brief trouve si la couleur de la case du noeud est la même que celle voulue
     * \param[in] noeud le noeud dont on veut savoir la couleur
     * \param[in] couleur la couleur que l'on veut
     * \return VRAI si la couleur n'est pas la même, FAUX si la couleur est la même
     */
    bool ListeDeCases::Iterateur::noeudMauvaiseCouleur(ListeDeCases::Noeud *noeud,
          Case::Couleur couleur) const
    {
       return (noeud != 0 && noeud->m_case.couleur != couleur);
    }

    /**
     * \brief déplace l'itérateur à la case suivante de même couleur
     * \param[in] couleur la couleur que l'on cherche
     */
    void ListeDeCases::Iterateur::caseSuivante(Case::Couleur couleur)
    {
       int distance = 0;
       m_courant = noeudSuivant(couleur, distance);
       if (m_courant == 0)
       {
          ostringstream message;
          message << "L'iterateur ne peut pas aller à une case suivante de couleur " << couleur << ".";
          throw out_of_range(message.str());
       }
    }

    /**
     * \brief vérifie s'il existe une autre case de la même couleur après la case courante
     * \param[in] couleur la couleur recherchée
     * \return VRAI si cette case existe, FAUX si elle n'existe pas
     */
    bool ListeDeCases::Iterateur::existeCaseSuivante(Case::Couleur couleur) const
    {
       int distance = 0;
       return noeudSuivant(couleur, distance) != 0;
    }

    /**
     * \brief donne le noeud qui précède celui couramment pointé de même couleur
     * \param[in] couleur la couleur recherchée
     * \param[in] distance la distance entre les noeuds
     * \return un pointeur sur le noeud précédent de la même couleur
     */
    ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudPrecedent(Case::Couleur couleur, int& distance) const
    {
       distance = 0;
       if (m_courant == 0)
       {
          return 0;
       }

       ListeDeCases::Noeud* precedent = m_courant->m_precedent;
       while (noeudMauvaiseCouleur(precedent, couleur))
       {
          precedent = precedent->m_precedent;
          distance++;
       }
       return precedent;
    }

    /**
     * \brief donne la case qui précède celle courante, qui est de la même couleur
     * \param[in] couleur la couleur de case recherchée
     * \exception out_of_range si on ne peut pas atteindre cette case
     */
    void ListeDeCases::Iterateur::casePrecedente(Case::Couleur couleur)
    {
       int distance;
       m_courant = noeudPrecedent(couleur, distance);
       if (m_courant == 0)
       {
          ostringstream message;
          message << "L'iterateur ne peut pas aller à une case precedente de couleur " << couleur
                << ".";
          throw out_of_range(message.str());
       }
    }

    /**
     * \brief trouve s'il existe une case précédent celle courante de même couleur
     * \param[in] couleur la couleur recherchée
     * \return VRAI si cette case existe, FAUX si elle n'existe pas
     */
    bool ListeDeCases::Iterateur::existeCasePrecedente(Case::Couleur couleur) const
    {
       int distance = 0;
       return noeudPrecedent(couleur, distance) != 0;
    }

    /**
     * \brief donne la position courante de l'itérateur
     * \return la position courante de l'itérateur
     */
    int ListeDeCases::Iterateur::positionCourante() const
    {
       Noeud *courant = m_liste.m_debut;
       if (courant == 0)
          throw range_error("positionCourante: La liste est vide");

       int i = 1;
       while (courant != m_courant)
       {
          courant = courant->m_suivant;
          i++;
       }
       return i;
    }

    /**
     * \brief détermine si la case est la dernière de la liste
     * \return VRAI si la case est la dernière, FAUX autrement
     */
    bool ListeDeCases::Iterateur::estADerniereCase() const
    {
       return m_courant == m_liste.m_fin && m_courant != 0;
    }

    //Ne touchez surtout pas à cette fonction.
    /**
     * \brief surcharge de l'opérateur d'affichage
     * \param[in] os ostream_char utilisé pour le formatage
     * \param[in] liste la liste que l'on veut afficher l'information formaté
     * \return ostream_char qui contient la liste formaté
     */
    std::ostream& operator<<(std::ostream& os, const ListeDeCases & liste)
    {
       if (liste.estVide())
       {
          os << "Liste de cases vide";
       }
       else
       {
          ListeDeCases::Iterateur iter = liste.debut();
          while (!iter.estADerniereCase())
          {
             os << iter.caseCourante() << "; ";
             ++iter;
          }
          os << iter.caseCourante();
       }

       return os;
    }

}
