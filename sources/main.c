/*
	Programme de simulation de composants logiques.
	Clément Bossard & Clément K-R
*/

#include "logicSimButInC.h"


int main(int argc,char **argv)
{
	GtkWidget	*window;
	GtkWidget	*vBox;
	GtkWidget	*grid;
	GtkWidget	*workingLayout;
	data_t		*data;
	//char		*test;
	//GtkCssProvider *cssProvider; 

	data = g_malloc(sizeof(data_t));
	data->imgPath = NULL;
	data->component = NULL;
	data->filename = NULL;
	data->link = NULL;
    
	data->option = read_option_file();
	if (data->option == NULL){
		printf("Error: failed to open option.txt file,\n");
	}
	window = gtkWindow(&argc, &argv);
	
	/*cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(cssProvider, ".frame{border:10px solid red;}", -1, NULL);
	gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(window), GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
*/
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(window), vBox);
	menubar(window, vBox, data);

	toolbar(vBox, data);

	grid = gtk_grid_new();
	gtk_container_set_border_width (GTK_CONTAINER (grid), 5);
    gtk_box_pack_start(GTK_BOX(vBox), grid, TRUE, TRUE, 0);

	workingLayout = workingPart(grid, data);
	componentsPart(data, grid, window, workingLayout);
	data->drawing_area = gdk_window_create_similar_surface(gtk_widget_get_window (workingLayout), CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width (workingLayout), gtk_widget_get_allocated_height (workingLayout));
	

	//print_option(data->option);
	//test = get_option(data->option, "component_img_path");
	//printf("%s\n",test);

	gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}