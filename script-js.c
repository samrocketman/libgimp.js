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
hello (GtkWidget *widget,
       gpointer data)
{
  g_print ("Hellow World \n");
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
   /*  g_message("This is the new output!\n"); */

    gimp_ui_init ("jsfu", FALSE);

    GtkWidget *window;
    GtkWidget *button;
    GtkTextBuffer *buffer;

    window = gimp_dialog_new ("JS-Fu Console", "jsfu", NULL,
                           0, gimp_standard_help_func, "script-js",
                           GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                           GTK_STOCK_OK, GTK_RESPONSE_OK,
                           NULL);

  /* gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  button = gtk_button_new_with_label ("Hellow World");
  g_signal_connect (button, "clicked", G_CALLBACK (hello), NULL);
  gtk_container_add (GTK_CONTAINER (window), button);
  gtk_widget_show (button);
  gtk_widget_show (window);
  gtk_main(); */

    gtk_widget_show (window);
    int run = (gimp_dialog_run (GIMP_DIALOG (window)) == GTK_RESPONSE_OK);
    gtk_widget_destroy (window);
  }
}

