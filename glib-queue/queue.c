
// gcc -o queue `pkg-config --cflags --libs glib-2.0` queue.c

#include <glib.h>
#include <stdio.h>

int main()
{
	GQueue * q = g_queue_new();

	g_queue_push_tail(q, GUINT_TO_POINTER(0));
	g_queue_push_tail(q, GUINT_TO_POINTER(1));
	g_queue_push_tail(q, GUINT_TO_POINTER(2));
	g_queue_push_tail(q, GUINT_TO_POINTER(3));
	g_queue_push_tail(q, GUINT_TO_POINTER(4));

	int i;

	for (i=0; i < g_queue_get_length(q); i++) {
		printf("value at index %i = %i\n", i,
				GPOINTER_TO_UINT(g_queue_peek_nth(q, i)));
	}

	return 0;
}

// this program outputs
// value at index 0 = 0
// value at index 1 = 1
// value at index 2 = 2
// value at index 3 = 3
// value at index 4 = 4
//
// from this, we can assume that its intended for stuff to be pushed onto the
// tail, and popped off the head if we want the FIFO type behavior.  Index 0
// for peek_nth starts at the oldest value, and progresses to the newest.



