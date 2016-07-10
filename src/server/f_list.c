/*
** f_list.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:09:19 2016 nicolas thouchkaieff
** Last update Sun Jun  5 15:23:06 2016 nicolas thouchkaieff
*/

#include "server.h"

static int	count_client_list(t_list_c *list)
{
  int		i;

  i = 0;
  while (list)
    {
      if (list->client)
	i++;
      list = list->next;
    }
  return (i);
}

static void	list_chan(t_client *client, t_channel *channel, char *cmd)
{
  if (cmd && strlen(cmd) > 0)
    {
      if (strstr(cmd, channel->name) != NULL)
	dprintf(client->socket, ":127.0.0.1 322 %s %s %d :%s\r\n",
		client->nick, channel->name,
		count_client_list(channel->list_client),
		((channel->topic) ? (channel->topic) : ("")));
    }
  else
    dprintf(client->socket, ":127.0.0.1 322 %s %s %d :%s\r\n",
	    client->nick, channel->name,
	    count_client_list(channel->list_client),
	    ((channel->topic) ? (channel->topic) : ("")));
}

int		f_list(t_server *server, t_client *client, char *cmd)
{
  t_channel	*channel;

  channel = server->channels;
  dprintf(client->socket, ":127.0.0.1 321 %s Channel :Users Name\r\n",
	  client->nick);
  while (channel)
    {
      if (channel->name && channel->name[0] == '#')
	list_chan(client, channel, cmd);
      channel = channel->next;
    }
  dprintf(client->socket, ":127.0.0.1 323 %s :End of LIST\r\n", client->nick);
  return (0);
}
