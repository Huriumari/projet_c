//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions de callback


#include "logicSimButInC.h"

void    mousePos(GtkWidget * mouse, GdkEvent *event, gpointer gtk_data){
    GdkEventButton* mouse_click = (GdkEventButton *) event;
    data_t      *data = (data_t *)gtk_data;
    char        is_on_another_comp;
    component_t *component;
    GdkPixbuf   *pb;
    double      x,y;

    if (mouse)
        is_on_another_comp = 0;
    else
        is_on_another_comp = 0;
    
    if(data->imgPath != NULL){
        if(strcmp(data->imgPath, "delete") == 0){
            remove_component(data, mouse_click->x, mouse_click->y);
            data->imgPath = NULL;
        }else if(strcmp(data->imgPath, "LINK") == 0){
            link_coordinates(data, mouse_click->x, mouse_click->y);
        }else{
          component = data->component;
          while (!is_on_another_comp && component != NULL){
            pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
            x = gdk_pixbuf_get_width(pb);
            y = gdk_pixbuf_get_height(pb);
            if (mouse_click->x > component->pos.x - (double)(x)
            &&  mouse_click->x < component->pos.x + (double)(x)
            &&  mouse_click->y > component->pos.y - (double)(y)
            &&  mouse_click->y < component->pos.y + (double)(y))
                is_on_another_comp = 1;
            component = component->next;
        }

        if (!is_on_another_comp){
            add_component(data, data->imgPath, mouse_click->x, mouse_click->y);
            data->imgPath = NULL;
        }
      }
  }else
      select_component(data, mouse_click->x, mouse_click->y);

}

gboolean    isClicked(GtkWidget * comp, gpointer gtk_data){

  data_t * data = (data_t *)gtk_data;
  
  if (data->imgPath != NULL && !strcmp(data->imgPath, "LINK"))
    link_coordinates(data, -1.,-1.);

  if(strcmp(gtk_widget_get_name(comp), "compAND") == 0)
      data->imgPath = "AND";

  else if(strcmp(gtk_widget_get_name(comp), "compNAND") == 0)
	  data->imgPath = "NAND";

  else if(strcmp(gtk_widget_get_name(comp), "compOR") == 0)
		data->imgPath = "OR";

  else if(strcmp(gtk_widget_get_name(comp), "compNOR") == 0)
		data->imgPath = "NOR";

  else if(strcmp(gtk_widget_get_name(comp), "compXOR") == 0)
		data->imgPath = "XOR";

else if(strcmp(gtk_widget_get_name(comp), "compLINK") == 0)
		data->imgPath = "LINK";

  else if(strcmp(gtk_widget_get_name(comp), "compOUTPUT_OFF") == 0)
		data->imgPath = "OUTPUT_OFF";

  else if(strcmp(gtk_widget_get_name(comp), "compINPUT_OFF") == 0)
		data->imgPath = "INPUT_OFF";
  
  else if(strcmp(gtk_widget_get_name(comp), "delete") == 0)
    data->imgPath = "delete";

  return TRUE;

}
/*
void dragComponents(GtkWidget* comp, gpointer gtk_data){
    GtkWidget * workingLayout;
    data_t * data = (data_t *)gtk_data;
    workingLayout = comp;
    workingLayout = data->workingLayout;

    //printf("%s\n", data->imgPath);
    //g_signal_connect_after(G_OBJECT(workingLayout), "delete-event", G_CALLBACK(delete_event), NULL);
    //g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(mousePos), data);
}*/