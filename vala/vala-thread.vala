// valac --thread vala-thread.vala

void* thread_func() {
    stdout.printf("Thread running.\n");
    return null;
}

int main(string[] args) {
    if (!Thread.supported()) {
        stderr.printf("Cannot run without threads.\n");
        return 1;
    }

    try {
        unowned Thread<void*> thread = Thread.create<void*>(thread_func, false);
        thread.join();
    } catch (ThreadError e) {
        return 1;
    }

    return 0;
}

/*
class Demo.HelloWorld : GLib.Object {




    public static int main(string[] args) {

        stdout.printf("Hello, World\n");

        return 0;
    }
}
*/


