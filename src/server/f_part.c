/*
** f_part.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:23:25 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:29:59 2016 nicolas thouchkaieff
*/

#include "server.h"

static void	part_chan(t_server *server, t_client *client, char *cmd, char *msg)
{
  t_channel	*channel;

  if (get_channel_from_name(client->channels, cmd) != NULL)
    {
      channel = get_channel_from_name(server->channels, cmd);
      sup_client(&channel->list_client, client);
      sup_chanel(&client->channels, cmd);
      client->channel = NULL;
      if (msg && strlen(msg) > 0)
	dprintf(client->socket, ":127.0.0.1 PART %s %s\r\n", cmd, msg);
      else
	dprintf(client->socket, ":127.0.0.1 PART %s\r\n", cmd);
    }
  else
    dprintf(client->socket,
	    ":127.0.0.1 442 %s %s :You're not on that channel\r\n",
	    client->nick, cmd);
}

static void	part_multichan(t_server *server, t_client *client,
			       char *chan, char *msg)
{
  char		*new;
  int		i;

  i = 0;
  while ((new = strtok(strdup(&chan[i]), ",")) != NULL)
    {
      new = epur_str(new);
      if (strlen(new) <= 50 && (new[0] == '#' || new[0] == '&')
	  && get_channel_from_name(server->channels, new))
	part_chan(server, client, new, msg);
      else
	dprintf(client->socket, ":127.0.0.1 403 %s %s :No such channel\r\n",
		client->nick, new);
      i += strlen(new) + 1;
    }
}

static void	leave_allchan(t_server *server, t_client *client, char *msg)
{
  t_channel	*chan;

  chan = client->channels;
  while (chan)
    {
      if (chan->name)
	part_chan(server, client, chan->name, msg);
      chan = chan->next;
    }
}

int	f_part(t_server *server, t_client *client, char *cmd)
{
  char	chan[256];
  char	msg[256];

  memset(chan, 0, 256);
  memset(msg, 0, 256);
  if ((sscanf(cmd, "%s %s", chan, msg)) == 2)
    part_multichan(server, client, chan, msg);
  else if ((sscanf(cmd, "%s", chan)) == 1)
    part_multichan(server, client, chan, NULL);
  else
    dprintf(client->socket, ":127.0.0.1 461 %s PART :Not enough parameters\r\n",
	    client->nick);
  return (0);
}

int	f_quit(t_server *server, t_client *client, char *cmd)
{
  leave_allchan(server, client, cmd);
  dprintf(client->socket, ":127.0.0.1 QUIT %s\r\n", cmd);
  printf("%s(%d): Connection closed\n", client->nick, client->socket);
  server->e.fd_type[client->socket] = FD_FREE;
  close(client->socket);
  sup_client(&server->clients, client);
  return (0);
}
