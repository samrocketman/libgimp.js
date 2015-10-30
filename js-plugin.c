#include "js-plugin.h"

typedef struct {
  gchar *greetee;
  /* stuff */
} JsPluginPrivate;

enum {
    PROP_GREETEE = 0;
}

static void
js_plugin_class_init (JsPluginClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->set_property = js_plugin_set_property;
    object_class->get_property = js_plugin_get_property;
    object_class->finalize = js_plugin_finalize;

    /**
     * JsPlugin:greetee:
     *
     * The entity to greet.
     */
    obj_properties[PROP_GREETEE] = 
        g_param_spec_string ("greetee",
                             "Greetee",
                             "The entity to greet.",
                             "World",
                             G_PARAM_READWRITE |
                             G_PARAM_CONSTRUCT);

    g_object_class_install_properties (object_class,
                                       N_PROPERTIES,
                                       obj_properties);

    g_type_class_add_private (object_class, sizeof (JsPluginPrivate));
}

/**
 * tut_greeter_greet:
 * @greeter: a #TutGreeter
 *
 * Prints a friendly greeting.
 *
 * Return value: nothing.
 */

void
js_plugin_greet (JsPlugin *plugin)
{
    JsPluginPrivate *priv;
    g_return_if_fail (greeter != NULL);

    priv = TUT_GREETER_GET_PRIVATE (plugin);
    printf ("Hello, %s!\n", priv->greetee);

}

void main() {
    GOptionContext *ctx;
    GError *error = NULL;

    ctx = g_option_context_new (NULL);
    g_option_context_add_group (ctx, g_irepository_get_option_group ());  

    if (!g_option_context_parse (ctx, &argc, &argv, &error)) {
        g_print ("greeter: %s\n", error->message);
        return 1;
    }

    gjs = gjs_context_new ();
    if (!gjs_context_eval_file (gjs, "main.js", &status, &error)) {
        g_print ("greeter: couldn't evaluate JavaScript: %s\n",
                 error->message);
        g_clear_error (&error);
    }
    g_object_unref (gjs);
}