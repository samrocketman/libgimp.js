#include "script-js.h"

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

  /* Set up the dialog */
  if (run_mode != GIMP_RUN_NONINTERACTIVE) {

    gimp_ui_init ("jsfu", FALSE);
    Console console;
    GtkTextIter iter;
    const gchar *header = "Welcome to Javascript-Fu Console\n\0";
    const gchar *subheader = "Interactive Javascript Development\n\n\0";
    const gchar *submit = "Submit...";

    /* Main dialog */
    console.window = gimp_dialog_new ("JS-Fu Console", "jsfu", NULL,
                           0, gimp_standard_help_func, "script-js",
                           GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                           GTK_STOCK_OK, GTK_RESPONSE_OK,
                           NULL);
    
    /* Box to package all of the pieces */
    console.box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width (GTK_CONTAINER (console.box), 12);
    gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (console.window))),
                        console.box, TRUE, TRUE, 0);

    /* Show the box */
    gtk_widget_show (console.box);

    /* Create the scrolled window */
    console.scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (console.scrolled_window), 
                                     GTK_POLICY_AUTOMATIC,
                                     GTK_POLICY_ALWAYS);
    
    /* Pack and show the scrolled window */
    gtk_box_pack_start (GTK_BOX (console.box), console.scrolled_window, TRUE, TRUE, 0);
    gtk_widget_show (console.scrolled_window);

    /* Create the text buffer and textbox */
    console.buffer = gtk_text_buffer_new (NULL);
    gtk_text_buffer_get_start_iter (console.buffer, &iter);

    gtk_text_buffer_create_tag (console.buffer, "header", "weight", PANGO_WEIGHT_BOLD,
                                "scale", PANGO_SCALE_LARGE, NULL);

    gtk_text_buffer_create_tag (console.buffer, "subheader", "style", PANGO_STYLE_OBLIQUE,
                                NULL);

    gtk_text_buffer_insert_with_tags_by_name (console.buffer, &iter, header, -1, "header", NULL);
    gtk_text_buffer_insert_with_tags_by_name (console.buffer, &iter, subheader, -1, "subheader", NULL);
    console.textbox = gtk_text_view_new_with_buffer (console.buffer);
    
    /* Create the button */
    console.button = gtk_button_new_with_label(submit);
    gtk_misc_set_padding (GTK_MISC (gtk_bin_get_child (GTK_BIN (console.button))), 0, 0);
    gtk_box_pack_start (GTK_BOX (console.box), console.button, FALSE, TRUE, 0);
    gtk_widget_show (console.button);
    
    /* Connect the callback signal for when the button is pressed */
    g_signal_connect (console.button, "clicked", G_CALLBACK (js_fu_submit), console.buffer);

    /* Set the properties of the textbox */
    gtk_text_view_set_editable (GTK_TEXT_VIEW (console.textbox), TRUE);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (console.textbox), GTK_WRAP_WORD);
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (console.textbox), 6);
    gtk_text_view_set_right_margin (GTK_TEXT_VIEW (console.textbox), 6);
    gtk_widget_set_size_request (console.textbox, 400, 480);

    /* Add and show the textbox */
    gtk_container_add (GTK_CONTAINER (console.scrolled_window), console.textbox);
    gtk_widget_show (console.window);
    gtk_widget_show (console.textbox);
    int run = (gimp_dialog_run (GIMP_DIALOG (console.window)) == GTK_RESPONSE_OK);
    gtk_widget_destroy (console.window);
  }
}

/* On "Submit" button click */
static void
js_fu_submit (GtkWidget *widget, GtkTextBuffer *buffer)
{
  GtkTextIter start, end;
  gchar * text;

  /* Gets the start and stop points for the buffer */
  gtk_text_buffer_get_iter_at_line (buffer, &start, 3);
  gtk_text_buffer_get_end_iter (buffer, &end);
  text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

  printf(text);

  printf("\n");
  fflush(stdout);
}
