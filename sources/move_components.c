#include "logicSimButInC.h"

static int offsetx, offsety;

gboolean mouse_pressed(GtkWidget *frameEventBox, GdkEventButton *event, data_t *data){

    int width, height;
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(data->window));
    int origin_coordinate_system_wp_x, origin_coordinate_system_wp_y;
    GtkAllocation alloc;
    int scrollx = (int)gtk_adjustment_get_value(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(data->windowScrollWorking)));
    int scrolly = (int)gtk_adjustment_get_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(data->windowScrollWorking)));

    printf("scrollx ; %d, scrolly : %d\n", scrollx, scrolly);

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

    offsetx += (int)event->x + origin_coordinate_system_wp_x + scrollx;
    offsety += (int)event->y + origin_coordinate_system_wp_y + scrolly;

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

    //printf("x : %d, y : %d\n", x, y);
    
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

    if(!(is_on_another_comp) && (x != curComponent->pos.x || y != curComponent->pos.y)){
        curComponent->pos.x = x;
        curComponent->pos.y = y;
        gtk_layout_move(GTK_LAYOUT(data->workingLayout), curComponent->frameEventBox, x, y);
        gtk_widget_show_all(data->workingLayout);
    }

    return TRUE;
}