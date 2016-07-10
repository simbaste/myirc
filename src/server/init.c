/*
** init.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:40:08 2016 nicolas thouchkaieff
** Last update Sun Jun  5 14:46:13 2016 nicolas thouchkaieff
*/

#include "server.h"

void	init_client(int cs, t_client *client)
{
  client->socket = cs;
  client->nick = NULL;
  client->username = NULL;
  client->realname = NULL;
  client->hostname = NULL;
  client->logged = 0;
  client->channel = NULL;
  client->channels = NULL;
  client->buffer = init_ring();
}

static void	server_read(t_server *server, int fd)
{
  printf("New client.\n");
  add_client(server, fd);
}

int	init_server(t_server *server)
{
  memset(server->e.fd_type, FD_FREE, MAX_FD);
  if ((server->socket = socket(PF_INET, SOCK_STREAM,
			       getprotobyname("TCP")->p_proto)) == -1)
    return (my_perr("socket"));
  server->sin.sin_family = AF_INET;
  server->sin.sin_port = ntohs(server->port);
  server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(server->socket, (struct sockaddr*)&server->sin,
	   sizeof(server->sin)) != 0)
    {
      if (close(server->socket) == -1)
	return (-1);
      return (my_perr("bind"));
    }
  if (listen(server->socket, FD_SETSIZE) == -1)
    {
      if (close(server->socket) == -1)
	return (-1);
      return (my_perr("listen"));
    }
  server->e.fd_type[server->socket] = FD_SERVER;
  server->e.fct_read[server->socket] = server_read;
  server->e.fct_write[server->socket] = NULL;
  return (0);
}
