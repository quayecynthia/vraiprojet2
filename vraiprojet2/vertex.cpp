#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "grman/grman.h"
#include "vertex.h"
#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    //m_top_box.get_pos();
    m_top_box.set_pos(x, y); ///position de l'image
    m_top_box.set_dim(130, 100); ///taille de l'image
    m_top_box.set_moveable(); ///mouvement de l'image

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_population );
    m_slider_population.set_range(0 , 100); ///jauge de sommet de 0 à 100 à modifier
    m_slider_population.set_dim(20,80); ///dimension de la jauge
    m_slider_population.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up); ///gravité de la jauge

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_population );
    m_label_population.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);///numero du sommet de l'image
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}

///Constructeur de vertex


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_population vers le slider associé
    m_interface->m_slider_population.set_population(m_population);

    /// Copier la valeur locale de la donnée m_population vers le label sous le slider
    m_interface->m_label_population.set_message( std::to_string( (int)m_population) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_population locale
    m_population = m_interface->m_slider_population.get_population();
//    m_posx=m_interface->m_top_box.get_posx();
//    m_posy=m_interface->m_top_box.get_posy();

}

