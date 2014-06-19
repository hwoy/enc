#ifdef ANSI
int grapstring (const char *str, char sep, int maxcount, int blength,
		void *buff);
#else
int grapstring (const char *str, char sep, int maxcount, int blength,
		char buff[*][*]);
#endif

int cutnl (char *, char);
char *cutcharbe (char *, char);

extern char GRAP_VERSION_STRING[];
extern int GRAP_VERSION_MAJOR;
extern int GRAP_VERSION_MINOR;

/* version 1.36 */


