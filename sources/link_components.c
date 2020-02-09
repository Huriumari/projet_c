#include "logicSimButInC.h"

gboolean start_event_link(GtkWidget *widget, gpointer gtk_data){
    data_t * data = (data_t *)gtk_data;
    GtkWidget *workingLayout;

    workingLayout = data->workingLayout;

    if(widget){
        widget++;
        data++;
    }

    printf("ok\n");
    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(link_coordinates), data);
    return TRUE;

}

void link_coordinates(GtkWidget *widget, GdkEventButton *event, data_t *data){

    static link_t *link;
    static double keep_x, keep_y;
    static int clickCounter = 0;
    
    if(widget)
        widget++;

    if(clickCounter == 0){
            keep_x = event->x;
            keep_y = event->y;
            link = malloc(sizeof(link_t));
            link->next = data->link;

            if(is_free_link(data, event->x, event->y))
                if(assign_link_parts(data, event->x, event->y))
                    clickCounter++;
    }
    else if(clickCounter == 1){
            if(is_free_link(data, event->x, event->y))
                if(event->x != keep_x && event->y != keep_y)
                    if(assign_link_parts(data, event->x, event->y)){
                        clickCounter = 0;
                        link->id = new_component_id(0);
                        data->link = link;
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

    return 0;
}

char assign_link_parts(data_t *data, double x, double y){
    
    component_t *component = data->component;
    link_t *link = data->link;
    int i = 0;

    while(component != NULL){
        while(i < component->number_parts){
            if(x == component->parts[i].pos.x && y == component->parts[i].pos.y){
                if(component->parts[i].type == 'o'){
                    link->pos_o.x = x;
                    link->pos_o.y = y;
                    return 1;
                }
                else if(component->parts[i].type == 'i'){
                    link->pos_i.x = x;
                    link->pos_i.y = y;
                    return 1;
                }
                i++;
            }
        }
        i = 0;
        component = component->next;  
    }
    return 0;
}