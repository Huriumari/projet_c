#include "logicSimButInC.h"

gboolean mouse_pressed(GtkWidget *frameEventBox, component_t *component){

    if(frameEventBox)
        frameEventBox++;

    printf("x : %f, y : %f\n", component->pos.x, component->pos.y);
    return TRUE;
}

gboolean mouse_move(GtkWidget *widget, GdkEventButton *event, data_t *data){
    component_t *component;
    component_t *curComponent;
    GdkPixbuf   *pb;
    int x, y;
    int is_on_another_comp = 0;

    component = data->component;
    curComponent = data->curComponent;

    if(widget)
        widget++;

    while (!is_on_another_comp && component != NULL){
        pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
        x = gdk_pixbuf_get_width(pb);
        y = gdk_pixbuf_get_height(pb);

        if (event->x > component->pos.x - (double)(x)
        &&  event->x < component->pos.x + (double)(x)
        &&  event->y > component->pos.y - (double)(y)
        &&  event->y < component->pos.y + (double)(y))
            is_on_another_comp = 1;
        component = component->next;
    }

    if(!(is_on_another_comp) && (event->x != curComponent->pos.x || event->y != curComponent->pos.y)){
        component = data->component;
        while(component != curComponent)
            component = component->next;
        component->pos.x = event->x;
        component->pos.y = event->y;
        gtk_layout_move(GTK_LAYOUT(data->workingLayout), curComponent->frameEventBox, event->x, event->y);
        gtk_widget_show_all(data->workingLayout);
    }

    return TRUE;
}