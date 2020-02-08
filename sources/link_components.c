#include "logicSimButInC.h"

//check if the component part is free
//One output can have multiple links
//One input can have only one link connected

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

    static int clickCounter = 0;
    static link_t *link;
    
    if(widget)
        widget++;

    if(clickCounter == 0){
        link = malloc(sizeof(link_t));
        link->next = data->link;
        link->pos_i.x = event->x;
        link->pos_i.y = event->y;
        link->id = new_component_id(0);
        link->id_i = new_component_id(0);
        link->id_o = new_component_id(0);
        data->link = link;
    }
    else if(clickCounter == 1){
        link->pos_o.x = event->x;
        link->pos_o.y = event->y;
        clickCounter = 0;
    }

    clickCounter++;
}
