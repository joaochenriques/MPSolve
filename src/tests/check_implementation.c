/**
 * @file
 * @brief Implementation of the routines common to all the
 * checks
 */

#include "check_implementation.h"
#include <stdlib.h>

void
starting_setup()
{
    putenv("CK_DEFAULT_TIMEOUT=10");
}

void
set_timeout(int timeout)
{
    char set_timeout_string[255];
    sprintf(set_timeout_string, "CK_DEFAULT_TIMEOUT=%d", timeout);
    putenv(set_timeout_string);
}

void
append_slash(char* dest)
{
#ifdef WIN32
    strcat(dest, "\\");
#else
    strcat(dest, "/");
#endif
}

/**
 * @brief Since this is a autotest unit, we can get the
 * name of the pol_file concatenating the environment
 * variable srcdir with the name of the pol_file
 */
char*
get_pol_file(const char* pol_name, const char* type_name)
{
    const char* srcdir_path = getenv("srcdir");
    size_t path_length = strlen(pol_name) + strlen(srcdir_path) + 14;
    char* final_path = (char*) malloc(sizeof(char) * path_length);

    /* Construct the path */
    strcpy(final_path, srcdir_path);
    append_slash(final_path);
    strcat(final_path, type_name);
    append_slash(final_path);
    strcat(final_path, pol_name);
    strcat(final_path, ".pol");

    return final_path;
}

/**
 * @brief Since this is a autotest unit, we can get the
 * name of the res_file concatenating the environment
 * variable srcdir with the name of the res_file
 */
char*
get_res_file(const char* pol_name, const char* type_name)
{
    const char* srcdir_path = getenv("srcdir");
    size_t path_length = strlen(pol_name) + strlen(srcdir_path) + 26;
    char* final_path = (char*) malloc(sizeof(char) * path_length);

    /* Construct the path */
    strcpy(final_path, srcdir_path);
    append_slash(final_path);
    strcat(final_path, "..");
    append_slash(final_path);
    strcat(final_path, "results");
    append_slash(final_path);
    strcat(final_path, type_name);
    append_slash(final_path);
    strcat(final_path, pol_name);
    strcat(final_path, ".res");

    return final_path;
}


test_pol*
test_pol_new(const char* name, const char* type_name,
             int out_digits,
             mps_phase phase, mps_boolean ga)
{
  test_pol *t = malloc(sizeof(test_pol));
  t->pol_file = get_pol_file(name, type_name);
  t->res_file = get_res_file(name, type_name);
  t->out_digits = out_digits;
  t->phase = phase;
  t->ga = ga;
  return t;
}

void
test_pol_free(test_pol* pol)
{
    free(pol->pol_file);
    free(pol->res_file);
    free(pol);
}