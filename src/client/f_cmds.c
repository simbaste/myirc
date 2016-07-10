/*
** f_cmds.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sat Jun  4 11:46:58 2016 nicolas thouchkaieff
** Last update Sun Jun  5 19:22:00 2016 nicolas thouchkaieff
*/

#include "client.h"

int	f_users(t_client *client, char *cmd)
{
  dprintf(client->fd, "USERS %s\r\n", cmd);
  return (0);
}

int	f_names(t_client *client, char *cmd)
{
  dprintf(client->fd, "NAMES %s\r\n", cmd);
  return (0);
}

int	f_msg(t_client *client, char *cmd)
{
  dprintf(client->fd, "PRIVMSG %s\r\n", cmd);
  return (0);
}

int	f_send_file(t_client *client, char *cmd)
{
  dprintf(client->fd, "SEND_FILE %s\r\n", cmd);
  return (0);
}

int	f_accept_file(t_client *client, char *cmd)
{
  dprintf(client->fd, "ACCEPT_FILE %s\r\n", cmd);
  return (0);
}
