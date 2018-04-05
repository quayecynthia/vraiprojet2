#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <allegro.h>
#include "graph.h"

class Menu
{
private:
    //INITIALISATION DES differents bitmap d'affichage des menus
    BITMAP *m_page; //buffer d'affichage
    BITMAP *m_accueil;
    BITMAP *m_menu2;
    int m_choix; //differents etats pour les choix de l'utilisateur

public:
    //Constructeur qui initialise les attributs
    Menu();
    ~Menu();

    //Méthode qui charge une image en sécurité
    BITMAP  *charger_bitmap(char *nomImage);

    //getters et setters
    void setChoix(int _choix);
    int getChoix();

    //Affiche le menu principal
    void affiche_principal();
    void gestion_menu2(Graph g);





};

#endif // MENU_H_INCLUDED
