/**
 * This program implements a GObject for a simple class, then
 * registers the object on the D-Bus and starts serving requests.
 *
 * This maemo code example is licensed under a MIT-style license,
 * that can be found in the file called "License" in the same
 * directory as this file.
 * Copyright (c) 2007 Nokia Corporation. All rights reserved.
 *
 * In more complicated code, the GObject definition, implementation
 * and D-Bus registration would all live in separate files. In this
 * server, they're all present in this file.
 *
 * This program will pull the automatically generated D-Bus/GLib stub
 * code (which contains the marshaling code as well as a binding/call
 * table.
 *
 * This program also might serve as an introduction into implementing
 * custom GType/GObjects, but it is not the primary purpose here.
 * Important things like object life-time management (freeing of
 * objects), sub-classing and GObject properties are not covered at
 * all.
 *
 * Demonstrates a simple implementation of "tracing" as well (via the
 * NO_DAEMON define, as when built as non-daemonizing version, will
 * output information about what is happening and where. Adding
 * timestamps to each trace message is left out (see gettimeofday()
 * system call for a simple solution).
 */

#include <glib.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <unistd.h> /* daemon */

/* Pull symbolic constants that are shared (in this example) between
   the client and the server. */
#include "common-defs.h"

/**
 * Define enumerations for the different signals that we can generate
 * (so that we can refer to them within the signals-array [below]
 * using symbolic names). These are not the same as the signal name
 * strings.
 *
 * NOTE: E_SIGNAL_COUNT is NOT a signal enum. We use it as a
 *       convenient constant giving the number of signals defined so
 *       far. It needs to be listed last.
 */
typedef enum {
  E_SIGNAL_CHANGED_VALUE1,
  E_SIGNAL_CHANGED_VALUE2,
  E_SIGNAL_OUTOFRANGE_VALUE1,
  E_SIGNAL_OUTOFRANGE_VALUE2,
  E_SIGNAL_COUNT
} ValueSignalNumber;

typedef struct {
  /* The parent class object state. */
  GObject parent;
  /* Our first per-object state variable. */
  gint value1;
  /* Our second per-object state variable. */
  gdouble value2;
} ValueObject;

typedef struct {
  /* The parent class state. */
  GObjectClass parent;
  /* The minimum number under which values will cause signals to be
     emitted. */
  gint thresholdMin;
  /* The maximum number over which values will cause signals to be
     emitted. */
  gint thresholdMax;
  /* Signals created for this class. */
  guint signals[E_SIGNAL_COUNT];
} ValueObjectClass;

/* Forward declaration of the function that will return the GType of
   the Value implementation. Not used in this program. */
GType value_object_get_type(void);

/* Macro for the above. It is common to define macros using the
   naming convention (seen below) for all GType implementations,
   and that's why we're going to do that here as well. */
#define VALUE_TYPE_OBJECT              (value_object_get_type())

#define VALUE_OBJECT(object) \
        (G_TYPE_CHECK_INSTANCE_CAST ((object), \
         VALUE_TYPE_OBJECT, ValueObject))
#define VALUE_OBJECT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), \
         VALUE_TYPE_OBJECT, ValueObjectClass))
#define VALUE_IS_OBJECT(object) \
        (G_TYPE_CHECK_INSTANCE_TYPE ((object), \
         VALUE_TYPE_OBJECT))
#define VALUE_IS_OBJECT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE ((klass), \
         VALUE_TYPE_OBJECT))
#define VALUE_OBJECT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj), \
         VALUE_TYPE_OBJECT, ValueObjectClass))

G_DEFINE_TYPE(ValueObject, value_object, G_TYPE_OBJECT)

/**
 * Since the stub generator will reference the functions from a call
 * table, the functions must be declared before the stub is included.
 */
gboolean value_object_getvalue1(ValueObject* obj, gint* value_out,
                                                  GError** error);
gboolean value_object_getvalue2(ValueObject* obj, gdouble* value_out,
                                                  GError** error);
gboolean value_object_setvalue1(ValueObject* obj, gint value_in,
                                                  GError** error);
gboolean value_object_setvalue2(ValueObject* obj, gdouble value_in,
                                                  GError** error);

/**
 * Pull in the stub for the server side.
 */
#include "value-server-stub.h"

/* A small macro that will wrap g_print and expand to empty when
   server will daemonize. We use this to add debugging info on
   the server side, but if server will be daemonized, it doesn't
   make sense to even compile the code in.

   The macro is quite "hairy", but very convenient. */
#ifdef NO_DAEMON
#define dbg(fmtstr, args...) \
  (g_print(PROGNAME ":%s: " fmtstr "\n", __func__, ##args))
#else
#define dbg(dummy...)
#endif

/**
 * Per object initializer
 *
 * Only sets up internal state (both values set to zero)
 */
static void value_object_init(ValueObject* obj) {
  dbg("Called");
  g_assert(obj != NULL);
  obj->value1 = 0;
  obj->value2 = 0.0;
}

/**
 * Per class initializer
 *
 * Sets up the thresholds (-100 .. 100), creates the signals that we
 * can emit from any object of this class and finally registers the
 * type into the GLib/D-Bus wrapper so that it may add its own magic.
 */
static void value_object_class_init(ValueObjectClass* klass) {

  /* Since all signals have the same prototype (each will get one
     string as a parameter), we create them in a loop below. The only
     difference between them is the index into the klass->signals
     array, and the signal name.

     Since the index goes from 0 to E_SIGNAL_COUNT-1, we just specify
     the signal names into an array and iterate over it.

     Note that the order here must correspond to the order of the
     enumerations before. */
  const gchar* signalNames[E_SIGNAL_COUNT] = {
    SIGNAL_CHANGED_VALUE1,
    SIGNAL_CHANGED_VALUE2,
    SIGNAL_OUTOFRANGE_VALUE1,
    SIGNAL_OUTOFRANGE_VALUE2 };
  /* Loop variable */
  int i;

  dbg("Called");
  g_assert(klass != NULL);

  /* Setup sane minimums and maximums for the thresholds. There is no
     way to change these afterwards (currently), so you can consider
     them as constants. */
  klass->thresholdMin = -100;
  klass->thresholdMax = 100;

  dbg("Creating signals");

  /* Create the signals in one loop, since they all are similar
     (except for the names). */
  for (i = 0; i < E_SIGNAL_COUNT; i++) {
    guint signalId;

    /* Most of the time you will encounter the following code without
       comments. This is why all the parameters are documented
       directly below. */
    signalId =
      g_signal_new(signalNames[i], /* str name of the signal */
                   /* GType to which signal is bound to */
                   G_OBJECT_CLASS_TYPE(klass),
                   /* Combination of GSignalFlags which tell the
                      signal dispatch machinery how and when to
                      dispatch this signal. The most common is the
                      G_SIGNAL_RUN_LAST specification. */
                   G_SIGNAL_RUN_LAST,
                   /* Offset into the class structure for the type
                      function pointer. Since we're implementing a
                      simple class/type, we'll leave this at zero. */
                   0,
                   /* GSignalAccumulator to use. We don't need one. */
                   NULL,
                   /* User-data to pass to the accumulator. */
                   NULL,
                   /* Function to use to marshal the signal data into
                      the parameters of the signal call. Luckily for
                      us, GLib (GCClosure) already defines just the
                      function that we want for a signal handler that
                      we don't expect any return values (void) and
                      one that will accept one string as parameter
                      (besides the instance pointer and pointer to
                      user-data).

                      If no such function would exist, you would need
                      to create a new one (by using glib-genmarshal
                      tool). */
                   g_cclosure_marshal_VOID__STRING,
                   /* Return GType of the return value. The handler
                      does not return anything, so we use G_TYPE_NONE
                      to mark that. */
                   G_TYPE_NONE,
                   /* Number of parameter GTypes to follow. */
                   1,
                   /* GType(s) of the parameters. We only have one. */
                   G_TYPE_STRING);
    /* Store the signal Id into the class state, so that we can use
       it later. */
    klass->signals[i] = signalId;

    /* Proceed with the next signal creation. */
  }
  /* All signals created. */

  dbg("Binding to GLib/D-Bus");

  /* Time to bind this GType into the GLib/D-Bus wrappers.
     NOTE: This is not yet "publishing" the object on the D-Bus, but
           since it is only allowed to do this once per class
           creation, the safest place to put it is in the class
           initializer.
           Specifically, this function adds "method introspection
           data" to the class so that methods can be called over
           the D-Bus. */
  dbus_g_object_type_install_info(VALUE_TYPE_OBJECT,
                                 &dbus_glib_value_object_object_info);

  dbg("Done");
  /* All done. Class is ready to be used for instantiating objects */
}

/**
 * Utility helper to emit a signal given with internal enumeration and
 * the passed string as the signal data.
 *
 * Used in the setter functions below.
 */
static void value_object_emitSignal(ValueObject* obj,
                                    ValueSignalNumber num,
                                    const gchar* message) {

  /* In order to access the signal identifiers, we need to get a hold
     of the class structure first. */
  ValueObjectClass* klass = VALUE_OBJECT_GET_CLASS(obj);

  /* Check that the given num is valid (abort if not).
     Given that this file is the module actually using this utility,
     you can consider this check superfluous (but useful for
     development work). */
  g_assert((num < E_SIGNAL_COUNT) && (num >= 0));

  dbg("Emitting signal id %d, with message '%s'", num, message);

  /* This is the simplest way of emitting signals. */
  g_signal_emit(/* Instance of the object that is generating this
                   signal. This will be passed as the first parameter
                   to the signal handler (eventually). But obviously
                   when speaking about D-Bus, a signal caught on the
                   other side of D-Bus will be first processed by
                   the GLib-wrappers (the object proxy) and only then
                   processed by the signal handler. */
                obj,
                /* Signal id for the signal to generate. These are
                   stored inside the class state structure. */
                klass->signals[num],
                /* Detail of signal. Since we are not using detailed
                   signals, we leave this at zero (default). */
                0,
                /* Data to marshal into the signal. In our case it's
                   just one string. */
                message);
  /* g_signal_emit returns void, so we cannot check for success. */

  /* Done emitting signal. */
}

/**
 * Utility to check the given integer against the thresholds.
 * Will return TRUE if thresholds are not exceeded, FALSE otherwise.
 *
 * Used in the setter functions below.
 */
static gboolean value_object_thresholdsOk(ValueObject* obj,
                                          gint value) {

  /* Thresholds are in class state data, get access to it */
  ValueObjectClass* klass = VALUE_OBJECT_GET_CLASS(obj);

  return ((value >= klass->thresholdMin) &&
          (value <= klass->thresholdMax));
}

/**
 * Function that gets called when someone tries to execute "setvalue1"
 * over the D-Bus. (Actually the marshalling code from the stubs gets
 * executed first, but they will eventually execute this function.)
 *
 * NOTE: If you change the name of this function, the generated
 *       stubs will no longer find it! On the other hand, if you
 *       decide to modify the interface XML, this is one of the places
 *       that you'll have to modify as well.
 *       This applies to the next four functions (including this one).
 */
gboolean value_object_setvalue1(ValueObject* obj, gint valueIn,
                                                  GError** error) {

  dbg("Called (valueIn=%d)", valueIn);

  g_assert(obj != NULL);

  /* Compare the current value against old one. If they're the same,
     we don't need to do anything (except return success). */
  if (obj->value1 != valueIn) {
    /* Change the value. */
    obj->value1 = valueIn;

    /* Emit the "changed_value1" signal. */
    value_object_emitSignal(obj, E_SIGNAL_CHANGED_VALUE1, "value1");

    /* If new value falls outside the thresholds, emit
       "outofrange_value1" signal as well. */
    if (!value_object_thresholdsOk(obj, valueIn)) {
      value_object_emitSignal(obj, E_SIGNAL_OUTOFRANGE_VALUE1,
                                   "value1");
    }
  }
  /* Return success to GLib/D-Bus wrappers. In this case we don't need
     to touch the supplied error pointer-pointer. */
  return TRUE;
}

/**
 * Function that gets executed on "setvalue2".
 * Other than this function operating with different type input
 * parameter (and different internal value), all the comments from
 * set_value1 apply here as well.
 */
gboolean value_object_setvalue2(ValueObject* obj, gdouble valueIn,
                                                  GError** error) {

  dbg("Called (valueIn=%.3f)", valueIn);

  g_assert(obj != NULL);

  /* Normally comparing doubles against other doubles is a bad idea,
     since multiple values can "collide" into one binary
     representation. In our case, it is not a real problem, as we're
     not interested in numeric comparison, but testing whether the
     binary content is about to change. Also, as the value has been
     sent by client over the D-Bus, it has already been reduced. */
  if (obj->value2 != valueIn) {
    obj->value2 = valueIn;

    value_object_emitSignal(obj, E_SIGNAL_CHANGED_VALUE2, "value2");

    if (!value_object_thresholdsOk(obj, valueIn)) {
      value_object_emitSignal(obj, E_SIGNAL_OUTOFRANGE_VALUE2,
                                   "value2");
    }
  }
  return TRUE;
}

/**
 * Function that gets executed on "getvalue1".
 * We don't signal the get operations, so this will be simple.
 */
gboolean value_object_getvalue1(ValueObject* obj, gint* valueOut,
                                                  GError** error) {

  dbg("Called (internal value1 is %d)", obj->value1);

  g_assert(obj != NULL);

  /* Check that the target pointer is not NULL.
     Even is the only caller for this will be the GLib-wrapper code,
     we cannot trust the stub generated code and should handle the
     situation. We will terminate with an error in this case.

     Another option would be to create a new GError, and store
     the error condition there. */
  g_assert(valueOut != NULL);

  /* Copy the current first value to caller specified memory. */
  *valueOut = obj->value1;

  /* Return success. */
  return TRUE;
}

/**
 * Function that gets executed on "getvalue2".
 * (Again, similar to "getvalue1").
 */
gboolean value_object_getvalue2(ValueObject* obj, gdouble* valueOut,
                                                  GError** error) {
  dbg("Called (internal value2 is %.3f)", obj->value2);

  g_assert(obj != NULL);
  g_assert(valueOut != NULL);

  *valueOut = obj->value2;
  return TRUE;
}

/**
 * Print out an error message and optionally quit (if fatal is TRUE)
 */
static void handleError(const char* msg, const char* reason,
                                         gboolean fatal) {
  g_printerr(PROGNAME ": ERROR: %s (%s)\n", msg, reason);
  if (fatal) {
    exit(EXIT_FAILURE);
  }
}

/**
 * The main server code
 *
 * 1) Init GType/GObject
 * 2) Create a mainloop
 * 3) Connect to the Session bus
 * 4) Get a proxy object representing the bus itself
 * 5) Register the well-known name by which clients can find us.
 * 6) Create one Value object that will handle all client requests.
 * 7) Register it on the bus (will be found via "/GlobalValue" object
 *    path)
 * 8) Daemonize the process (if not built with NO_DAEMON)
 * 9) Start processing requests (run GMainLoop)
 *
 * This program will not exit (unless it encounters critical errors).
 */
int main(int argc, char** argv) {
  /* The GObject representing a D-Bus connection. */
  DBusGConnection* bus = NULL;
  /* Proxy object representing the D-Bus service object. */
  DBusGProxy* busProxy = NULL;
  /* Will hold one instance of ValueObject that will serve all the
     requsts. */
  ValueObject* valueObj = NULL;
  /* GMainLoop for our program. */
  GMainLoop* mainloop = NULL;
  /* Will store the result of the RequestName RPC here. */
  guint result;
  GError* error = NULL;

  /* Initialize the GType/GObject system. */
  g_type_init();

  /* Create a main loop that will dispatch callbacks. */
  mainloop = g_main_loop_new(NULL, FALSE);
  if (mainloop == NULL) {
    /* Print error and terminate. */
    handleError("Couldn't create GMainLoop", "Unknown(OOM?)", TRUE);
  }

  g_print(PROGNAME ":main Connecting to the Session D-Bus.\n");
  bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
  if (error != NULL) {
    /* Print error and terminate. */
    handleError("Couldn't connect to session bus", error->message, TRUE);
  }

  g_print(PROGNAME ":main Registering the well-known name (%s)\n",
    VALUE_SERVICE_NAME);

  /* In order to register a well-known name, we need to use the
     "RequestMethod" of the /org/freedesktop/DBus interface. Each
     bus provides an object that will implement this interface.

     In order to do the call, we need a proxy object first.
     DBUS_SERVICE_DBUS = "org.freedesktop.DBus"
     DBUS_PATH_DBUS = "/org/freedesktop/DBus"
     DBUS_INTERFACE_DBUS = "org.freedesktop.DBus" */
  busProxy = dbus_g_proxy_new_for_name(bus,
                                       DBUS_SERVICE_DBUS,
                                       DBUS_PATH_DBUS,
                                       DBUS_INTERFACE_DBUS);
  if (busProxy == NULL) {
    handleError("Failed to get a proxy for D-Bus",
                "Unknown(dbus_g_proxy_new_for_name)", TRUE);
  }

  /* Attempt to register the well-known name.
     The RPC call requires two parameters:
     - arg0: (D-Bus STRING): name to request
     - arg1: (D-Bus UINT32): flags for registration.
       (please see "org.freedesktop.DBus.RequestName" in
        http://dbus.freedesktop.org/doc/dbus-specification.html)
     Will return one uint32 giving the result of the RPC call.
     We're interested in 1 (we're now the primary owner of the name)
     or 4 (we were already the owner of the name, however in this
     application it wouldn't make much sense).

     The function will return FALSE if it sets the GError. */
  if (!dbus_g_proxy_call(busProxy,
                         /* Method name to call. */
                         "RequestName",
                         /* Where to store the GError. */
                         &error,
                         /* Parameter type of argument 0. Note that
                            since we're dealing with GLib/D-Bus
                            wrappers, you will need to find a suitable
                            GType instead of using the "native" D-Bus
                            type codes. */
                         G_TYPE_STRING,
                         /* Data of argument 0. In our case, this is
                            the well-known name for our server
                            example ("org.maemo.Platdev_ex"). */
                         VALUE_SERVICE_NAME,
                         /* Parameter type of argument 1. */
                         G_TYPE_UINT,
                         /* Data of argument 0. This is the "flags"
                            argument of the "RequestName" method which
                            can be use to specify what the bus service
                            should do when the name already exists on
                            the bus. We'll go with defaults. */
                         0,
                         /* Input arguments are terminated with a
                            special GType marker. */
                         G_TYPE_INVALID,
                         /* Parameter type of return value 0.
                            For "RequestName" it is UINT32 so we pick
                            the GType that maps into UINT32 in the
                            wrappers. */
                         G_TYPE_UINT,
                         /* Data of return value 0. These will always
                            be pointers to the locations where the
                            proxy can copy the results. */
                         &result,
                         /* Terminate list of return values. */
                         G_TYPE_INVALID)) {
    handleError("D-Bus.RequestName RPC failed", error->message,
                                                TRUE);
    /* Note that the whole call failed, not "just" the name
       registration (we deal with that below). This means that
       something bad probably has happened and there's not much we can
       do (hence program termination). */
  }
  /* Check the result code of the registration RPC. */
  g_print(PROGNAME ":main RequestName returned %d.\n", result);
  if (result != 1) {
    handleError("Failed to get the primary well-known name.",
                "RequestName result != 1", TRUE);
    /* In this case we could also continue instead of terminating.
       We could retry the RPC later. Or "lurk" on the bus waiting for
       someone to tell us what to do. If we would be publishing
       multiple services and/or interfaces, it even might make sense
       to continue with the rest anyway.

       In our simple program, we terminate. Not much left to do for
       this poor program if the clients won't be able to find the
       Value object using the well-known name. */
  }

  g_print(PROGNAME ":main Creating one Value object.\n");
  /* The NULL at the end means that we have stopped listing the
     property names and their values that would have been used to
     set the properties to initial values. Our simple Value
     implementation does not support GObject properties, and also
     doesn't inherit anything interesting from GObject directly, so
     there are no properties to set. For more examples on properties
     see the first GTK+ example programs from the Application
     Development material.

     NOTE: You need to keep at least one reference to the published
           object at all times, unless you want it to disappear from
           the D-Bus (implied by API reference for
           dbus_g_connection_register_g_object(). */
  valueObj = g_object_new(VALUE_TYPE_OBJECT, NULL);
  if (valueObj == NULL) {
    handleError("Failed to create one Value instance.",
                "Unknown(OOM?)", TRUE);
  }

  g_print(PROGNAME ":main Registering it on the D-Bus.\n");
  /* The function does not return any status, so can't check for
     errors here. */
  dbus_g_connection_register_g_object(bus,
                                      VALUE_SERVICE_OBJECT_PATH,
                                      G_OBJECT(valueObj));

  g_print(PROGNAME ":main Ready to serve requests (daemonizing).\n");

#ifndef NO_DAEMON

  /* This will attempt to daemonize this process. It will switch this
     process' working directory to / (chdir) and then reopen stdin,
     stdout and stderr to /dev/null. Which means that all printouts
     that would occur after this, will be lost. Obviously the
     daemonization will also detach the process from the controlling
     terminal as well. */
  if (daemon(0, 0) != 0) {
    g_error(PROGNAME ": Failed to daemonize.\n");
  }
#else
  g_print(PROGNAME
          ": Not daemonizing (built with NO_DAEMON-build define)\n");
#endif

  /* Start service requests on the D-Bus forever. */
  g_main_loop_run(mainloop);
  /* This program will not terminate unless there is a critical
     error which will cause abort() to be used. Hence it will never
     reach this point. */

  /* If it does, return failure exit code just in case. */
  return EXIT_FAILURE;
}

