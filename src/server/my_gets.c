/*
** my_gets.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 13:54:34 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:38:30 2016 nicolas thouchkaieff
*/

#include "server.h"

int	get_args(int ac, char **av, t_server *server)
{
  if (ac == 2)
    {
      if (atoi(av[1]) <= 0 || atoi(av[1]) > 65535)
	return (my_err("Bad port."));
      server->port = atoi(av[1]);
    }
  else
    return (my_err("Usage: ./server port."));
  server->channels = NULL;
  server->clients = NULL;
  return (0);
}

t_client	*get_client_from_nick(t_list_c *list, char *name)
{
  while (list)
    {
      if (list->client->nick && strcmp(list->client->nick, name) == 0)
	return (list->client);
      list = list->next;
    }
  return (NULL);
}

t_channel	*get_channel_from_name(t_channel *list, char *name)
{
  while (list)
    {
      if (strcmp(list->name, name) == 0)
	return (list);
      list = list->next;
    }
  return (NULL);
}

t_client	*get_client_from_username(t_list_c *list, char *name)
{
  while (list)
    {
      if (list->client->username && strcmp(list->client->username, name) == 0)
	return (list->client);
      list = list->next;
    }
  return (NULL);
}

t_client	*get_client_from_socket(t_list_c *list, int s)
{
  while (list)
    {
      if (list->client->socket == s)
	return (list->client);
      list = list->next;
    }
  return (NULL);
}
