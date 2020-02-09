#include "logicSimButInC.h"

GtkWidget * gtkWindow(int *argc, char ***argv){
	
	GtkWidget* window;

	gtk_init(argc,argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ 3.22");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return window;

}


//create the menubar and the keyboards shortcuts
void menubar(GtkWidget * window, GtkWidget * vBox, data_t * data){
	
	GtkWidget 	*menubar;
	GtkWidget 	*fileMenu;
  	GtkWidget 	*file;
	GtkWidget 	*new;
	GtkWidget 	*open;
	GtkWidget 	*save;
	GtkWidget 	*saveAs;
	GtkWidget 	*quit;
	GtkWidget 	*moduleMenu;
	GtkWidget 	*module;
	GtkWidget 	*create;
	GtkWidget 	*import;
	GtkWidget 	*export;
	GtkWidget 	*properties;
	GtkWidget 	*sep;

	GtkAccelGroup* accel_group = NULL;
	if (data == NULL)
		printf("pouet\n");

	menubar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();
	moduleMenu = gtk_menu_new();

	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);


	file = gtk_menu_item_new_with_mnemonic("_File");
  	new = gtk_menu_item_new_with_mnemonic("New");
  	open = gtk_menu_item_new_with_mnemonic("Open");
	save = gtk_menu_item_new_with_mnemonic("Save");
	saveAs = gtk_menu_item_new_with_mnemonic("SaveAs");
  	sep = gtk_separator_menu_item_new();
  	quit = gtk_menu_item_new_with_mnemonic("Quit");

	module = gtk_menu_item_new_with_mnemonic("_Module");
	create = gtk_menu_item_new_with_mnemonic("Create");
	import = gtk_menu_item_new_with_mnemonic("Import");
	export = gtk_menu_item_new_with_mnemonic("Export");
	properties = gtk_menu_item_new_with_mnemonic("Properties");
    
    
	
	create_shortcut(data, accel_group);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
  	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), new);
  	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), save);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveAs);
  	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);
  	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quit);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(module), moduleMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(moduleMenu), create);
	gtk_menu_shell_append(GTK_MENU_SHELL(moduleMenu), import);
	gtk_menu_shell_append(GTK_MENU_SHELL(moduleMenu), export);
	gtk_menu_shell_append(GTK_MENU_SHELL(moduleMenu), properties);

  	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), module);
    gtk_box_pack_start(GTK_BOX(vBox), menubar, FALSE, FALSE, 0);

	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);

}


void toolbar(GtkWidget * vBox, data_t *data){
	
	GtkWidget* toolbar;
  	GtkToolItem* newTb;
  	GtkToolItem* openTb;
  	GtkToolItem* saveTb;
  	GtkToolItem* tagTb;
	GtkToolItem* deleteTb;
	GtkToolItem* playTb;
	GtkToolItem* pauseTb;
	GtkToolItem* stopTb;
	GtkWidget* entryItem;
	GtkToolItem* simuSpeedTb;

	GtkToolItem* sepTool;
	


	toolbar = gtk_toolbar_new();
  	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	newTb = gtk_tool_button_new(gtk_image_new_from_icon_name("document-new", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);

	openTb = gtk_tool_button_new(gtk_image_new_from_icon_name("document-open", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);

	saveTb = gtk_tool_button_new(gtk_image_new_from_icon_name("document-save", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);
	
	tagTb = gtk_tool_button_new(NULL, "Tag");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tagTb, -1);

	deleteTb = gtk_tool_button_new(gtk_image_new_from_icon_name("edit-delete", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_widget_set_name(GTK_WIDGET(deleteTb), "delete");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), deleteTb, -1);

	sepTool = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sepTool, -1);

	playTb = gtk_tool_button_new(gtk_image_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), playTb, -1);

	pauseTb = gtk_tool_button_new(gtk_image_new_from_icon_name("media-playback-pause", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), pauseTb, -1);

	stopTb = gtk_tool_button_new(gtk_image_new_from_icon_name("media-playback-stop", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), stopTb, -1);

	entryItem = gtk_entry_new();
	simuSpeedTb = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(simuSpeedTb), entryItem);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), simuSpeedTb, -1);
	gtk_box_pack_start(GTK_BOX(vBox), toolbar, FALSE, FALSE, 5);

	g_signal_connect(G_OBJECT(deleteTb), "clicked", G_CALLBACK(isClicked), data);	
	g_signal_connect(G_OBJECT(deleteTb), "clicked", G_CALLBACK(dragComponents), data);	

}


void componentsPart(data_t *data, GtkWidget * grid, GtkWidget * window, GtkWidget * workingLayout){
	GtkWidget* scrolledWindowComponents;
	GtkWidget* componentsLayout;
	GtkSizeGroup * sizeGroup;
	GtkWidget* compAND;
	GtkWidget	*compNAND;
	GtkWidget	*compOR;
	GtkWidget	*compNOR;
	GtkWidget	*compXOR;
	GtkWidget	*compLINK;
	GtkWidget	*compInputOFF;
	GtkWidget	*compOutputOFF;
	GtkWidget	*sep;
	char		*ptr;
	char		buffer[255];


	data->window = window;
	data->workingLayout = workingLayout;

	scrolledWindowComponents = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindowComponents), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(scrolledWindowComponents), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (scrolledWindowComponents), 2);
	gtk_widget_set_hexpand(scrolledWindowComponents, TRUE);
	gtk_widget_set_vexpand(scrolledWindowComponents, TRUE);
	gtk_grid_attach(GTK_GRID(grid), scrolledWindowComponents, 0, 0, 1, 1);

	componentsLayout = gtk_layout_new(NULL, NULL);
	gtk_layout_set_size(GTK_LAYOUT(componentsLayout), 50, 2000);
	gtk_container_add(GTK_CONTAINER(scrolledWindowComponents), componentsLayout);

	sizeGroup = gtk_size_group_new(GTK_SIZE_GROUP_BOTH);

	ptr = get_option(data->option, "component_img_path");
	if (ptr == NULL){
		printf("Error: cannot found image for components.\n");
		exit(0);
	}
	strcat(strcpy(buffer, ptr),"/AND.png");
	compAND = componentsButton(buffer);
	gtk_widget_set_name(compAND, "compAND");
	gtk_size_group_add_widget(sizeGroup, compAND);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compAND, 0, 0);

	strcat(strcpy(buffer, ptr),"/NAND.png");
	compNAND = componentsButton(buffer);
	gtk_widget_set_name(compNAND, "compNAND");
	gtk_size_group_add_widget(sizeGroup, compNAND);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compNAND, 0, 75);

	strcat(strcpy(buffer, ptr),"/OR.png");
	compOR = componentsButton(buffer);
	gtk_widget_set_name(compOR, "compOR");
	gtk_size_group_add_widget(sizeGroup, compOR);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compOR, 0, 150);

	strcat(strcpy(buffer, ptr),"/NOR.png");
	compNOR = componentsButton(buffer);
	gtk_widget_set_name(compNOR, "compNOR");
	gtk_size_group_add_widget(sizeGroup, compNOR);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compNOR, 0, 225);
	
	strcat(strcpy(buffer, ptr),"/XOR.png");
	compXOR = componentsButton(buffer);
	gtk_widget_set_name(compXOR, "compXOR");
	gtk_size_group_add_widget(sizeGroup, compXOR);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compXOR, 0, 300);

	strcat(strcpy(buffer, ptr),"/LINK.png");
	compLINK = componentsButton(buffer);
	gtk_widget_set_name(compLINK, "compLINK");
	gtk_size_group_add_widget(sizeGroup, compLINK);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compLINK, 0, 300);

	sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), sep, 0, 350);

	strcat(strcpy(buffer, ptr),"/OUTPUT_OFF.png");
	compOutputOFF = componentsButton(buffer);
	gtk_widget_set_name(compOutputOFF, "compOUTPUT_OFF");
	gtk_size_group_add_widget(sizeGroup, compOutputOFF);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compOutputOFF, 0, 400);

	strcat(strcpy(buffer, ptr),"/INPUT_OFF.png");
	compInputOFF = componentsButton(buffer);
	gtk_widget_set_name(compInputOFF, "compINPUT_OFF");
	gtk_size_group_add_widget(sizeGroup, compInputOFF);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), compInputOFF, 0, 475);

	g_signal_connect(G_OBJECT(compAND), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compAND), "clicked", G_CALLBACK(dragComponents), data);
	
	g_signal_connect(G_OBJECT(compNAND), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compNAND), "clicked", G_CALLBACK(dragComponents), data);

	g_signal_connect(G_OBJECT(compOR), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compOR), "clicked", G_CALLBACK(dragComponents), data);
	
	g_signal_connect(G_OBJECT(compNOR), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compNOR), "clicked", G_CALLBACK(dragComponents), data);

	g_signal_connect(G_OBJECT(compXOR), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compXOR), "clicked", G_CALLBACK(dragComponents), data);

	g_signal_connect(G_OBJECT(compOutputOFF), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compOutputOFF), "clicked", G_CALLBACK(dragComponents), data);

	g_signal_connect(G_OBJECT(compInputOFF), "clicked", G_CALLBACK(isClicked), data);
	g_signal_connect(G_OBJECT(compInputOFF), "clicked", G_CALLBACK(dragComponents), data);
}


GtkWidget * workingPart(GtkWidget * grid){

	GtkWidget* windowScrollWorking;
	GtkWidget* workingLayout;
	guint* widthLayout;
	guint* heightLayout;


	windowScrollWorking = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(windowScrollWorking), TRUE);
	gtk_widget_set_hexpand(windowScrollWorking, TRUE);
	gtk_widget_set_vexpand(windowScrollWorking, TRUE);
	gtk_grid_attach(GTK_GRID(grid), windowScrollWorking, 1, 0, 10, 1);	

	workingLayout = gtk_layout_new(NULL, NULL);
	gtk_layout_set_size(GTK_LAYOUT(workingLayout), 2000, 2000);
	//gtk_widget_set_hexpand(workingLayout, TRUE);
   	//gtk_widget_set_vexpand(workingLayout, TRUE);
	widthLayout = malloc(sizeof(guint));
	heightLayout = malloc(sizeof(guint));
	gtk_container_add(GTK_CONTAINER(windowScrollWorking), workingLayout);
	gtk_layout_get_size(GTK_LAYOUT(workingLayout), widthLayout, heightLayout);

	return workingLayout;

}