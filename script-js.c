#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <string.h>
#include <glib/gstdio.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <glib/gi18n.h>

static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

MAIN()

static void
query (void)
{
  static GimpParamDef args[] =
  {
    {
      GIMP_PDB_INT32,
      "run-mode",
      "Run mode"
    },
    {
      GIMP_PDB_IMAGE,
      "image",
      "Input image"
    },
    {
      GIMP_PDB_DRAWABLE,
      "drawable",
      "Input drawable"
    }
  };

  gimp_install_procedure (
    "script-js",
    "Javascript Scripting Engine",
    "Allows users to write a Javascript script and install it as a plug-in in GIMP.",
    "Pratyusha Gupta, Scott Freeman",
    "Copyright Pratyusha Gupta, Scott Freeman",
    "2015",
    "_Console",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("script-js",
                             "<Image>/Filters/Javascript-Fu");
}

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,
     gint             *nreturn_vals,
     GimpParam       **return_vals)
{
  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals  = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if 
   * we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;

  if (run_mode != GIMP_RUN_NONINTERACTIVE) {

    gimp_ui_init ("jsfu", FALSE);

    GtkWidget *window;
    GtkWidget *button;
    GtkTextBuffer *buffer;
    GtkWidget *textbox;
    GtkWidget *vbox;
    GtkWidget *scrolled_window;

    window = gimp_dialog_new ("JS-Fu Console", "jsfu", NULL,
                           0, gimp_standard_help_func, "script-js",
                           GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                           GTK_STOCK_OK, GTK_RESPONSE_OK,
                           NULL);
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 12);
    gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (window))),
                        vbox, TRUE, TRUE, 0);
    gtk_widget_show (vbox);

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), 
                                     GTK_POLICY_AUTOMATIC,
                                     GTK_POLICY_ALWAYS);
    gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);

    buffer = gtk_text_buffer_new (NULL);
    textbox = gtk_text_view_new_with_buffer (buffer);
    g_object_unref (buffer);

    gtk_text_view_set_editable (GTK_TEXT_VIEW (textbox), FALSE);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textbox), GTK_WRAP_WORD);
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textbox), 6);
    gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textbox), 6);
    gtk_widget_set_size_request (textbox, 400, 480);


    gtk_container_add (GTK_CONTAINER (scrolled_window), textbox);

    gtk_widget_show (window);
    gtk_widget_show (textbox);
    int run = (gimp_dialog_run (GIMP_DIALOG (window)) == GTK_RESPONSE_OK);
    gtk_widget_destroy (window);
  }
}

