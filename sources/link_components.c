//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions pour la creation des fils.

#include "logicSimButInC.h"

void    remove_this_link(data_t *data, size_t id){
    link_t    *link, *tmp;

    link = data->link;
    if (link->id == id){
        data->link = link->next;
        destroy_link(data, link);
    }else{
        while (link->next != NULL){
            if (link->next->id == id){
                tmp = link->next;
                link->next = link->next->next;
                destroy_link(data, tmp);
            }else
                link = link->next;
        }
    }
}

link_t  *get_link_linked_to(data_t *data, size_t id){
    link_t *ptr, *good = NULL, *bad = NULL, *next = NULL;

    ptr = data->link;
    while (ptr != NULL){
        next = ptr->next;
        if (ptr->id_i == id || ptr->id_o == id){
            ptr->next = bad;
            bad = ptr;
        }else{
            ptr->next = good;
            good = ptr;
        }
        ptr = next;
    }
    data->link = good;
    return bad;
}

void    recreate_visual(data_t *data, link_t *link){
    while (link != NULL){
        visual_linking(data, link);
        link = link->next;
    }
}

void    remove_visual(data_t *data, link_t *link){
    while (link != NULL){
        gtk_widget_destroy(GTK_WIDGET(link->img));
        link = link->next;
    }
    gtk_widget_show_all(data->workingLayout);
}

void    destroy_link(data_t *data, link_t *link){
    gtk_widget_destroy(GTK_WIDGET(link->img));
    free(link);
    gtk_widget_show_all(data->workingLayout);
}

void    remove_link_linked_to(data_t *data, size_t id){
    link_t *ptr, *good = NULL, *bad = NULL, *next = NULL;

    ptr = data->link;
    while (ptr != NULL){
        next = ptr->next;
        if (ptr->id_i == id || ptr->id_o == id){
            ptr->next = bad;
            bad = ptr;
        }else{
            ptr->next = good;
            good = ptr;
        }
        ptr = next;
    }
    data->link = bad;
    clear_link(data);
    data->link = good;
}

void    clear_link(data_t *data){
    link_t  *link;

    while (data->link != NULL){
        link = data->link->next;
        destroy_link(data, data->link);
        data->link = link;
    }
}

void    print_parts(data_t  *data){
    component_t     *component = data->component;
    int             i;


    printf("////////////////////////////////\n");
    printf("///       PRINT PARTS        ///\n");
    printf("////////////////////////////////\n");
    while (component != NULL){
        i = 0;
        while (i < component->number_parts){
            printf("x: %lf\ty:%lf\n", component->parts[i].pos.x, component->parts[i].pos.y);
            i++;
        }
        component = component->next;
    }
}

void    reset_link_coordinates(GtkWidget * comp, data_t *data){
    if (comp)
        comp++;
    link_coordinates(data, -1., -1.);
    data->imgPath = NULL;
}

void    link_coordinates(data_t *data, double x, double y){

    static link_t *link =  NULL;
    static int clickCounter = 0;

//    print_parts(data);
//    printf("Position du clic:x: %lf\ty:%lf\n",x,y);
    if (x == -1.){
        if (link != NULL)
            free(link);
        link = NULL;
        clickCounter = 0;
    }else{
        if(clickCounter == 0){
                if (link == NULL){
                    link = malloc(sizeof(link_t));
                    //printf("Create new link\n");
                    

                    link->pos_i.x = -1;
                    link->pos_o.x = -1;
                }

                if(is_free_link(data, x, y))
                    if(assign_link_parts(data, link, x, y))
                        clickCounter++;
        }else if(clickCounter == 1){
                if(is_free_link(data, x, y))
                    if(assign_link_parts(data, link, x, y)){
                        clickCounter = 0;
                        link->id = new_component_id(0);
                        link->next = NULL;
                        add_action(data, "ADD", NULL, link);
                        link->next = data->link;
                        data->link = link;
                        visual_linking(data, link);
                        link = NULL;
                    }
        }
    }
}

char    is_free_link(data_t * data, double x, double y){
    
    link_t *link = data->link;

    while(link != NULL){
        if(x == link->pos_o.x && y == link->pos_o.y){
            return 0;
        }
        else if(x == link->pos_i.x && y == link->pos_i.y)
            return 1;

        link = link->next;
    }
    return 1;
}

char    assign_link_parts(data_t *data, link_t *link, double x, double y){
    
    component_t *component = data->component;
    int i;


    while(component != NULL){
        i = 0;
        while(i < component->number_parts){
            if((x >= component->parts[i].pos.x - 5. && x <= (component->parts[i].pos.x + 5.)) 
            && (y >= component->parts[i].pos.y - 5. && y <= (component->parts[i].pos.y + 5.))){
                if(component->parts[i].type == 'o' && link->pos_o.x == -1){
                    //printf("Pos output are set\n");
                    link->id_o = component->id;
                    link->pos_o.x = component->parts[i].pos.x;
                    link->pos_o.y = component->parts[i].pos.y;
                    return 1;
                }
                else if(component->parts[i].type == 'i' && link->pos_i.x == -1){
                    //printf("Pos input are set\n");
                    link->id_i = component->id;
                    link->pos_i.x = component->parts[i].pos.x;
                    link->pos_i.y = component->parts[i].pos.y;
                    return 1;
                }
            }
            i++;
        }
        component = component->next;
    }
    return 0;
}

void    create_img_from_link(link_t *link){
    double  x,y;

    x = fabs(link->pos_o.x - link->pos_i.x);
    y = fabs(link->pos_o.y - link->pos_i.y);
    if (x < 10.)
        x = 10.;
    if (y < 10.)
        y = 10.;
    cairo_surface_t *drawing_area = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, (int)x, (int)y);
    cairo_t *cr = cairo_create(drawing_area);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);

    if (link->pos_i.y < link->pos_o.y){
        if (link->pos_i.x < link->pos_o.x){
            cairo_move_to(cr, 0, 0);
            cairo_line_to(cr, link->pos_o.x - link->pos_i.x, link->pos_o.y - link->pos_i.y);
        }else{
            cairo_move_to(cr, link->pos_i.x - link->pos_o.x, 0);
            cairo_line_to(cr, 0, link->pos_o.y - link->pos_i.y);
        }
    }else{
        if (link->pos_i.x < link->pos_o.x){
            cairo_move_to(cr, link->pos_o.x - link->pos_i.x, 0);
            cairo_line_to(cr, 0, link->pos_i.y - link->pos_o.y);
        }else{
            cairo_move_to(cr, 0, 0);
            cairo_line_to(cr, link->pos_i.x - link->pos_o.x, link->pos_i.y - link->pos_o.y);
        }
    }   
    cairo_stroke(cr);
    link->img = gtk_image_new_from_surface(drawing_area);
    cairo_surface_destroy(drawing_area);
}

void    visual_linking(data_t *data, link_t *link){
    double  x,y;

    y = link->pos_i.y < link->pos_o.y?link->pos_i.y:link->pos_o.y;
    x = link->pos_i.x < link->pos_o.x?link->pos_i.x:link->pos_o.x;
    create_img_from_link(link);
    gtk_layout_put(GTK_LAYOUT(data->workingLayout), link->img, x, y);
    gtk_widget_show_all(data->workingLayout);
}