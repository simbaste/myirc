/*
** f_msg.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:32:41 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:32:42 2016 nicolas thouchkaieff
*/

#include "server.h"

void	send_msg_to_user(t_client *client, char *msg)
{
  dprintf(client->socket, ":127.0.0.1 PRIVMSG %s %s\r\n",
	  client->nick, msg);
}

void		send_msg_to_channel(t_channel *channel, char *msg)
{
  t_list_c	*list_client;

  list_client = channel->list_client;
  while (list_client)
    {
      if (list_client->client)
	dprintf(list_client->client->socket, ":127.0.0.1 PRIVMSG %s %s\r\n",
		channel->name, msg);
      list_client = list_client->next;
    }
}

int		f_privmsg(t_server *server, t_client *client, char *cmd)
{
  char		target[256];
  char		msg[256];
  t_channel	*chantarg;
  t_client	*clienttarg;

  memset(target, 0, 256);
  memset(msg, 0, 256);
  if ((sscanf(cmd, "%s %s", target, msg)) == 2)
    {
      if ((target[0] == '#' || target[0] == '&')
	  && (chantarg = get_channel_from_name(server->channels, target)))
	send_msg_to_channel(chantarg, msg);
      else if ((clienttarg = get_client_from_nick(server->clients, target)))
	send_msg_to_user(clienttarg, msg);
      else
	dprintf(client->socket,
		":127.0.0.1 401 %s %s :No such nick/channel\r\n", client->nick,
		target);
    }
  else
    dprintf(client->socket, ":127.0.0.1 411 %s :No text to send\r\n",
	    client->nick);
  return (0);
}

int	f_send_file(t_server *server, t_client *client, char *cmd)
{
  (void)server;
  (void)client;
  (void)cmd;
  dprintf(client->socket, ":127.0.0.1 421 SEND_FILE :Unknown command\r\n");
  return (0);
}

int	f_accept_file(t_server *server, t_client *client, char *cmd)
{
  (void)server;
  (void)client;
  (void)cmd;
  dprintf(client->socket, ":127.0.0.1 421 ACCEPT_FILE :Unknown command\r\n");
  return (0);
}
