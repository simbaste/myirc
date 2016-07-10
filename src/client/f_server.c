/*
** f_server.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/client
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 18:56:48 2016 nicolas thouchkaieff
** Last update Sun Jun  5 19:00:07 2016 nicolas thouchkaieff
*/

#include "client.h"

static char	*getport(char *iport, char *ip)
{
  char		*port;
  int		newport;

  if ((port = malloc(10)) == NULL)
    return (NULL);
  memset(port, 0, 10);
  if (iport[strlen(iport) - 1] == ':')
    port = strcpy(port, "0");
  else if (strlen(ip) == strlen(iport))
    port = strcpy(port, "6667");
  else
    {
      newport = atoi(strtok(strdup(&iport[strlen(ip) + 1]), "\0"));
      sprintf(port, "%d", newport);
    }
  return (port);
}

int	f_server(t_client *client, char *iport)
{
  char	*port;
  char	*ip;

  if (client->connected == 1)
    {
      printf("Error: already connected.\n");
      return (1);
    }
  if ((ip = strtok(strdup(iport), ":")) == NULL)
    {
      printf("server: bad ip\n");
      return (1);
    }
  if ((port = getport(iport, ip)) == NULL)
    return (1);
  if (my_connect(client, ip, port) == -1)
    return (1);
  dprintf(client->fd, "NICK %s\r\n", client->nick);
  dprintf(client->fd, "USER nicos 0 * thoucha\r\n");
  first_connect(client);
  return (0);
}

int	f_nick(t_client *client, char *cmd)
{
  dprintf(client->fd, "NICK %s\r\n", cmd);
  if (cmd && strlen(cmd) > 0)
    client->nick = strdup(cmd);
  else
    read_serv(client, "NIC");
  return (0);
}

int	f_list(t_client *client, char *cmd)
{
  dprintf(client->fd, "LIST %s\r\n", cmd);
  return (0);
}

int	f_join(t_client *client, char *cmd)
{
  dprintf(client->fd, "JOIN %s\r\n", cmd);
  client->channel = strdup(cmd);
  return (0);
}
