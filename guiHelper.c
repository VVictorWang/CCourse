//
// Created by victor on 8/17/17.
//
#include "head.h"


/*************************************************
 @Function: create_pixbuf
 @Description: return a pixbuf with the given filename.
 @param filename: the name of file
 @return: the pixbuf that creates.
*************************************************/
GdkPixbuf * create_pixbuf(const gchar * filename)
{
    GdkPixbuf * pixbuf;
    GError * error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf)
    {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

/*************************************************
Function: warning_message_dialog
Description: run a dialog showing warning messages.
Input: gchar * indicating the title of the dialog
       gchat * indicating the content of the dialog
Output: None
Return: None
Others: None
*************************************************/
void warning_message_dialog(gchar * title, gchar * message)
{
    GdkPixbuf * pixbuf = create_pixbuf("/home/victor/CLionProjects/course/ img/icon.png");
    GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, message);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/*************************************************
Function: error_message_dialog
Description: run a dialog showing error messages.
Input: gchar * indicating the title of the dialog
       gchat * indicating the content of the dialog
Output: None
Return: None
Others: None
*************************************************/
void error_message_dialog(gchar * title, gchar * message)
{
    GdkPixbuf * pixbuf = create_pixbuf("img/icon.png");
    GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}