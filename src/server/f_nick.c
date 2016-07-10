/*
** f_nick.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:04:30 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:07:19 2016 nicolas thouchkaieff
*/

#include "server.h"

static void		register_user(t_client *client, char *hostname)
{
  struct hostent	*hp;
  struct in_addr	ip;

  (void)hostname;
  inet_aton(client->ip, &ip);
  hp = gethostbyaddr((const void *)&ip, sizeof(ip), AF_INET);
  client->hostname = strdup(hp->h_name);
  client->logged = 1;
  dprintf(client->socket, ":127.0.0.1 001 %s :Welcome to the Internet ",
	  client->nick);
  dprintf(client->socket, "Relay Network %s!%s@%s\r\n", client->nick,
	  client->username, hp->h_name);
  dprintf(client->socket, ":127.0.0.1 002 %s :Your host is ", client->nick);
  dprintf(client->socket, "irc.simbaste.fr, running version ThouchIRC1.0\r\n");
  dprintf(client->socket, ":127.0.0.1 003 %s :This server was ", client->nick);
  dprintf(client->socket, "created 05/22/16\r\n");
  dprintf(client->socket, ":127.0.0.1 004 %s :irc.simbaste.fr ", client->nick);
  dprintf(client->socket, "ThouchIRC1.0\r\n");
}

int	f_nick(t_server *server, t_client *client, char *name)
{
  if (name && strlen(name) > 0)
    {
      if (get_client_from_nick(server->clients, name) == NULL)
	{
	  if (strlen(name) > 9)
	    dprintf(client->socket,
		    ":127.0.0.1 432 %s :Erroneus nickname\r\n", name);
	  else
	    {
	      client->nick = strdup(name);
	      dprintf(client->socket, ":127.0.0.1 NICK :%s\r\n", name);
	    }
	  if (client->username)
	    register_user(client, NULL);
	}
      else
	dprintf(client->socket,
		":127.0.0.1 431 %s :Nickname is already in use\r\n", name);
    }
  else
    my_send(client->socket, ":127.0.0.1 431 :No nickname given\r\n");
  return (0);
}

int	f_user(t_server *server, t_client *client, char *cmd)
{
  char	username[256];
  char	hostname[256];
  char	servername[256];
  char	realname[256];

  memset(username, 0, 256);
  memset(hostname, 0, 256);
  memset(realname, 0, 256);
  if ((sscanf(cmd, "%s %s %s %s", username,
	      hostname, servername, realname)) == 4)
    if (get_client_from_username(server->clients, username) == NULL)
      {
	client->username = strdup(username);
	client->realname = strdup(realname);
	if (client->nick)
	  register_user(client, hostname);
      }
    else
      my_send(client->socket, ":127.0.0.1 431 :You may not reregister\r\n");
  else
    my_send(client->socket, ":127.0.0.1 431 :Not enough parameters\r\n");
  return (0);
}
