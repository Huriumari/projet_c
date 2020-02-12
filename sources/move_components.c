#include "logicSimButInC.h"

static int offsetx, offsety;

gboolean mouse_pressed(GtkWidget *frameEventBox, GdkEventButton *event, data_t *data){

    int width, height;
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(data->window));
    int origin_coordinate_system_wp_x, origin_coordinate_system_wp_y;
    GtkAllocation alloc;
    int scrollx = (int)gtk_adjustment_get_value(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(data->windowScrollWorking)));
    int scrolly = (int)gtk_adjustment_get_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(data->windowScrollWorking)));

    //printf("scrollx ; %d, scrolly : %d\n", scrollx, scrolly);

    if(frameEventBox)
        frameEventBox++;

    gtk_widget_get_allocation(data->workingLayout, &alloc);
    width = alloc.width;
    height = alloc.height;
    gtk_widget_get_allocation(data->window, &alloc);

    origin_coordinate_system_wp_x = alloc.width - width;
    origin_coordinate_system_wp_y = alloc.height - height;

    gdk_window_get_position(gdk_window, &offsetx, &offsety);

    offsetx += (int)event->x + origin_coordinate_system_wp_x - scrollx;
    offsety += (int)event->y + origin_coordinate_system_wp_y - scrolly;

    return TRUE;
}


gboolean mouse_move(GtkWidget *frameEventBox, GdkEventButton *event, data_t *data){
    component_t *component;
    component_t *curComponent;
    GdkPixbuf   *pb;
    int x, y;
    int x_img, y_img;
    int is_on_another_comp = 0;
    int i;
    int changed;
    link_t *link = data->link;   

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

    component = data->component;
    while(component != curComponent)
        component = component->next;

    if(!(is_on_another_comp) && (x != curComponent->pos.x || y != curComponent->pos.y)){
        curComponent->pos.x = x;
        curComponent->pos.y = y;
        while(link != NULL){
            changed = 0;
            if(link->id_o == curComponent->id){
                i = 0;
                while(i < curComponent->number_parts){
                    if(curComponent->parts[i].type == 'o'){
                        link->pos_o.x = curComponent->parts[i].pos.x;
                        link->pos_o.y = curComponent->parts[i].pos.y;
                        changed = 1;
                    }
                    i++;
                }
                
            }
            if(link->id_i == curComponent->id){
                i = 0;
                while(i < curComponent->number_parts && curComponent->parts[i].type != 'i'){
                    if(component->parts[i].pos.y < link->pos_i.y){
                        if(curComponent->parts[i].pos.y > curComponent->parts[i+1].pos.y){
                            link->pos_i.x = curComponent->parts[i].pos.x;
                            link->pos_i.y = curComponent->parts[i].pos.y;
                            changed = 1;
                        }
                        i++;
                    }
                }
            }
            if(changed){
                gtk_widget_destroy(link->img);
                create_img_from_link(link);
                visual_linking(data, link);
            }
            link = link->next;
        }
        
        gtk_layout_move(GTK_LAYOUT(data->workingLayout), curComponent->frameEventBox, x, y);
        gtk_widget_show_all(data->workingLayout);
    }

    return TRUE;
}