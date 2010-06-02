/* test results
 *   - timed queue pops break if the system time changes.
 *   - g_usleep generally seem to be ok.
 */


#include <glib.h>
#include <glib/gstdio.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float time_diff(struct timespec * start, struct timespec * end)
{
  float elapsed_seconds;
  elapsed_seconds = (float)((end->tv_sec - start->tv_sec) + 
    (end->tv_nsec - start->tv_nsec)/(1e9));

  return elapsed_seconds;
}

float g_time_diff(GTimeVal * start, GTimeVal * end)
{
  float elapsed_seconds;
  elapsed_seconds = (gfloat)((end->tv_sec - start->tv_sec) + 
    (end->tv_usec - start->tv_usec)/(1e6));

  return elapsed_seconds;
}


struct timespec start, end;
float delay_measured;

static gboolean callback(gpointer data)
{
  g_debug("Callback called");
  clock_gettime(CLOCK_MONOTONIC, &end);
  delay_measured = time_diff(&start, &end);

  g_debug("measured delay = %fs", delay_measured);

  memcpy(&start, &end, sizeof(start));

  return TRUE;
}

static gboolean test_queue(gpointer data)
{
  GAsyncQueue * q;
  GTimeVal t1, t2;

  struct timespec q_start, q_end;
  float q_delay_measured;

  g_debug("Test queue delay");

  q = g_async_queue_new();
  g_get_current_time(&t1);
  memcpy(&t2, &t1, sizeof(t2));
  g_debug("sleeping 5 seconds");
  g_usleep(5*1000*1000);
  g_time_val_add(&t2, 10 * 1000 * 1000);
  g_debug("queue timed pop 10 seconds");
  g_async_queue_timed_pop(q, &t2);
  clock_gettime(CLOCK_MONOTONIC, &end);
  g_get_current_time(&t2);
  delay_measured = time_diff(&start, &end);

  g_debug("queue MONOTONIC clock measured delay = %fs\n", delay_measured);
  g_debug("g_get_current_time measured delay = %fs\n", g_time_diff(&t1, &t2));

  return FALSE;
}

main ()
{

#if 0
  g_debug("test g_usleep");
  clock_gettime(CLOCK_MONOTONIC, &start);
  g_debug("Delay 10 seconds");
  g_usleep(10 * 1000 * 1000);
  clock_gettime(CLOCK_MONOTONIC, &end);

  delay_measured = time_diff(&start, &end);

  g_debug("measured delay = %fs", delay_measured);

#endif

  g_debug("g_async_queue_timed_pop");

  GMainLoop * loop;

  g_thread_init(NULL);
  loop = g_main_loop_new(NULL, FALSE);
  g_debug("Starting main loop");
  g_timeout_add(1000, callback, NULL);
  g_timeout_add(1, test_queue, NULL);
  clock_gettime(CLOCK_MONOTONIC, &start);
  g_debug("monotonic time s = %i, ns = %i", start.tv_sec, start.tv_nsec);
  g_main_loop_run(loop);

}





