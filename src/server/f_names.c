/*
** f_names.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:12:35 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:22:58 2016 nicolas thouchkaieff
*/

#include "server.h"

static void	aff_nicks(t_client *client, t_list_c *list_client)
{
  while (list_client)
    {
      if (list_client->client)
	{
	  if (list_client->next && list_client->next->client)
	    dprintf(client->socket, "%s ", list_client->client->nick);
	  else
	    dprintf(client->socket, "%s", list_client->client->nick);
	}
      list_client = list_client->next;
    }
  dprintf(client->socket, "\r\n");
}

void		print_names(t_server *server, t_client *client, char *chan)
{
  char		*new;
  int		i;
  t_channel	*list;

  i = 0;
  while ((new = strtok(strdup(&chan[i]), ",")) != NULL)
    {
      new = epur_str(new);
      if ((new[0] == '#' || new[0] == '&')
	  && (list = get_channel_from_name(server->channels, new)))
	{
	  dprintf(client->socket, ":127.0.0.1 353 %s = %s :", client->nick,
		  list->name);
	  aff_nicks(client, list->list_client);
	  dprintf(client->socket, ":127.0.0.1 366 %s %s :End of NAMES list\r\n",
		  client->nick, list->name);
	}
      i += strlen(new) + 1;
    }
}

static void	print_allnames(t_server *server, t_client *client)
{
  t_channel	*list;

  list = server->channels;
  while (list)
    {
      dprintf(client->socket, ":127.0.0.1 353 %s = %s :", client->nick,
	      list->name);
      aff_nicks(client, list->list_client);
      dprintf(client->socket, ":127.0.0.1 366 %s %s :End of NAMES list\r\n",
	      client->nick, list->name);
      list = list->next;
    }
}

int	f_names(t_server *server, t_client *client, char *cmd)
{
  if (cmd && strlen(cmd) != 0)
    print_names(server, client, cmd);
  else
    print_allnames(server, client);
  return (0);
}

int		f_users(t_server *server, t_client *client, char *cmd)
{
  t_list_c	*list;

  (void)cmd;
  list = server->clients;
  dprintf(client->socket, ":127.0.0.1 392 %s :UserID   Terminal  Host\r\n",
	  client->nick);
  if (list == NULL)
    dprintf(client->socket, ":127.0.0.1 395 %s :Nobody logged in\r\n",
	    client->nick);
  else
    while (list)
      {
	dprintf(client->socket, ":127.0.0.1 393 %s :%s %d %s\r\n",
		client->nick,
		list->client->nick,
		list->client->socket,
		list->client->hostname);
	list = list->next;
      }
  dprintf(client->socket, ":127.0.0.1 394 %s :End of users\r\n", client->nick);
  return (0);
}
