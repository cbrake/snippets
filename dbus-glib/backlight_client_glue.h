/* Generated by dbus-binding-tool; do not edit! */

#include <glib/gtypes.h>
#include <glib/gerror.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

#ifndef DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Introspectable
#define DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Introspectable

static
#ifdef G_HAVE_INLINE
inline
#endif
gboolean
org_freedesktop_DBus_Introspectable_introspect (DBusGProxy *proxy, char ** OUT_data, GError **error)

{
  return dbus_g_proxy_call (proxy, "Introspect", error, G_TYPE_INVALID, G_TYPE_STRING, OUT_data, G_TYPE_INVALID);
}

typedef void (*org_freedesktop_DBus_Introspectable_introspect_reply) (DBusGProxy *proxy, char * OUT_data, GError *error, gpointer userdata);

static void
org_freedesktop_DBus_Introspectable_introspect_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  char * OUT_data;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_STRING, &OUT_data, G_TYPE_INVALID);
  (*(org_freedesktop_DBus_Introspectable_introspect_reply)data->cb) (proxy, OUT_data, error, data->userdata);
  return;
}

static
#ifdef G_HAVE_INLINE
inline
#endif
DBusGProxyCall*
org_freedesktop_DBus_Introspectable_introspect_async (DBusGProxy *proxy, org_freedesktop_DBus_Introspectable_introspect_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_new (DBusGAsyncData, 1);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "Introspect", org_freedesktop_DBus_Introspectable_introspect_async_callback, stuff, g_free, G_TYPE_INVALID);
}
#endif /* defined DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Introspectable */

#ifndef DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Properties
#define DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Properties

static
#ifdef G_HAVE_INLINE
inline
#endif
gboolean
org_freedesktop_DBus_Properties_get (DBusGProxy *proxy, const char * IN_interface, const char * IN_propname, GValue* OUT_value, GError **error)

{
  return dbus_g_proxy_call (proxy, "Get", error, G_TYPE_STRING, IN_interface, G_TYPE_STRING, IN_propname, G_TYPE_INVALID, G_TYPE_VALUE, OUT_value, G_TYPE_INVALID);
}

typedef void (*org_freedesktop_DBus_Properties_get_reply) (DBusGProxy *proxy, GValue OUT_value, GError *error, gpointer userdata);

static void
org_freedesktop_DBus_Properties_get_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  GValue OUT_value;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_VALUE, &OUT_value, G_TYPE_INVALID);
  (*(org_freedesktop_DBus_Properties_get_reply)data->cb) (proxy, OUT_value, error, data->userdata);
  return;
}

static
#ifdef G_HAVE_INLINE
inline
#endif
DBusGProxyCall*
org_freedesktop_DBus_Properties_get_async (DBusGProxy *proxy, const char * IN_interface, const char * IN_propname, org_freedesktop_DBus_Properties_get_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_new (DBusGAsyncData, 1);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "Get", org_freedesktop_DBus_Properties_get_async_callback, stuff, g_free, G_TYPE_STRING, IN_interface, G_TYPE_STRING, IN_propname, G_TYPE_INVALID);
}
static
#ifdef G_HAVE_INLINE
inline
#endif
gboolean
org_freedesktop_DBus_Properties_set (DBusGProxy *proxy, const char * IN_interface, const char * IN_propname, const GValue* IN_value, GError **error)

{
  return dbus_g_proxy_call (proxy, "Set", error, G_TYPE_STRING, IN_interface, G_TYPE_STRING, IN_propname, G_TYPE_VALUE, IN_value, G_TYPE_INVALID, G_TYPE_INVALID);
}

typedef void (*org_freedesktop_DBus_Properties_set_reply) (DBusGProxy *proxy, GError *error, gpointer userdata);

static void
org_freedesktop_DBus_Properties_set_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
  (*(org_freedesktop_DBus_Properties_set_reply)data->cb) (proxy, error, data->userdata);
  return;
}

static
#ifdef G_HAVE_INLINE
inline
#endif
DBusGProxyCall*
org_freedesktop_DBus_Properties_set_async (DBusGProxy *proxy, const char * IN_interface, const char * IN_propname, const GValue* IN_value, org_freedesktop_DBus_Properties_set_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_new (DBusGAsyncData, 1);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "Set", org_freedesktop_DBus_Properties_set_async_callback, stuff, g_free, G_TYPE_STRING, IN_interface, G_TYPE_STRING, IN_propname, G_TYPE_VALUE, IN_value, G_TYPE_INVALID);
}
#endif /* defined DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_DBus_Properties */

#ifndef DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_PowerManagement_Backlight
#define DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_PowerManagement_Backlight

static
#ifdef G_HAVE_INLINE
inline
#endif
gboolean
org_freedesktop_PowerManagement_Backlight_set_brightness (DBusGProxy *proxy, const guint IN_percentage_brightness, GError **error)

{
  return dbus_g_proxy_call (proxy, "SetBrightness", error, G_TYPE_UINT, IN_percentage_brightness, G_TYPE_INVALID, G_TYPE_INVALID);
}

typedef void (*org_freedesktop_PowerManagement_Backlight_set_brightness_reply) (DBusGProxy *proxy, GError *error, gpointer userdata);

static void
org_freedesktop_PowerManagement_Backlight_set_brightness_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
  (*(org_freedesktop_PowerManagement_Backlight_set_brightness_reply)data->cb) (proxy, error, data->userdata);
  return;
}

static
#ifdef G_HAVE_INLINE
inline
#endif
DBusGProxyCall*
org_freedesktop_PowerManagement_Backlight_set_brightness_async (DBusGProxy *proxy, const guint IN_percentage_brightness, org_freedesktop_PowerManagement_Backlight_set_brightness_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_new (DBusGAsyncData, 1);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "SetBrightness", org_freedesktop_PowerManagement_Backlight_set_brightness_async_callback, stuff, g_free, G_TYPE_UINT, IN_percentage_brightness, G_TYPE_INVALID);
}
static
#ifdef G_HAVE_INLINE
inline
#endif
gboolean
org_freedesktop_PowerManagement_Backlight_get_brightness (DBusGProxy *proxy, guint* OUT_percentage_brightness, GError **error)

{
  return dbus_g_proxy_call (proxy, "GetBrightness", error, G_TYPE_INVALID, G_TYPE_UINT, OUT_percentage_brightness, G_TYPE_INVALID);
}

typedef void (*org_freedesktop_PowerManagement_Backlight_get_brightness_reply) (DBusGProxy *proxy, guint OUT_percentage_brightness, GError *error, gpointer userdata);

static void
org_freedesktop_PowerManagement_Backlight_get_brightness_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  guint OUT_percentage_brightness;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_UINT, &OUT_percentage_brightness, G_TYPE_INVALID);
  (*(org_freedesktop_PowerManagement_Backlight_get_brightness_reply)data->cb) (proxy, OUT_percentage_brightness, error, data->userdata);
  return;
}

static
#ifdef G_HAVE_INLINE
inline
#endif
DBusGProxyCall*
org_freedesktop_PowerManagement_Backlight_get_brightness_async (DBusGProxy *proxy, org_freedesktop_PowerManagement_Backlight_get_brightness_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_new (DBusGAsyncData, 1);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "GetBrightness", org_freedesktop_PowerManagement_Backlight_get_brightness_async_callback, stuff, g_free, G_TYPE_INVALID);
}
#endif /* defined DBUS_GLIB_CLIENT_WRAPPERS_org_freedesktop_PowerManagement_Backlight */

G_END_DECLS
