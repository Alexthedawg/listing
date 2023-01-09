#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#define OPTSTR "l:e:r:"
#define USAGE  "usage: ./main -l label | -e entry [-l label] | -r label\n"

void errexit (const char* msg);
void remove_list (char *label);
void add_list (char *label);
void add_entry (char *entry, char *label);

int main (int argc, char **argv) {
  int opt, l, e, r;
  char *lopt, *eopt, *ropt;
  
  /* Parsing CL arguments. */
  while ((opt = getopt (argc, argv, OPTSTR)) != EOF) {
    switch (opt) {
      case 'l':
        lopt = optarg;
        l++;
        break;
      case 'e':
        eopt = optarg;
        e++;
        break;
      case 'r':
        ropt = optarg;
        r++;
        break;
      default:
        errexit (USAGE);
        break;
    }
  }
  
  /* Argument validation. */
  if (l < 1 && e < 1 && r < 1)
    errexit (USAGE);
  if (l > 1 || e > 1 || r > 1)
    errexit (USAGE);
  if (r == 1 && e == 1)
    errexit (USAGE);
  if (r == 1 && l == 1)
    errexit (USAGE);
  if (e == 1 && l != 1)
    errexit (USAGE);
  
  /* Performing action. */
  if (r == 1)
    remove_list (ropt);
  
  else if (e == 1)
    add_entry (eopt, lopt);
  
  else if (l == 1)
    add_list (lopt);
  
  exit (EXIT_SUCCESS);
}

void errexit (const char *msg) {
  printf ("%s", msg);
  exit (EXIT_FAILURE);
}

void remove_list (char *label) {
  printf ("Do you want to remove %s? [y]\n", label);
  if (getc (stdin) != 'y')
    errexit ("Operation aborted.\n");
  
  if (remove (label) != 0)
    errexit ("Deletion failed.\n");
  
  exit (EXIT_SUCCESS);
}

void add_list (char *label) {
  FILE *fp;
  
  if ((fp = fopen (label, "a+")) == NULL)
    errexit ("File creation failed.\n");
  
  fclose (fp);
}

void add_entry (char *entry, char *label) {
  FILE *fp;
  
  if ((fp = fopen (label, "a+")) == NULL)
    errexit ("File creation failed.\n");
  
  fprintf (fp, "%s\n", entry);
  fclose (fp);
}
