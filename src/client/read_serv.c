/*
** read_serv.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 18:04:34 2016 nicolas thouchkaieff
** Last update Sun Jun  5 18:27:32 2016 nicolas thouchkaieff
*/

#include "client.h"

t_data		init_data(int *tab, char *last, char *code)
{
  t_data	data;

  data.tab = tab;
  data.last = last;
  data.code = code;
  return (data);
}

static void	loop_linerecv(char *tmp, t_data *data, int *stop)
{
  int		j;
  char		*new;

  j = 0;
  while ((new = strtok(strdup(&tmp[j]), "\n")) != NULL)
    {
      j += strlen(new) + 1;
      if (new[strlen(new) - 1] == '\r')
	{
	  new[strlen(new) - 1] = 0;
	  sprintf(data->last, "%s%s", data->last, new);
	  if (data->last[0] == ':')
	    new = strstr(data->last, " ") + 1;
	  printf("%s\n", new);
	  if (strncmp(new, data->code, 3) == 0)
	    *stop = 1;
	  if (strncmp(new, "4", 1) == 0 || strncmp(new, "5", 1) == 0
	      || strncmp(new, "ERROR", 5) == 0)
	    *stop = 1;
	  memset(data->last, 0, 512);
	}
      else
	sprintf(data->last, "%s", new);
    }
}

static int	read_recv(t_client *client, char **last, int *stop, char *code)
{
  int		i;
  char		tmp[SIZE];
  t_data	data;

  memset(tmp, 0, SIZE);
  data = init_data(NULL, *last, code);
  i = recv(client->fd, tmp, SIZE, 0);
  if (i > 0)
    {
      loop_linerecv(tmp, &data, stop);
      *last = data.last;
      return (0);
    }
  else if (i == 0)
    {
      client->connected = 0;
      return (my_err("Connection closed by server"));
    }
  else
    return (my_perr("recv"));
}

int	read_serv(t_client *client, char *code)
{
  int	stop;
  char	*last;

  stop = 0;
  if ((last = malloc(SIZE_CMD)) == NULL)
    return (my_perr("malloc"));
  memset(last, 0, SIZE_CMD);
  while (stop == 0)
    if (read_recv(client, &last, &stop, code) == -1)
      return (-1);
  return (0);
}
