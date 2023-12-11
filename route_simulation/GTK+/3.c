#include <gtk/gtk.h>

// 回调函数：点击按钮时执行的操作
void on_button_clicked(GtkWidget *widget, gpointer data) {
    // 在这里添加按钮点击后的逻辑
    gint button_id = GPOINTER_TO_INT(data);
    if (button_id == 1) {
        // "Clear"按钮被点击
        // 执行清除操作
    } else if (button_id == 2) {
        // "Confirm"按钮被点击
        // 执行确认操作
    }
}

// 全局变量，用于保存选中的文件路径
char* selectedFilePath = NULL;

// 回调函数：选择文件时执行的操作
void select_file(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(data);

    // 创建文件选择对话框
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Select a file",                       // 对话框标题
        GTK_WINDOW(gtk_widget_get_toplevel(widget)),  // 对话框的父窗口，传入当前窗口
        GTK_FILE_CHOOSER_ACTION_OPEN,          // 对话框的操作类型为打开文件
        "Cancel", GTK_RESPONSE_CANCEL,          // 取消按钮的文本和响应
        "Open", GTK_RESPONSE_ACCEPT,            // 打开按钮的文本和响应
        NULL
    );

    // 运行文件选择对话框，等待用户操作
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        // 用户点击了打开按钮
        // 获取选中的文件路径
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        // 更新文本框中的文件路径
        gtk_entry_set_text(GTK_ENTRY(entry), filename);

        // 保存选中的文件路径到全局变量
        selectedFilePath = g_strdup(filename);

        // 释放选中的文件路径内存
        g_free(filename);
    }

    // 关闭文件选择对话框
    gtk_widget_destroy(dialog);
}

// 回调函数：确认选择文件时执行的操作
void file_OK(GtkWidget *widget, gpointer data) {
    // 在这里添加确认选择文件的逻辑
    if (selectedFilePath != NULL) {
        // 执行选中文件后的操作

        // 释放选中的文件路径内存
        g_free(selectedFilePath);
        selectedFilePath = NULL;
    }
}



int main(int argc, char *argv[]) {
    // 初始化GTK库
    gtk_init(&argc, &argv);

    // 创建顶层窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Table Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 创建表格
    GtkWidget *table = gtk_table_new(6, 8, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);

    // 创建标签并添加到表格中
    GtkWidget *label = gtk_label_new("Select file to complete group forwarding");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 2, 6, 0, 1);

    // 创建Pcap文件路径选择部分并添加到表格中
    label = gtk_label_new("Pcap file path: ");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 2, 1, 2);
    GtkWidget *pcapFile = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), pcapFile, 2, 6, 1, 2);
    GtkWidget *button = gtk_button_new_with_label("Select file");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(select_file), pcapFile);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 7, 8, 1, 2);

    // 创建空白行
    GtkWidget *emptyLabel = gtk_label_new("");
    gtk_table_attach_defaults(GTK_TABLE(table), emptyLabel, 0, 1, 2, 3);

    // 创建路由表文件路径选择部分并添加到表格中
    label = gtk_label_new("Route table file path: ");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 2, 3, 4);
    GtkWidget *routeFile = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), routeFile, 2, 6, 3, 4);
    button = gtk_button_new_with_label("Select file");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(select_file), routeFile);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 7, 8, 3, 4);

    // 创建"Clear"按钮并添加到表格中
    button = gtk_button_new_with_label("Clear");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), GINT_TO_POINTER(1));
    gtk_table_attach(GTK_TABLE(table), button, 2, 4, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
    gtk_widget_show(button);

    // 创建"Confirm"按钮并添加到表格中
    button = gtk_button_new_with_label("Confirm");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), GINT_TO_POINTER(2));
    g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_table_attach(GTK_TABLE(table), button, 4, 6, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
    gtk_widget_show(button);

    // 显示窗口及其内容
    gtk_widget_show_all(window);

    // 进入GTK主循环
    gtk_main();

    return 0;
}
