#include "graph.h"



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///ajouter l'outil de chargement

//    m_top_box.add_child(m_tool_box);
//    m_tool_box.set_frame(5,5,80,80);
//    m_tool_box.set_bg_color(ROSE);
//
//    m_tool_box.add_child( m_label_chargement);
//    m_label_chargement.set_message("Chargement");
//    textprintf(screen,font,20,5,NOIR,"Chargement");

    ///ajouter l'outil de sauvegarde
    m_top_box.add_child(m_tool_box);
    m_tool_box.set_frame(5,80,80,80);
    m_tool_box.set_bg_color(BLEU);

    m_tool_box.add_child( m_label_sauvegarde);
    m_label_sauvegarde.set_message("Sauvegarde");

}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de CHARGEMENT de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600); /// le POINTEUR sur l'interface associée
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);
    std::cout << "test" << std::endl;
    charger_fichier("Fichier.txt");
    //sauver_fichier("Fichier.txt");

    /// Les sommets doivent être définis avant les arcs
    ///int pic_idx,  int population, int x, int y, int besoin, int apport, int periode

}

void Graph::charger_fichier(std::string nomfichier)
{
    std::cout << nomfichier << std::endl;
    double chiffre;
    std::vector <double> ligne;
    int idx_sommet =0;
    int idx_arete = 0;
    int population = 0;
    int x = 0;
    int y = 0;
    int pic_idx = 0;
    int besoin = 0;
    int apport = 0;
    int periode = 0;
    std::string pic_name = "";
    int id_vert1 =0;
    int id_vert2 = 0;
    double weight = 0;
    std::ifstream fp;
    fp.open(nomfichier.c_str());

    if(fp)
    {
        fp >> m_ordre; ///lecture de l'ordre
        fp >> m_nbaretes; ///lecture du nombre d'arete
        std::cout << " Le graphe est d'ordre " << m_ordre << std::endl;
        for (int i=0; i<m_ordre; i++)
        {
            fp >> idx_sommet >> population >> x >> y >> besoin >> apport >> periode >> pic_name;
            ///creation de sommets
            add_interfaced_vertex(idx_sommet, population, x, y, pic_idx, besoin, apport, pic_name, periode);
            std::cout << "idx_sommet: " << idx_sommet
                      << " population: " << population
                      << " x: " << x
                      << " y: " << y
                      << " pic_idx: " << pic_idx
                      << " besoin: " << besoin
                      << " apport: " << apport
                      << " pic_name: " << pic_name
                      << " periode: " << periode <<std::endl;
        }
        for(int j=0; j<m_nbaretes; j++)
        {
            fp >> idx_arete >> id_vert1 >> id_vert2 >> weight;
            ///creation des aretes
            add_interfaced_edge(idx_arete, id_vert1, id_vert2, weight);
            std::cout << "idx_arete: " << idx_arete
                      << " id_vert1: " << id_vert1
                      << " id_vert_2: " << id_vert2
                      << " weight: " << weight << std::endl;
        }
        ///Parcours de la matrice d'adjacence
        for(unsigned int i=0; i<m_ordre; i++)
        {
            for(unsigned int j=0; j<m_ordre; j++)
            {
                fp >> chiffre;
                ligne.push_back(chiffre);
            }
            m_matrice.push_back(ligne);
            ligne.clear();
        }

    fp.close();
    }
    else
        std::cout << "Erreur d'ouverture lors du chargement";
}
void Graph::sauver_fichier(std::string nomfichier)
{
    std::string const fp1(nomfichier);
    std::ofstream ofs(fp1.c_str());

    /// Parcours la "liste" des arêtes std::map<int, Edge> m_edges;

    /// Parcours la liste des sommets std::map<int, Vertex> m_vertices;
    if(ofs)
    {
        ///Ecrire l'ordre et le nb d'arete

        ofs<<m_ordre<<std::endl;
        ofs<<m_nbaretes<<std::endl;

        ///Ecrire les sommets
        for(std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            ofs <<it->second.m_indice << " "<<
            it->second.m_population << " " <<
            it->second.getX()<< " " <<
            it->second.getY()<< " " <<
            it->second.m_besoin << " " <<
            it->second.m_apport << " " <<
            it->second.m_periode<< " " <<
            it->second.m_interface->m_img.get_pic_name()<<std::endl;
        }

        ///Ecrire les valeurs de chaque arete
        for(std::map<int, Edge>::iterator it = m_edges.begin(); it!=m_edges.end(); it++)
        {
            ofs <<it->second.m_indice << " "<<
            it->second.m_from << " "<<
            it->second.m_to<< " "<<
            it->second.m_weight<<std::endl;
        }
      /*  ///Ecrire la matrice d'adjacence dans le fichier
        for(unsigned int i = 0; i<m_ordre; i++)
        {
            for(unsigned int j =0; j<m_ordre; j++)
            {
                if((m_edges.m_indice.find())&& (m_edges.m_indice.find(j)))//montrer la connexite
                {
                    m_matrice[i][j]=1;//it->second.m_weight;
                    ofs<<m_matrice[i][j]<<" ";
                }
                else
                    ofs<<0;
                }
            }
            std::cout<<std::endl;
        }
*/
        ofs.close();
    }
    else
        std::cout << "Erreur d'ouverture";

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, int population, int x, int y, int pic_idx,  int besoin, int apport, std::string pic_name, int periode)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(idx, population, besoin, apport, periode, vi);

}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int indice, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(indice)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at indice=" << indice << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge indice=" << indice << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[indice] = Edge(indice, weight, ei);

    ///OOOPS A RAJOUTER DANS LE CODE DE KEVIN
    ///Connecter un arc à 2 sommets
    m_edges[indice].m_from = id_vert1;
    m_edges[indice].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(indice);
    m_vertices[id_vert2].m_in.push_back(indice);
}

void Graph::composantes_connexes()
{
    for (unsigned int i = 0; i < m_edges.size(); i++)
    {
        for(unsigned int j = 0; j < m_edges.size(); j++)
        {
            if(m_vertices[i].m_indice == m_edges[j].m_from) /// m_idx joue le role de l'indice du sommet
            {
                m_vertices[i].m_in.push_back(m_edges[i].m_to); /// S1 --(A1)-> S2
                std::cout << m_edges[i].m_to << std::endl;
            }

            else if(m_vertices[i].m_population == m_edges[j].m_to)
            {
                m_vertices[i].m_out.push_back(m_edges[i].m_from);
                std::cout << m_edges[i].m_from << std::endl;
            }

        }
    }


    for(unsigned int i = 0; i < m_vertices.size(); i++)
    {
        std::cout << "le sommet " << m_vertices[i].m_population << " a pour voisins :" << std::endl;
        for(unsigned int j = 0; j < m_vertices[i].m_in.size(); j++)
        {

            std::cout << " in " << m_vertices[i].m_in[j] << " out " << m_vertices[i].m_out[j] << std::endl;

        }
    }
}
