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

    charger_fichier("Fichier.txt");


    /// Les sommets doivent être définis avant les arcs
    ///int pic_idx,  int population, int x, int y, int besoin, int apport, int periode

}

void Graph::charger_fichier(std::string nomfichier)
{
    std::cout << nomfichier << std::endl;
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
        /*for(int j=0; j<m_nbaretes; j++)
        {
            fp >> idx_arete >> id_vert1 >> id_vert2 >> weight;
            ///creation des aretes
            add_interfaced_edge(idx_arete, id_vert1, id_vert2, weight);
            std::cout << "idx_arete: " << idx_arete
                      << " id_vert1: " << id_vert1
                      << " id_vert_2: " << id_vert2
                      << " weight: " << weight << std::endl;
        }
        */


    fp.close();
    }
    else
        std::cout << "Erreur d'ouverture";


        ///CECI EST UNE MATRICE POUR TESTER, ATTENDRE LE CHARGEMENT DE CYNTHIA
        ///Dimensions de la matrice de taille m_ordre
        m_matAdj.resize(m_ordre);
    for(int i=0;i<m_matAdj.size();i++)
    {
        m_matAdj[i].resize(m_ordre);
    }

    for(int i=0;i<m_ordre;i++)
    {
        for(int j=0;j<m_ordre;j++)
            {
            m_matAdj[i][j]=0;
            }
    }

    m_matAdj[m_vertices[0].m_indice][m_vertices[1].m_indice]=1;
    m_matAdj[m_vertices[1].m_indice][m_vertices[2].m_indice]=1;
    m_matAdj[m_vertices[1].m_indice][m_vertices[3].m_indice]=1;
    m_matAdj[m_vertices[2].m_indice][m_vertices[3].m_indice]=1;

    //m_matAdj[m_vertices[1].m_indice][m_vertices[0].m_indice]=1;
    //m_matAdj[m_vertices[2].m_indice][m_vertices[1].m_indice]=1;
   // m_matAdj[m_vertices[3].m_indice][m_vertices[2].m_indice]=1;



}


/*void Graph::sauver_fichier(std::string nomfichier)
{
    std::string const fp1(nomfichier);
    std::ofstream ofs(fp1.c_str());

    /// Parcours la "liste" des arêtes std::map<int, Edge> m_edges;

    /// Parcours la liste des sommets std::map<int, Vertex> m_vertices;
    if(ofs)
    {
        ///Ecrire l'ordre et le nb d'arete
        ///
        ///Ecrire les valeurs de chaque arete

        ///Ecrire les valeurs de chaque sommet

        ///utiliser vertex interface
//            fp >> idx_sommet >> population >> x >> y >> besoin >> apport >> periode >> pic_name;
//    std::cout << VertexInterface(0, Coords get_pos(), "clown1.jpg"); ///afficher les coordonnes du sommet

        for(const auto &it : m_vertices)
        {
            ofs <<it.second.m_idx << " "<<
            it.second.m_population << " " <<
            it.second.m_posx<<" "<<
            it.second.m_posy<<" "<<
            it.second.m_besoin << " " <<
            it.second.m_apport << " " <<
            it.second.m_periode<< " " <<
            it.second.m_interface->m_img.get_pic_name()<<std::endl;
            std::cout << "idx: " << it.second.m_idx <<
            " population: " << it.second.m_population <<
            " position en x: "<<it.second.m_posx<<
            " position en y: "<<it.second.m_posy<<
            " besoin: " <<it.second.m_besoin <<
            " apport: " <<it.second.m_apport <<
            " periode: " <<it.second.m_periode<<
            " nom image: " << it.second.m_interface->m_img.get_pic_name() <<std::endl;
            //la position de x: "<<(it.second).m_interface->m_top_box.get_posx()<<std::endl;

        }
        ofs.close();
    }
    else
        std::cout << "Erreur d'ouverture";

}
*/
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
void Graph::add_interfaced_vertex(int idx, int population, int &x, int &y, int pic_idx,  int besoin, int apport, std::string pic_name, int periode)
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
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
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


std::vector<int> Graph::uneComposanteFortementConnexe()
{
    //Les composantes connexes, une partant du sommet initial (c1) et une arrivant au sommet initial (c2)
    //un numéro de sommet vaut 1 si connexe, 0 sinon
    std::vector<int> c1;
    std::vector<int> c2;
    int s=m_vertices[0].m_indice; //numero du sommet initial

    std::vector<int> c; //la composante fortement connexe
    std::vector<bool> estMarque1; //tableau indiquant si les sommets sotn marqués ou non
    std::vector<bool> estMarque2; //tableau indiquant si les sommets sotn marqués ou non
    int x,y; //numéros de sommets intermédiaires des composantes fortement connexes
    bool ajoute1=true; //booléen indiquant si une nouvelle composante connexe est ajoutée
    bool ajoute2=true;

    //Initialisation des tableaux des composantes connexes et estMarque de taille m_ordre à 0 et faux
    for(int i=0; i<m_ordre;i++)
    {
        c1.push_back(0);
        c2.push_back(0);
        c.push_back(0);
        estMarque1.push_back(false);
        estMarque2.push_back(false);

    }

    //Le sommet initial est connexe
    c1[s]=1;
    c2[s]=1;

    //Recherche des composantes connexes partant de s à ajouter dans c1

    //Tant qu'il y a une composante connexe...
    while(ajoute1)
    {
        ajoute1=false;

        //Pour tous les sommets x non marqués et connectés à partir de s
        //marquer les sommets x et connecter les sommets non marqués y adjacents à x
        for(x=0;x<m_ordre;x++)
        {
            //Si le sommet x n'est pas marqué et connexe...
            if(!estMarque1[x] && c1[x])
            {
                //Le marquer
                estMarque1[x]=true;

                //Parcourir ses voisins, s'ils sont adjacents et non marqués, les connecter au sommet x (c1[y]=1)
                for(y=0;y<m_ordre;y++)
                {
                    if(m_matAdj[x][y] && !estMarque1[y])
                    {
                        c1[y]=1;
                        ajoute1=true;
                    }
                }
            }
        }

    }

    //Recherche des composantes connexes dans le sens inverse(arcs arrivant au sommet s)
    while(ajoute2)
    {
        ajoute2=false;

        //Pour tous les sommets x non marqués et connectés à s à partir de la fin
        //marquer les sommets x et connecter les sommets non marqués y adjacents à x
        for(y=0;y<m_ordre;y++)
        {
            //Si le sommet x n'est pas marqué et connexe...
            if(!estMarque2[y] && c2[y])
            {
                //Le marquer
                estMarque2[y]=true;

                //Parcourir ses voisins, s'ils sont adjacents et non marqués, les connecter au sommet x (c1[y]=1)
                for(x=0;x<m_ordre;x++)
                {
                    if(m_matAdj[x][y] && !estMarque2[x])
                    {
                        c2[x]=1;
                        ajoute2=true;
                    }
                }
            }

        }
    }

    //Composante fortement connexe c= intersection entre c1 et c2
    for(int i=0;i<m_ordre;i++)
        std::cout<<"c1[i]="<<c1[i]<<" ";

        std::cout<<std::endl;
    for(int i=0;i<m_ordre;i++)
        std::cout<<"c2[i]="<<c2[i]<<" ";


    std::cout<<"Voici une compo fortement connexe du graphe:"<<std::endl;
    for(int i=0; i<m_ordre;i++)
    {
        c[i]=c1[i] & c2[i];
        std::cout<<"sommet"<<i<<"="<<c[i]<<std::endl;

    }

    return c;

}

void Graph::lesComposantesFortementConnexes()
{
    std::vector<std::vector<int>> c; //la tableau qui contient toutes les composantes connexes du graphe
    std::vector<bool> estMarque; //tableau indiquant si les sommets sont marqués ou non
    int x,y;

    //initialisation des tableaux



}


