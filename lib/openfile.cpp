/* openfile.c */
#include "libdams.h"

int fildes = 0;
FILE *f_data = NULL;
char* current_fname = NULL;
long base;

int openfile(const char* fname) {
  struct stat st;
  void* pbase;
  char fnamedata[BUFSIZ], fnametry[BUFSIZ];

  if (f_data) {
    // already opened
    if (strcmp(fname, current_fname) == 0) {
      // opening identical file
      return 0;
    }
    // close opened file
    closefile();
  }
  // open new file
  current_fname = (char*)malloc(sizeof(char) * strlen(fname) + 1);
  strcpy(current_fname, fname);

  strcpy(fnamedata, fname);
  strcat(fnamedata, ".dat");
  strcpy(fnametry, fname);
  strcat(fnametry, ".try");

  stat(fnametry, &st);
  fildes = open(fnametry, O_RDONLY, 0666);
  if (fildes == -1) {
    fprintf(stderr, "ERR: Cannot open data file: %s\n", fnametry);
    return -1;
  }

  pbase = NULL;
  if (onmemory == 1) {
    pbase = malloc(st.st_size);
    if (!pbase) {
      fprintf(stdout, "MSG: in openfile, can't allocate memory.\n");
    } else {
      int readbytes = read(fildes, pbase, st.st_size);
      if (readbytes < st.st_size) {
	fprintf(stdout, "MSG: in openfile, can't read index file.\n");
	free(pbase);
	pbase = NULL;
      }
    }    
  }
  if (!pbase) {
    pbase = mmap((caddr_t)0, st.st_size, PROT_READ, MAP_PRIVATE, fildes, 0);
    onmemory = 0;
    if (pbase < 0) {
      /* mmap failed */
      fprintf(stderr, "ERR: failed to execute mmap.\n");
      return -1;
    }
  }
  base = (long)pbase;
  damsTry = (StaticPtrTry*)pbase;

  // Open datafile
  f_data = fopen(fnamedata, "r");
  if (!f_data) {
    fprintf(stderr, "ERR: Cannot open data file: %s\n", fnamedata);
    return -1;
  }
  return 0;
}

int closefile(void) {
  struct stat st;
  void* pbase;
  char fnametry[BUFSIZ];

  if (!f_data) return 0; // not opened yet

  strcpy(fnametry, current_fname);
  strcat(fnametry, ".try");

  pbase = (void*)base;
  stat(fnametry, &st);

  if (onmemory == 1) {
    free(pbase);
  } else {
    munmap(pbase, st.st_size);
  }

  // close opened file
  close(fildes);
  fclose(f_data);
  free(current_fname);
  f_data = NULL; // mark that the file is closed.
  return 0;
}
