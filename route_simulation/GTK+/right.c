#include <gtk/gtk.h>

    label = gtk_label_new("Select file to complete group forwarding");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 3, 5, 8, 1);

    // pcap file path selection
    label = gtk_label_new("Pcap file path: ");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 2, 1, 2);
    pcapFile = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), pcapFile, 2, 6, 1, 2);
    button = gtk_button_new_with_label("Select file");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(select_file), pcapFile);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 6, 7, 2, 3);

    // Route table file path selection
    label = gtk_label_new("Route table file path: ");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 2, 3, 4);
    routeFile = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), routeFile, 2, 6, 3, 4);
    button = gtk_button_new_with_label("Select file");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(select_file), routeFile);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 6, 7, 3, 4);

    button = gtk_button_new_with_label("Clear");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), (gpointer)1);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 3, 3, 4);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Confirm");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), (gpointer)2);
    g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 7, 3, 4);
    gtk_widget_show(button);


int main(int argc,char *argv[]){
    
}