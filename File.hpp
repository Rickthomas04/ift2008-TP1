/////////////////////////////////////////////////////////////////////////////
//Fichier File.hpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file File.hpp
 * \brief Ce fichier contient une implémentation générique de la classe File
 * \author IFT-2008
 * \author Alexis Roberge
 * \version 0.1
 * \date mai-juin 2024
 */

/**
 * \namespace tp1
 * \brief namespace du travail pratique 1
 */
namespace tp1
{
    /**
     * \brief constructeur par défaut de la classe template File
     */
    template<typename T>
    File<T>::File() : liste() {}

    /**
     * \brief Ajoute un élément à la fin de la file
     * \param[in] element l'élément que l'on veut ajouter à la file
     */
    template<typename T>
    void File<T>::enfiler ( const T& element )
    {
        liste.ajouterFin(element);
    }

    /**
     * \brief Enlève l'élément qui se trouve au début de la file
     * \return l'élément de type T qui se trouvait au début de la file
     * \exception logic_error si la liste est vide
     */
    template<typename T>
    T File<T>::defiler ()
    {
        if (liste.estVide())
        {
            throw std::logic_error("defiler:On ne peut pas defiler une liste vide");
        }
        T valeur = liste.element(1);
        liste.enleverPos(1);
        return valeur;
    }

    /**
     * \brief Donne la taille de la file
     * \return unsigned int qui représente la taille de la file
     */
    template<typename T>
    unsigned int File<T>::taille ()
    {
       return liste.taille();
    }

    //Ne touchez pas à cette fonction.
    /**
     * \brief permet un affichage formatée de la liste
     * \param[in] os ostream_char qui sera utilisé pour l'affichage
     * \param[in] file la file qu'on veut afficher
     * \return ostream_char qui contient les informations de la file formatée
     */
    template< typename T >
    std::ostream& operator<<(std::ostream& os, const File<T> & file)
    {
       os << file.liste;
       return os;
    }

}
