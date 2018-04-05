#include "grman/grman.h"
#include <iostream>
#include "menu.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"


int main()
{

    std::vector<int> c;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    ///Declaration du menu
    Menu menu;

    /// Un graphe à charger depuis un fichier choisi
    Graph g;
    g.make_example();


    ///Gestion des menus
    do{
    menu.affiche_principal();
    menu.gestion_menu2(g);



    ///Lancer la boucle de jeu (intéraction du graphe) si le choix du joueur=2
    if(menu.getChoix()==2)
    {
        /// Vous gardez la main sur la "boucle de jeu"
        /// ( contrairement à des frameworks plus avancés )
        while ( !key[KEY_ESC] )
        {

            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();


        }
        c=g.uneComposanteFortementConnexe();

        ///Retour au menu principal si on quitte le jeu et faire sauvegarde du graphe
        menu.setChoix(0);


    }

    } while(menu.getChoix()==0);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


