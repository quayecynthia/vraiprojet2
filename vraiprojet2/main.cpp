#include "grman/grman.h"
#include <iostream>
#include "menu.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"


int main()
{


    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    ///Declaration du menu
    Menu menu;

    /// Un graphe � charger depuis un fichier choisi
    Graph g;
    //g.make_example();

    int mousePrev = 0, mouseAc=0;

    ///Gestion des menus
    do
    {
        menu.affiche_principal();
        menu.gestion_menu2(g);



        ///Lancer la boucle de jeu (int�raction du graphe) si le choix du joueur=2
        if(menu.getChoix()==2)
        {
            /// Vous gardez la main sur la "boucle de jeu"
            /// ( contrairement � des frameworks plus avanc�s )
            while ( !key[KEY_ESC] )
            {
                mousePrev = mouseAc;
                mouseAc = mouse_b&1;
                /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
                g.update();
                if(mouseAc && !mousePrev && (mouse_x>8)&&(mouse_x<86)&&(mouse_y>7)&&(mouse_y<74))
                    {
                        g.charger_fichier("Fichier.txt");
                        std::cout<<"Le chargement a ete effectue"<<std::endl;
                    }
                if(mouseAc && !mousePrev && (mouse_x>6)&&(mouse_x<81)&&(mouse_y>86)&&(mouse_y<161))
                    {
                        g.sauver_fichier("Fichier.txt");
                        std::cout<<"La sauvegarde a ete effectuee"<<std::endl;
                    }

                /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
            }

            ///Retour au menu principal si on quitte le jeu et faire sauvegarde du graphe
            menu.setChoix(0);


        }

    }
    while(menu.getChoix()==0);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


