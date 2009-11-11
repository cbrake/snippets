/* DBus in Vala sample code */

// valac --pkg dbus-glib-1 -o dbussample DBusSample.vala

using GLib;
using DBus;

public class DBusSample : GLib.Object {

    private DBus.Connection conn;
    private dynamic DBus.Object backlight;

    public void run () throws DBus.Error, GLib.Error {
        // remove the space before SESSION, it is only required for this wiki
        conn = DBus.Bus.get (DBus.BusType.SESSION);

        //purple = conn.get_object ("im.pidgin.purple.PurpleService", "/im/pidgin/purple/PurpleObject", "im.pidgin.purple.PurpleInterface");
        backlight = conn.get_object ("org.freedesktop.PowerManagement", "/org/freedesktop/PowerManagement/Backlight", "org.freedesktop.PowerManagement");

        // async dbus call
        backlight.GetBrightness (getbrightness_reply);

        // dbus signals
        backlight.ReceivedImMsg += msg_received;
    }

    private void msg_received (dynamic DBus.Object backlight, int dummy1, string sender, string message_, int dummy2, uint dummy3) {
        // dbus signal handler

        message ("Message received %s %s", sender, message_);
    }

    private void getbrightness_reply(int brightness, GLib.Error e) {
        message("CLIFF: getbrightness_reply, brightness = %i", brightness);
    }

    private void getall_reply (int brightness, GLib.Error e) {
        // callback for async dbus call
        if (e != null) {
            critical (e.message);
            return;
        }

        message ("Brightness");
        /*
        try {
            foreach (int id in ids) {
                // sync dbus call
                string s = purple.PurpleAccountGetUsername (id);
                message ("Account %s", s);
            }
        } catch (DBus.Error dbus_error) {
            critical (dbus_error.message);
        }
        */
    }

    static int main (string[] args) {
        var loop = new MainLoop (null, false);

        var test = new DBusSample ();
        try {
            test.run ();
        } catch (DBus.Error e) {
            stderr.printf ("Failed to initialise");
            return 1;
        } catch {
            stderr.printf ("Dynamic method failure");
            return 1;
        }

        loop.run ();

        return 0;
    }
}
