/* outputs:
 * (process:10005): DEBUG: CLIFF: we have a match SeedSense_update_3.4.05.inc
 * (process:10005): DEBUG: match count = 3
 * (process:10005): DEBUG: full = SeedSense_update_3.4.05.inc
 * (process:10005): DEBUG: version = 3.4.05
 * (process:10005): DEBUG: type = inc
 */

#include <glib.h>


int main()
{
  const gchar * name = "SeedSense_update_3.4.05.inc";
  gchar * full;
  gchar * version;
  gchar * type;

  int match_count;

  GMatchInfo * match_info;
  GRegex * update_re = g_regex_new("SeedSense_update_(\\d+\\.\\d+\\.\\d+)\\.(img|inc)", 0, 0, NULL);

  if (g_regex_match_full(update_re, name, -1, 0, 0, &match_info, NULL) == TRUE) {
    g_debug("CLIFF: we have a match %s", name);
    match_count = g_match_info_get_match_count(match_info);

    g_debug("match count = %i", match_count);

    full = g_match_info_fetch(match_info, 0);
    version = g_match_info_fetch(match_info, 1);
    type = g_match_info_fetch(match_info, 2);
  }

  g_debug("full = %s", full);
  g_debug("version = %s", version);
  g_debug("type = %s", type);

  g_free(full);
  g_free(version);
  g_free(type);

  g_match_info_free(match_info);
  g_regex_unref(update_re);
}


