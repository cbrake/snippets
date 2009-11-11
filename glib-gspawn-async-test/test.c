
#include <glib.h>

int main()
{
  GPid pid;
  GError *error = NULL;
  gchar *dial_ppp_argv[] = {"/usr/sbin/pppd", "call", "verizon", NULL};
  //gchar *dial_ppp_argv[] = {"/bin/ls", NULL};

  if (g_spawn_async_with_pipes(NULL,          /* working dir */
                               dial_ppp_argv, /* argv */
                               NULL,          /* envp */
                               0,             /* flags */
                               NULL,          /* child_setup */
                               NULL,          /* user_data */
                               NULL,          /* child_pid */
                               NULL,          /* standard_input */
                               NULL,          /* standard_output */
                               NULL,          /* standard_error */
                               NULL          /* error */
        ) == FALSE) {
    g_debug("Error executing pppd");
  }

  return;

  if (g_spawn_async(NULL,          /* working dir */
                               dial_ppp_argv, /* argv */
                               NULL,          /* envp */
                               0,             /* flags */
                               NULL,          /* child_setup */
                               NULL,          /* user_data */
                               NULL,          /* child_pid */
                               NULL          /* error */
        ) == FALSE) {
    g_debug("Error executing pppd");
  }

}

