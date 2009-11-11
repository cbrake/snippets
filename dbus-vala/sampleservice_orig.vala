using GLib;

[DBus (name = "org.gnome.TestServer")]
public class TestServer1 : Object {
        int64 counter;

        public int64 ping (string msg) {
                message (msg);
                return counter++;
        }
}

[DBus (name = "org.gnome.TestServer")]
public class TestServer2 : Object {
        int64 counter;

        public int64 ping (string msg) {
                message (msg);
                return counter++;
        }
}


void main () {
        MainLoop loop = new MainLoop (null, false);

        try {
                var conn = DBus.Bus.get (DBus.BusType. SESSION);

                dynamic DBus.Object bus = conn.get_object (
                        "org.freedesktop.DBus", "/org/freedesktop/DBus", "org.freedesktop.DBus");
        
                // try to register service in session bus
                uint request_name_result = bus.request_name ("org.gnome.TestService", (uint) 0);

                if (request_name_result == DBus.RequestNameReply.PRIMARY_OWNER) {
                        // start server

                        var server1 = new TestServer1 ();
                        var server2 = new TestServer2 ();
                        conn.register_object ("/org/gnome/test1", server1);
                        conn.register_object ("/org/gnome/test2", server2);

                        loop.run ();
                } else {        
                        // client       
                        dynamic DBus.Object test_server_object = conn.get_object ("org.gnome.TestService", "/org/gnome/test", "org.gnome.TestServer");

                        int64 pong = test_server_object.ping ("Hello from Vala");
                        message (pong.to_string ());
                }
        } catch (Error foo) {
                stderr.printf("Oops %s\n", foo.message);
        }
}
