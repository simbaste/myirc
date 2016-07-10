/*
** first_connect.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/client
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 18:15:17 2016 nicolas thouchkaieff
** Last update Sun Jun  5 18:27:05 2016 nicolas thouchkaieff
*/

#include "client.h"

static int	*check_wel(char *new, int *tab, int *stop, t_client *client)
{
  if (strncmp(new, "001", 3) == 0)
    tab[0] = 1;
  if (strncmp(new, "002", 3) == 0)
    tab[1] = 1;
  if (strncmp(new, "003", 3) == 0)
    tab[2] = 1;
  if (strncmp(new, "4", 1) == 0 || strncmp(new, "5", 1) == 0)
    *stop = 1;
  if (strncmp(new, "ERROR", 5) == 0)
    {
      *stop = 1;
      client->connected = 0;
    }
  printf("%s\n", new);
  return (tab);
}

static int	*init_tab()
{
  int		*tab;

  if ((tab = malloc(3 * sizeof(int))) == NULL)
    return (NULL);
  tab[0] = 0;
  tab[1] = 0;
  tab[2] = 0;
  return (tab);
}

static void	loop_line(char *tmp, t_data *data, t_client *client, int *stop)
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
	  data->tab = check_wel(new, data->tab, stop, client);
	  memset(data->last, 0, 512);
	}
      else
	sprintf(data->last, "%s", new);
    }
  if (tmp[strlen(tmp) - 1] == '\n' && tmp[strlen(tmp) - 2] == '\r'
      && data->tab[0] == 1 && data->tab[1] == 1 && data->tab[2] == 1)
    *stop = 1;
}

static int	*first_recv(int *tab, t_client *client, char **last, int *stop)
{
  int		i;
  char		tmp[SIZE];
  t_data	data;

  data = init_data(tab, *last, NULL);
  memset(tmp, 0, SIZE);
  i = recv(client->fd, tmp, SIZE, 0);
  if (i > 0)
    {
      loop_line(tmp, &data, client, stop);
      tab = data.tab;
      *last = data.last;
      return (tab);
    }
  else if (i == 0)
    {
      client->connected = 0;
      my_err("Connection closed by server");
      return (NULL);
    }
  else
    {
      my_perr("recv");
      return (NULL);
    }
}

int	first_connect(t_client *client)
{
  int	*tab;
  int	stop;
  char	*last;

  stop = 0;
  if ((tab = init_tab()) == NULL)
    return (my_perr("malloc"));
  if ((last = malloc(SIZE_CMD)) == NULL)
    return (my_perr("malloc"));
  memset(last, 0, SIZE_CMD);
  while (stop == 0)
    if ((tab = first_recv(tab, client, &last, &stop)) == NULL)
      return (-1);
  if (tab[0] == 1 && tab[1] == 1 && tab[2] == 1)
    return (client->connected = 1);
  return (0);
}
