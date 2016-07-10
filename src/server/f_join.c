/*
** f_join.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:18:02 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:20:45 2016 nicolas thouchkaieff
*/

#include "server.h"

static void	print_join(t_server *server, t_client *client, t_channel *channel,
		   char *cmd)
{
  if (channel->topic)
    dprintf(client->socket, ":127.0.0.1 332 %s %s :%s\r\n", client->nick, cmd,
	    channel->topic);
  else
    dprintf(client->socket, ":127.0.0.1 331 %s %s :No topic is set\r\n",
	    client->nick, cmd);
  print_names(server, client, cmd);
}

static void	join_chan(t_server *server, t_client *client, char *cmd)
{
  t_channel	*channel;

  if (get_channel_from_name(server->channels, cmd) == NULL)
    {
      add_chanel(&server->channels, NULL, strdup(cmd));
      channel = get_channel_from_name(server->channels, cmd);
      my_put_end_in_list(&channel->list_client, client);
      client->channel = strdup(cmd);
      add_chanel(&client->channels, NULL, strdup(cmd));
    }
  else
    {
      channel = get_channel_from_name(server->channels, cmd);
      if (get_channel_from_name(client->channels, cmd) == NULL)
	{
	  my_put_end_in_list(&channel->list_client, client);
	  add_chanel(&client->channels, NULL, strdup(cmd));
	}
      client->channel = strdup(cmd);
    }
  print_join(server, client, channel, cmd);
}

int	f_join(t_server *server, t_client *client, char *cmd)
{
  char	*new;
  int	i;

  i = 0;
  if (cmd && strlen(cmd) > 0)
    {
      while ((new = strtok(strdup(&cmd[i]), ",")) != NULL)
	{
	  new = epur_str(new);
	  if (strlen(new) <= 50 && (new[0] == '#' || new[0] == '&')
	      && strstr(new, " ") == NULL)
	    join_chan(server, client, new);
	  else
	    dprintf(client->socket, ":127.0.0.1 403 %s %s :No such channel\r\n",
		    client->nick, new);
	  i += strlen(new) + 1;
	}
    }
  else
    dprintf(client->socket, ":127.0.0.1 461 %s JOIN :No such channel\r\n",
	    client->nick);
  return (0);
}
