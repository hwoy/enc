#include "main.h"

int
main (int argc, char *argv[])
{
  FILE *fp, *fp1, *fp2;
  int i, n, index = DEFAULTINDEX;

  if (getNenc (enc) < 0)
    {
      fprintf (stderr,
	       "Avalidable encryption function. Please contact a programmer\n");
      return 1;
    }

/**********************************          Parameters Operation                  *********************************/
  if ((argc != 3) && (argc != 4))
    {
      fprintf (stderr, "USAGE %s filename parse\n", grappath (argv[0]));
      fprintf (stderr, "\tor\n");
      fprintf (stderr, "USAGE %s filename parse n_option\n\n",
	       grappath (argv[0]));
      fprintf (stderr, "Valid n_option rang < 0 to %d>\n", getNenc (enc));
      fprintf (stderr, "Default n_option = %d\n", DEFAULTINDEX);
      return 1;
    }

  if (!argv[2][0])
    {
      fprintf (stderr, "NULL parse key is invalid\n");
      return 1;
    }

  if (strlen (argv[2]) > PASSIZE - 1)
    {
      fprintf (stderr, "Parse key is limited to %d chars.\n", PASSIZE - 1);
      return 1;
    }
  if (argc == 4)
    {
      if (!isnumchar (argv[3]))
	{
	  fprintf (stderr, "Invalid value of n_option\n");
	  fprintf (stderr, "Valid n_option rang < 0 to %d>\n", getNenc (enc));
	  return 1;
	}

      if ((index = atoi (argv[3])) > getNenc (enc) || (index < 0))
	{
	  fprintf (stderr,
		   "Valid numbers of encyption option rang < 0 to %d>\n",
		   getNenc (enc));
	  return 1;
	}

    }

/**********************************         Primary key is read from file  (fp2)                 *********************************/
  if (!dircat (fbuff, argv[0], PFILE))
    {
      fprintf (stderr, "Pointer mustn't be NULL\n");
      return 1;
    }

  if (!(fp2 = fopen (fbuff, "r")))
    {
      perror (fbuff);
      return 1;
    }

  fgets (gr, PSIZE * CHARSIZE, fp2);
  fclose (fp2);				  /**********closed fp2**********/
  cutnl (gr, 0);
  i = grapstring (cutcharbe (gr, 0x20), DELIM, PSIZE, CHARSIZE, buff);

  if (!i)
    {
      fprintf (stderr, "<Primary key> is must not null\n");
      return 1;
    }

  else if (i == -1)
    {
      fprintf (stderr, "<Primary key> is limited to <%d> key numbers\n",
	       PSIZE - 1);
      return 1;
    }

  else if (i == -2)
    {
      fprintf (stderr, "<Primary key> is limited to <%d> charecter numbers\n",
	       CHARSIZE - 1);
      return 1;
    }

  for (n = 0; n < i; n++)
    {
      if (!isnumchar (&buff[n][0]))
	{
	  fprintf (stderr,
		   "Position %d %s:Value of <PRIMARY KEY> must be number\n",
		   n + 1, &buff[n][0]);
	  return 1;
	}

      prikey[n] = (char) atoi (&buff[n][0]);
      if (!prikey[n])
	{
	  fprintf (stderr,
		   "Position %d %s:Value of <PRIMARY KEY> must not equal 0\n",
		   n + 1, &buff[n][0]);
	  return 1;
	}
    }
  prikey[n] = 0;



/**********************************        secondary key is read from third parameter                    *********************************/
  for (i = 0; argv[2][i]; i++)
    {
      seckey[i] = argv[2][i];
    }

  seckey[i++] = FCHAR;
  seckey[i] = 0;


/**********************************        open file for reading (fp)                   *********************************/

  if (!(fp = fopen (argv[1], "rb")))
    {
      perror (argv[1]);
      return 1;
    }

/**********************************        open file for writing  (fp1)                  *********************************/
  strcpy (fbuff, argv[1]);
  strcat (fbuff, EXFILE);

  if (!(fp1 = fopen (fbuff, "wb")))
    {
      perror (fbuff);
      fclose (fp);
      return 1;
    }

/**********************************        Encryted-data writing                    *********************************/
  for (i = 0; seckey[i]; i++)
    {
      fputc ((*enc[index]) (seckey[i], prikey, i % strlen (prikey)), fp1);
    }


  for (n = 0; (i = fgetc (fp)) != EOF; n %= strlen (seckey))
    {
      fputc ((*enc[index]) (i, seckey, n), fp1);
      n++;
    }

  fclose (fp);
  fclose (fp1);
  return 0;
}


