//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"


/*************************************************
 @name: create_pixbuf
 @function: return a pixbuf with the given filename.
 @param filename: the name of file
 @return: the pixbuf that creates.
*************************************************/
GdkPixbuf *create_pixbuf(const gchar *filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

/*************************************************
 @name: warning_message_dialog
 @function: run a dialog showing warning messages.
 @param title: the title of the dialog
 @param message: the content of the dialog
 @return none
*************************************************/
void warning_message_dialog(gchar *title, gchar *message) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK, message);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: error_message_dialog
 @function: run a dialog showing error messages.
 @param title: the title of the dialog
 @param message: the content of the dialog
 @return none
*************************************************/
void error_message_dialog(gchar *title, gchar *message) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK, message);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: information_message_dialog
 @function: run a dialog showing information messages.
 @param title: the title of the dialog
 @param message: the content of the dialog
 @return none
*************************************************/
void information_message_dialog(gchar *title, gchar *message) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK, message);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: addTreeColumnView
 @function: add a column to a excel.
 @param list: the widget which the column will be added to
 @param renderer: the cell renderer
 @param columnDes: the text description of the column
 @param columnNo: the index of the column
 @return none
*************************************************/
void addTreeColumnView(GtkWidget *list, GtkCellRenderer *renderer, char *columnDes, int columnNo) {
    GtkTreeViewColumn *addColumn = gtk_tree_view_column_new_with_attributes(columnDes, renderer,
                                                                            "text",
                                                                            columnNo, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(addColumn),
                                    GTK_TREE_VIEW_COLUMN_AUTOSIZE);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(addColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(addColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), addColumn);
}


/*************************************************
 @name: setTableView
 @function: set the widgets of a new table.
 @param labels: the labels in the first column of the table
 @param entries: the widgets in the second column of the table
 @param dialog: the parent dialog to show the table
 @return none
*************************************************/
void setTableView(GtkWidget **labels, GtkWidget **entries, GtkWidget *dialog) {
    unsigned int length = (unsigned int) getGtkWidgetListLen(labels);
    GtkWidget *table = gtk_table_new(length, 2, FALSE);
    unsigned int i = 0;
    for (i = 0; i < length; i++) {
        gtk_table_attach_defaults(GTK_TABLE(table), labels[i], 0, 1, i, i + 1);
        gtk_table_attach_defaults(GTK_TABLE(table), entries[i], 1, 2, i, i + 1);
    }
    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(table), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), table);
}