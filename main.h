#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grap/grap.h"
#include "enc.h"
#define PASSIZE 1024+1+1
#define PSIZE 1024
#define CHARSIZE 5
#define FCHAR -25
#define DEFAULTINDEX 0
#define DELIM ','
#define PFILE "prikey.txt"
#define EXFILE ".enc"
static char seckey[PASSIZE];
static char prikey[PSIZE + 1];
static char gr[PSIZE * CHARSIZE + 1];
static char buff[PSIZE][CHARSIZE];
static char fbuff[PSIZE + 1];

typedef char (*_enc_) (char, const char *, int);
static _enc_ enc[] = { enc0, enc1, enc2, encrnd, NULL };	/* Can be set encryption method function */

#define denc enc

int dircat (char *buff, const char *path, const char *fname);
int findFileExtend (const char *fn, const char *ext);
char *grappath (char *path);
int getNenc (const _enc_[]);
int isnumchar (const char *);










int
dircat (char *buff, const char *path, const char *fname)	/* return 0 if unsuccess and 1 if success */
{
  int i, j = 0, k;
  if (!buff || !path || !fname)
    {
      return 0;
    }



  for (i = 0; path[i]; i++)
    {
      if ((path[i] == '\\') || (path[i] == '/'))
	{
	  j = i;
	}
      buff[i] = path[i];
    }


  if (j)
    {
      j++;
    }

  for (i = j, k = 0; fname[k]; k++, i++)
    {
      buff[i] = fname[k];
    }
  buff[i] = 0;
  return 1;
}

int
findFileExtend (const char *fn, const char *ext)	/* return 0 if unsuccess and last position of '.' if success */
{
  int i, j;
  if (!fn || !ext)
    {
      return 0;
    }

  for (i = 0, j = -1; fn[i]; i++)
    {
      if (fn[i] == '.')
	{
	  j = i;
	}
    }

  return ((j == -1) || (strcmp (fn + j, ext))) ? 0 : j;	/*string.h is required */
}

char *
grappath (char *path)		/* return -1 if NULL ptr, 0 if sep was not found  and position of filename if success */
{
  int i, j = -1;
  if (!path)
    {
      return ((char *) 0);
    }
  for (i = 0; path[i]; i++)
    {
      if ((path[i] == '\\') || (path[i] == '/'))
	{
	  j = i;
	}
    }
  return path + ((j == -1) ? 0 : j + 1);

}

int
getNenc (const _enc_ enc[])	/* return -1 if NULL ptr and count-1 if success */
{
  int i;
  if (!enc)
    {
      return (-1);
    }
  for (i = 0; enc[i]; i++)
    {
    }
  return i - 1;
}

int
isnumchar (const char *str)	/* return 0 if false1 if true */
{
  int i;
  if ((!str) || !str[0])
    {
      return 0;
    }
  for (i = 0; str[i]; i++)
    {
      if (!(i) && (str[i] == '-'))
	{
	  continue;
	}
      if ((str[i] < '0') || (str[i] > '9'))
	{
	  return 0;
	}
    }
  return 1;
}


