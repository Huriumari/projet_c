#include "logicSimButInC.h"

static int offsetx, offsety;
static int origin_coordinate_system_wp_x, origin_coordinate_system_wp_y;
static GtkAllocation alloc;

gboolean mouse_pressed(GtkWidget *frameEventBox, GdkEventButton *event, data_t *data){

    int width, height;
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(data->window));

    if(frameEventBox)
        frameEventBox++;

    gtk_widget_get_allocation(data->workingLayout, &alloc);
    width = alloc.width;
    height = alloc.height;
    gtk_widget_get_allocation(data->window, &alloc);

    origin_coordinate_system_wp_x = alloc.width - width;
    origin_coordinate_system_wp_y = alloc.height - height;

    //printf("x : %d y : %d\n", origin_coordinate_system_wp_x, origin_coordinate_system_wp_y);

    gdk_window_get_position(gdk_window, &offsetx, &offsety);

    offsetx += (int)event->x + origin_coordinate_system_wp_x;
    offsety += (int)event->y + origin_coordinate_system_wp_y;

    //printf("offsetx : %d, offsety : %d\n", offsetx, offsety);
    return TRUE;
}

gboolean mouse_move(GtkWidget *frameEventBox, GdkEventButton *event, data_t *data){
    component_t *component;
    component_t *curComponent;
    GdkPixbuf   *pb;
    int x, y;
    int x_img, y_img;
    int is_on_another_comp = 0;
    

    //printf("Window : x:%d, y:%d | workingPart : x:%d, y:%d\n", alloc.width, alloc.height, width, height);

    component = data->component;
    curComponent = data->component;
    
    while(curComponent != NULL && frameEventBox != curComponent->frameEventBox)
            curComponent = curComponent->next;

    
    x = (int)event->x_root - offsetx;
    y = (int)event->y_root - offsety;

    printf("x : %d, y : %d\n", x, y);
    
    while (!is_on_another_comp && component != NULL){
        pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
        x_img = gdk_pixbuf_get_width(pb);
        y_img = gdk_pixbuf_get_height(pb);

        x_img = (double)x_img;
        y_img = (double)y_img;

        if (x > component->pos.x - x_img
        &&  x < component->pos.x + x_img
        &&  y > component->pos.y - y_img
        &&  y < component->pos.y + y_img)
            is_on_another_comp = 1;
        component = component->next;
    }

    if(!(is_on_another_comp) && (x != curComponent->pos.x || y != curComponent->pos.y) 
    /*&&  (x - x_img) > (- origin_coordinate_system_wp_x - x_img)
    &&  (x + x_img) < alloc.width
    &&  (y - y_img) > (- origin_coordinate_system_wp_y - y_img)
    &&  (y + y_img) < alloc.height*/){
        //printf("ok\n");
        component = data->component;
        component->pos.x = x;
        component->pos.y = y;
        gtk_layout_move(GTK_LAYOUT(data->workingLayout), curComponent->frameEventBox, x, y);
        gtk_widget_show_all(data->workingLayout);
    }

    return TRUE;
}