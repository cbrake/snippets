/* DBus in Vala sample code */

// valac --pkg dbus-glib-1 -o dbussample DBusSample.vala

using GLib;
using DBus;

public class DBusSample : GLib.Object {

    private DBus.Connection conn;
    private dynamic DBus.Object proxy;

    public void run () throws DBus.Error, GLib.Error {
        // remove the space before SESSION, it is only required for this wiki
        conn = DBus.Bus.get (DBus.BusType.SESSION);

        //purple = conn.get_object ("im.pidgin.purple.PurpleService", "/im/pidgin/purple/PurpleObject", "im.pidgin.purple.PurpleInterface");
        proxy = conn.get_object ("com.example.SampleService", "/SomeObject", "com.example.SampleInterface");

        // async dbus call
        //backlight.GetBrightness (getall_reply);
        //proxy.Exit();
        proxy.GetDict(getdict_reply);

        // dbus signals
        proxy.ReceivedImMsg += msg_received;
    }

    private void msg_received (dynamic DBus.Object backlight, int dummy1, string sender, string message_, int dummy2, uint dummy3) {
        // dbus signal handler

        message ("Message received %s %s", sender, message_);
    }

    private void getdict_reply(HashTable h)
    {

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
