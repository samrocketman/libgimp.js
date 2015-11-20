// A class for JavaScript introspection

#include <stdio.h>
#include "js-plugin.h"

G_DEFINE_TYPE (JsPlugin, js_plugin, G_TYPE_OBJECT)

#define JS_PLUGIN_GET_PRIVATE(o)  \
    (G_TYPE_INSTANCE_GET_PRIVATE ((o), JS_PLUGIN_TYPE, JsPluginPrivate))

struct _JsPluginPrivate {
    gchar *greetee;     /* The entity to greet */
};

enum
{
    PROP_0,

    PROP_GREETEE,

    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void
js_plugin_init (TutGreeter *object)
{
    TutGreeterPrivate *priv = TUT_GREETER_GET_PRIVATE (object);

    priv->greetee = NULL;
}

static void
js_plugin_finalize (GObject *object)
{
    TutGreeterPrivate *priv = TUT_GREETER_GET_PRIVATE (object);

    g_free (priv->greetee);
    G_OBJECT_CLASS (tut_greeter_parent_class)->finalize (object);
}

static void
js_plugin_set_property (GObject      *object,
              guint         property_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    TutGreeterPrivate *priv = TUT_GREETER_GET_PRIVATE (object);

    switch (property_id) {
    case PROP_GREETEE:
    g_free (priv->greetee);
    priv->greetee = g_value_dup_string (value);
    break;

    default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
    }
}

static void
js_plugin_get_property (GObject    *object,
              guint       property_id,
              GValue     *value,
              GParamSpec *pspec)
{
    JsPluginPrivate *priv = TUT_GREETER_GET_PRIVATE (object);

    switch (property_id) {
    case PROP_GREETEE:
    g_value_set_string (value, priv->greetee);
    break;

    default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
    }
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
 * js_plugin_new:
 *
 * Allocates a new #JsPlugin.
 *
 * Return value: a new #JsPlugin.
 */

JsPlugin*
js_plugin_new ()
{
    JsPlugin *plugin;

    plugin = g_object_new (JS_PLUGIN_TYPE, NULL);
    return plugin;
}

/**
 * js_plugin_greet:
 * @greeter: a #JsPlugin
 *
 * Prints a friendly greeting.
 *
 * Return value: nothing.
 */

void
js_plugin_greet (JsPlugin *plugin)
{
    JsPluginPrivate *priv;
    g_return_if_fail (plugin != NULL);

    priv = TUT_GREETER_GET_PRIVATE (plugin);
    printf ("Hello, %s!\n", priv->greetee);

}