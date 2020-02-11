#include "logicSimButInC.h"

/*gboolean start_event_link(GtkWidget *widget, gpointer gtk_data){
    data_t * data = (data_t *)gtk_data;
    GtkWidget *workingLayout;

    workingLayout = data->workingLayout;

    if(widget){
        widget++;
        data++;
    }

    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(link_coordinates), data);
    return TRUE;

}*/

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

void link_coordinates(data_t *data, double x, double y){

    static link_t *link =  NULL;
    static int clickCounter = 0;

//    print_parts(data);
//    printf("Position du clic:x: %lf\ty:%lf\n",x,y);
    if(clickCounter == 0){
            if (link == NULL){
                link = malloc(sizeof(link_t));
                printf("Create new link\n");
                link->next = data->link;

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
                    data->link = link;
                    link = NULL;
                    data->imgPath = NULL;
                    g_signal_connect(G_OBJECT(data->darea), "draw", G_CALLBACK(on_draw_event), NULL);
                }
    }

}

char is_free_link(data_t * data, double x, double y){
    
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

char assign_link_parts(data_t *data, link_t *link, double x, double y){
    
    component_t *component = data->component;
    int i;


    while(component != NULL){
        i = 0;
        while(i < component->number_parts){
            if((x >= component->parts[i].pos.x - 5. && x <= (component->parts[i].pos.x + 5.)) 
            && (y >= component->parts[i].pos.y - 5. && y <= (component->parts[i].pos.y + 5.))){
                if(component->parts[i].type == 'o' && link->pos_o.x == -1){
                    printf("Pos output are set\n");
                    link->pos_o.x = component->parts[i].pos.x;
                    link->pos_o.y = component->parts[i].pos.y;
                    return 1;
                }
                else if(component->parts[i].type == 'i' && link->pos_i.x == -1){
                    printf("Pos input are set\n");
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

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, link_t *link){

    if(widget)
        widget++;
  
    visual_linking(cr, link);

    return FALSE;

}

void visual_linking(cairo_t *cr, link_t *link){

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 0.5);

    cairo_move_to(cr, link->pos_i.x, link->pos_i.y);
    cairo_line_to(cr, link->pos_o.x, link->pos_o.y);
    
    cairo_stroke(cr); 

}