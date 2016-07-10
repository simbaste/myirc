/*
** func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Tue May 24 18:25:19 2016 stephanedarcy simomba
** Last update Sun Jun  5 14:53:11 2016 nicolas thouchkaieff
*/

#include <stdio.h>
#include "myirc.h"

int	my_perr(char *str)
{
  perror(str);
  return (-1);
}

int	my_err(char *str)
{
  fprintf(stderr, "%s\n", str);
  return (-1);
}

ssize_t	my_send(int socket, char *msg)
{
  return (send(socket, msg, strlen(msg), 0));
}

char	*epur_str(char *str)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str && str[i] != 0)
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  while (str[i] == ' ' || str[i] == '\t')
	    i++;
	  if (str[i] != 0 && j > 0)
	    str[j++] = ' ';
	}
      str[j++] = str[i++];
    }
  str[j] = 0;
  return (str);
}
