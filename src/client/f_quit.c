/*
** f_quit.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/client
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 19:00:27 2016 nicolas thouchkaieff
** Last update Sun Jun  5 19:22:15 2016 nicolas thouchkaieff
*/

#include "client.h"

int	f_part(t_client *client, char *cmd)
{
  dprintf(client->fd, "PART %s\r\n", cmd);
  client->channel = NULL;
  return (0);
}

int	f_disconnect(t_client *client, char *cmd)
{
  client->connected = 0;
  dprintf(client->fd, "QUIT :%s\r\n", cmd);
  read_serv(client, "QUI");
  client->channel = NULL;
  close(client->fd);
  return (0);
}

int	f_quit(t_client *client, char *cmd)
{
  (void)cmd;
  if (client->connected)
    f_disconnect(client, "bye");
  printf("Good bye.\n");
  return (-1);
}
