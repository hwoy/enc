#include "enc.h"


PUTENCFP (enc0)
{
  int j;
  char tch;

  if (!parse)
    {
      return ('0');
    }

  tch = ch;

  for (j = 0; j <= i; j++)
    {
      tch = tch ^ parse[j];
    }

  return (tch ^ (parse[i] + 1));
}

/*************************************************************************************/

PUTENCFP (enc1)
{
  int j;
  char tch;

  if (!parse)
    {
      return 0;
    }

  tch = ch;


  for (j = 0; j <= i; j++)
    {
      tch = tch ^ parse[j];
    }

  return tch ^ (parse[i] << 1);
}

/*************************************************************************************/
PUTENCFP (enc2)
{
  int j;
  char tch;

  if (!parse)
    {
      return 0;
    }

  tch = ch;


  for (j = 0; j <= i; j++)
    {
      tch = tch ^ (parse[j] % (j + 1));
    }

  return tch ^ (parse[i]);
}

/*************************************************************************************/
PUTENCFP (encrnd)
{
  return (i % 2) ? enc1 (ch, parse, i) : enc0 (ch, parse, i);
}

