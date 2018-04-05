#include "menu.h"
#include <iostream>

//Méthode qui charge une image en sécurité
BITMAP  *Menu::charger_bitmap(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage, NULL);
    if(!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }

    return bmp;


}

Menu::Menu()
{
    m_page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(m_page);

    ///CHARGER la bitmap d'accueil
    m_accueil=charger_bitmap("accueil.bmp");
    m_menu2=charger_bitmap("menu2.bmp");
    m_choix=0;

}

Menu::~Menu()
{

}

void Menu::setChoix(int _choix)
{
    m_choix=_choix;

}

int Menu::getChoix()
{
    return m_choix;
}

void Menu::affiche_principal()
{
    ///AFFICHAGE DU MENU PRINCIPAL
    blit(m_accueil,screen,0,0,0,0,SCREEN_W,SCREEN_H);

}

void Menu::gestion_menu2(Graph g)
{
    ///Gestion du menu en fonction des choix de l'utilisateur
    while(m_choix==0)
    {
        //Affichage du 2eme menu qui affiche les différents graphes si le joueur choisit ainsi
        if((mouse_b&1)&&(mouse_x>291)&&(mouse_x<470)&&(mouse_y>230)&&(mouse_y<265))
        {
            setChoix(1);
            blit(m_menu2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(500);

            while(m_choix==1)
            {
                //Charger les différents graphes choisis par l'utiisateur
                //Graphe 1
                if((mouse_b&1)&&(mouse_x>105)&&(mouse_x<260)&&(mouse_y>250)&&(mouse_y<360))
                {
                    setChoix(2);

                }

                //Graphe2
                if((mouse_b&1)&&(mouse_x>325)&&(mouse_x<480)&&(mouse_y>250)&&(mouse_y<360))
                {
                    setChoix(2);

                }

                //Graphe 3
                if((mouse_b&1)&&(mouse_x>540)&&(mouse_x<690)&&(mouse_y>250)&&(mouse_y<360))
                {
                    setChoix(2);

                }

                //Pour faire un retour au menu prinipal
                if((mouse_b&1)&&(mouse_x>30)&&(mouse_x<90)&&(mouse_y>20)&&(mouse_y<60))
                {
                    std::cout<<"Retour"<<std::endl;
                    setChoix(0);
                    affiche_principal();

                }

            }

        }


        ///Affichage des règles/commandes
        if((mouse_b&1)&&(mouse_x>333)&&(mouse_x<435)&&(mouse_y>350)&&(mouse_y<390))
        {
             //blit(regles,screen,0,0,0,0,SCREEN_W,SCREEN_H);

             while(!keypressed())
             {
                //Pour faire un retour en arrière
                /*if((mouse_b&1)&&(mouse_x>333)&&(mouse_x<435)&&(mouse_y>350)&&(mouse_y<390))
                {
                    std::cout<<"retour"<<std::endl;
                    setChoix(0);
                    affiche_principal();
                }*/
             }

        }



        ///Quitter
        if((mouse_b&1)&&(mouse_x>230)&&(mouse_x<430)&&(mouse_y>465)&&(mouse_y<505))
        {
            exit(0);
        }
    }


}
