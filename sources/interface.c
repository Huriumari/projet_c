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
void menubar(GtkWidget * window, GtkWidget * vBox){
	
	GtkWidget* menubar;
	GtkWidget* fileMenu;
  	GtkWidget* file;
	GtkWidget* new;
	GtkWidget* open;
	GtkWidget* save;
	GtkWidget* saveAs;
	GtkWidget* quit;
	GtkWidget* moduleMenu;
	GtkWidget* module;
	GtkWidget* create;
	GtkWidget* import;
	GtkWidget* export;
	GtkWidget* properties;

	GtkWidget* sep;

	GtkAccelGroup* accel_group = NULL;

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
    
	gtk_widget_add_accelerator(new, "activate", accel_group, GDK_KEY_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(open, "activate", accel_group, GDK_KEY_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(save, "activate", accel_group, GDK_KEY_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(saveAs, "activate", accel_group, GDK_KEY_s, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(quit, "activate", accel_group, GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

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


void toolbar(GtkWidget * vBox){
	
	GtkWidget* toolbar;
  	GtkToolItem* newTb;
  	GtkToolItem* openTb;
  	GtkToolItem* saveTb;
  	GtkToolItem* tagTb;
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

	saveTb = gtk_tool_button_new(NULL, "Tag");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);
	
	tagTb = gtk_tool_button_new(gtk_image_new_from_icon_name("preferences-system", GTK_ICON_SIZE_SMALL_TOOLBAR), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tagTb, -1);

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

}


void workingPart(GtkWidget * vBox){
	
	GtkWidget* grid;
	GtkWidget* scrolledWindowComponents;
	GtkWidget* componentsLayout;
	GtkWidget* p_Label;
	gchar* sUtf8;

	GtkWidget* windowScrollWorking;
	GtkWidget* workingLayout;
	guint * widthLayout;
	guint * heightLayout;

	grid = gtk_grid_new();
	gtk_container_set_border_width (GTK_CONTAINER (grid), 5);
    gtk_box_pack_start(GTK_BOX(vBox), grid, TRUE, TRUE, 0);
	

	scrolledWindowComponents = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindowComponents), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(scrolledWindowComponents), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (scrolledWindowComponents), 2);
	gtk_widget_set_hexpand(scrolledWindowComponents, TRUE);
	gtk_widget_set_vexpand(scrolledWindowComponents, TRUE);
	gtk_grid_attach(GTK_GRID(grid), scrolledWindowComponents, 0, 0, 1, 1);

	componentsLayout = gtk_layout_new(NULL, NULL);
	gtk_layout_set_size(GTK_LAYOUT(componentsLayout), 150, 2000);
	gtk_container_add(GTK_CONTAINER(scrolledWindowComponents), componentsLayout);


	GtkWidget* p_Label2;
	sUtf8 = g_locale_to_utf8("La Bibliothèque GTK+ à bien été Installée !", -1, NULL, NULL, NULL);
    p_Label = gtk_label_new(sUtf8);
	p_Label2 = gtk_label_new(sUtf8);
    g_free(sUtf8);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), p_Label, 0, 50);
	gtk_layout_put(GTK_LAYOUT(componentsLayout), p_Label2, 50, 0);
	
	GtkWidget * test;
	test = gtk_button_new_with_label("Test");	
	gtk_layout_put(GTK_LAYOUT(componentsLayout), test, 0, 0);

	windowScrollWorking = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(windowScrollWorking), TRUE);
	gtk_widget_set_hexpand(windowScrollWorking, TRUE);
	gtk_widget_set_vexpand(windowScrollWorking, TRUE);
	gtk_grid_attach(GTK_GRID(grid), windowScrollWorking, 1, 0, 4, 1);

	workingLayout = gtk_layout_new(NULL, NULL);
	gtk_layout_set_size(GTK_LAYOUT(workingLayout), 2000, 2000);
	//gtk_widget_set_hexpand(workingLayout, TRUE);
   	//gtk_widget_set_vexpand(workingLayout, TRUE);
	widthLayout = malloc(sizeof(guint));
	heightLayout = malloc(sizeof(guint));
	gtk_container_add(GTK_CONTAINER(windowScrollWorking), workingLayout);
	gtk_layout_get_size(GTK_LAYOUT(workingLayout), widthLayout, heightLayout);

}