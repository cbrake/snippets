/**
 * A simple test program to test using of the Value object over the
 * D-Bus.
 *
 * This maemo code example is licensed under a MIT-style license,
 * that can be found in the file called "License" in the same
 * directory as this file.
 * Copyright (c) 2007 Nokia Corporation. All rights reserved.
 *
 * It will first create a GLib/D-Bus proxy object connected to the
 * server's Value object, and then start firing away value set
 * methods.
 *
 * The methods are fired from a timer based callback once per second.
 * If the method calls fail (the ones that modify the values), the
 * program will still continue to run (so that the server can be
 * restarted if necessary).
 *
 * Also demonstrates listening to/catching of D-Bus signals (using the
 * GSignal mechanism, into which D-Bus signals are automatically
 * converted by the GLib-bindings.
 *
 * When value changed signals are received, will also request the
 * Value object for the current value and print that out.
 */

#include <glib.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <string.h> /* strcmp */

/* Pull the common symbolic defines. */
#include "common-defs.h"

/* Pull in the client stubs that were generated with
   dbus-binding-tool */
#include "value-client-stub.h"

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
 * Handles signals from Value-object when either value is outside
 * the thresholds (min or max).
 *
 * We use strcmp internally to differentiate between the values.
 * NOTE: This signal handler's parameters are "selected" by the server
 *       when it creates the signals, and filtered by the interface
 *       XML. Unfortunately dbus-binding-tool does not know how to
 *       enforce the argument specifications of signals (from XML),
 *       so you'll need to be careful to match this function with
 *       the exact signal creation (marshaling information).
 */
static void outOfRangeSignalHandler(DBusGProxy* proxy,
                                    const char* valueName,
                                    gpointer userData) {

  g_print(PROGNAME ":out-of-range (%s)!\n", valueName);
  if (strcmp(valueName, "value1") == 0) {
    g_print(PROGNAME ":out-of-range Value 1 is outside threshold\n");
  } else {
    g_print(PROGNAME ":out-of-range Value 2 is outside threshold\n");
  }
}

/**
 * Signal handler for the "changed" signals. These will be sent by the
 * Value-object whenever its contents change (whether within
 * thresholds or not).
 *
 * Like before, we use strcmp to differentiate between the two
 * values, and act accordingly (in this case by retrieving
 * synchronously the values using getvalue1 or getvalue2.
 *
 * NOTE: Since we use synchronous getvalues, it is possible to get
 *       this code stuck if for some reason the server would be stuck
 *       in an eternal loop.
 */
static void valueChangedSignalHandler(DBusGProxy* proxy,
                                      const char* valueName,
                                      gpointer userData) {
  /* Since method calls over D-Bus can fail, we'll need to check
     for failures. The server might be shut down in the middle of
     things, or might act badly in other ways. */
  GError* error = NULL;

  g_print(PROGNAME ":value-changed (%s)\n", valueName);

  /* Find out which value changed, and act accordingly. */
  if (strcmp(valueName, "value1") == 0) {
    gint v = 0;
    /* Execute the RPC to get value1. */
    org_maemo_Value_getvalue1(proxy, &v, &error);
    if (error == NULL) {
      g_print(PROGNAME ":value-changed Value1 now %d\n", v);
    } else {
      /* You could interrogate the GError further, to find out exactly
         what the error was, but in our case, we'll just ignore the
         error with the hope that some day (preferably soon), the
         RPC will succeed again (server comes back on the bus). */
      handleError("Failed to retrieve value1", error->message, FALSE);
    }
  } else {
    gdouble v = 0.0;
    org_maemo_Value_getvalue2(proxy, &v, &error);
    if (error == NULL) {
      g_print(PROGNAME ":value-changed Value2 now %.3f\n", v);
    } else {
      handleError("Failed to retrieve value2", error->message, FALSE);
    }
  }
  /* Free up error object if one was allocated. */
  g_clear_error(&error);
}

/**
 * This function will be called repeatedly from within the mainloop
 * timer launch code.
 *
 * The function will start with two statically initialized variables
 * (int and double) which will be incremented after each time this
 * function runs and will use the setvalue* remote methods to set the
 * new values. If the set methods fail, program is not aborted, but an
 * message will be issued to the user describing the error.
 *
 * It will purposefully start value2 from below the default minimum
 * threshold (set in the server code).
 *
 * NOTE: There is a design issue in the implementation in the Value
 *       object: it does not provide "adjust" method which would make
 *       it possible for multiple clients to adjust the values,
 *       instead of setting them separately. Now, if you launch
 *       multiple clients (at different times), the object internal
 *       values will end up fluctuating between the clients.
 */
static gboolean timerCallback(DBusGProxy* remoteobj) {

  /* Local values that we'll start updating to the remote object. */
  static gint localValue1 = -80;
  static gdouble localValue2 = -120.0;

  GError* error = NULL;

  /* Set the first value. */
  org_maemo_Value_setvalue1(remoteobj, localValue1, &error);
  if (error != NULL) {
    handleError("Failed to set value1", error->message, FALSE);
  } else {
    g_print(PROGNAME ":timerCallback Set value1 to %d\n", localValue1);
  }

  /* If there was an error with the first, release the error, and
     don't attempt the second time. Also, don't add to the local
     values. We assume that errors from the first set are caused by
     server going off the D-Bus, but are hopeful that it will come
     back, and hence keep trying (returning TRUE). */
  if (error != NULL) {
    g_clear_error(&error);
    return TRUE;
  }

  /* Now try to set the second value as well. */
  org_maemo_Value_setvalue2(remoteobj, localValue2, &error);
  if (error != NULL) {
    handleError("Failed to set value2", error->message, FALSE);
    g_clear_error(&error); /* Or g_error_free in this case. */
  } else {
    g_print(PROGNAME ":timerCallback Set value2 to %.3lf\n", localValue2);
  }

  /* Step the local values forward. */
  localValue1 += 10;
  localValue2 += 10.0;

  /* Tell the timer launcher that we want to remain on the timer
     call list in the future as well. Returning FALSE here would
     stop the launch of this timer callback. */
  return TRUE;
}

/**
 * The test program itself.
 *
 * 1) Setup GType/GSignal
 * 2) Create GMainLoop object
 * 3) Connect to the Session D-Bus
 * 4) Create a proxy GObject for the remote Value object
 * 5) Register signals that we're interested from the Value object
 * 6) Register signal handlers for them
 * 7) Start a timer that will launch timerCallback once per second.
 * 8) Run main-loop (forever)
 */
int main(int argc, char** argv) {
  /* The D-Bus connection object. Provided by GLib/D-Bus wrappers. */
  DBusGConnection* bus;
  /* This will represent the Value object locally (acting as a proxy
     for all method calls and signal delivery. */
  DBusGProxy* remoteValue;
  /* This will refer to the GMainLoop object */
  GMainLoop* mainloop;
  GError* error = NULL;

  /* Initialize the GType/GObject system. */
  g_type_init();

  /* Create a new GMainLoop with default context (NULL) and initial
     state of "not running" (FALSE). */
  mainloop = g_main_loop_new(NULL, FALSE);
  /* Failure to create the main loop is fatal (for us). */
  if (mainloop == NULL) {
    handleError("Failed to create the mainloop", "Unknown (OOM?)",
                TRUE);
  }

  g_print(PROGNAME ":main Connecting to Session D-Bus.\n");
  bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
  if (error != NULL) {
    handleError("Couldn't connect to the Session bus", error->message,
                TRUE);
    /* Normally you'd have to also g_error_free() the error object
       but since the program will terminate within handleError,
       it is not necessary here. */
  }

  g_print(PROGNAME ":main Creating a GLib proxy object for Value.\n");

  /* Create the proxy object that we'll be using to access the object
     on the server. If you would use dbus_g_proxy_for_name_owner(),
     you would be also notified when the server that implements the
     object is removed (or rather, the interface is removed). Since
     we don't care who actually implements the interface, we'll use the
     more common function. See the API documentation at
     http://maemo.org/api_refs/4.0/dbus/ for more details. */
  remoteValue =
    dbus_g_proxy_new_for_name(bus,
                              VALUE_SERVICE_NAME, /* name */
                              VALUE_SERVICE_OBJECT_PATH, /* obj path */
                              VALUE_SERVICE_INTERFACE /* interface */);
  if (remoteValue == NULL) {
    handleError("Couldn't create the proxy object",
                "Unknown(dbus_g_proxy_new_for_name)", TRUE);
  }

  /* Register the signatures for the signal handlers.
     In our case, we'll have one string parameter passed to use along
     the signal itself. The parameter list is terminated with
     G_TYPE_INVALID (i.e., the GType for string objects. */

  g_print(PROGNAME ":main Registering signal handler signatures.\n");

  /* Add the argument signatures for the signals (needs to be done
     before connecting the signals). This might go away in the future,
     when the GLib-bindings will do automatic introspection over the
     D-Bus, but for now we need the registration phase. */
  { /* Create a local scope for variables. */

    int i;
    const gchar* signalNames[] = { SIGNAL_CHANGED_VALUE1,
                                   SIGNAL_CHANGED_VALUE2,
                                   SIGNAL_OUTOFRANGE_VALUE1,
                                   SIGNAL_OUTOFRANGE_VALUE2 };
    /* Iterate over all the entries in the above array.
       The upper limit for i might seem strange at first glance,
       but is quite common idiom to extract the number of elements
       in a statically allocated arrays in C.
       NOTE: The idiom will not work with dynamically allocated
             arrays. (Or rather it will, but the result is probably
             not what you expect.) */
    for (i = 0; i < sizeof(signalNames)/sizeof(signalNames[0]); i++) {
      /* Since the function doesn't return anything, we cannot check
         for errors here. */
      dbus_g_proxy_add_signal(/* Proxy to use */
                              remoteValue,
                              /* Signal name */
                              signalNames[i],
                              /* Will receive one string argument */
                              G_TYPE_STRING,
                              /* Termination of the argument list */
                              G_TYPE_INVALID);
    }
  } /* end of local scope */

  g_print(PROGNAME ":main Registering D-Bus signal handlers.\n");

  /* We connect each of the following signals one at a time,
     since we'll be using two different callbacks. */

  /* Again, no return values, cannot hence check for errors. */
  dbus_g_proxy_connect_signal(/* Proxy object */
                              remoteValue,
                              /* Signal name */
                              SIGNAL_CHANGED_VALUE1,
                              /* Signal handler to use. Note that the
                                 typecast is just to make the compiler
                                 happy about the function, since the
                                 prototype is not compatible with
                                 regular signal handlers. */
                              G_CALLBACK(valueChangedSignalHandler),
                              /* User-data (we don't use any). */
                              NULL,
                              /* GClosureNotify function that is
                                 responsible in freeing the passed
                                 user-data (we have no data). */
                              NULL);

  dbus_g_proxy_connect_signal(remoteValue, SIGNAL_CHANGED_VALUE2,
                              G_CALLBACK(valueChangedSignalHandler),
                              NULL, NULL);

  dbus_g_proxy_connect_signal(remoteValue, SIGNAL_OUTOFRANGE_VALUE1,
                              G_CALLBACK(outOfRangeSignalHandler),
                              NULL, NULL);

  dbus_g_proxy_connect_signal(remoteValue, SIGNAL_OUTOFRANGE_VALUE2,
                              G_CALLBACK(outOfRangeSignalHandler),
                              NULL, NULL);

  /* All signals are now registered and we're ready to handle them. */

  g_print(PROGNAME ":main Starting main loop (first timer in 1s).\n");

  /* Register a timer callback that will do RPC sets on the values.
     The userdata pointer is used to pass the proxy object to the
     callback so that it can launch modifications to the object. */
  g_timeout_add(1000, (GSourceFunc)timerCallback, remoteValue);

  /* Run the program. */
  g_main_loop_run(mainloop);
  /* Since the main loop is not stopped (by this code), we shouldn't
     ever get here. The program might abort() for other reasons. */

  /* If it does, return failure as exit code. */
  return EXIT_FAILURE;
}

