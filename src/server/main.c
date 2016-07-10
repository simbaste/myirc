/*
** main.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Tue May 24 10:19:38 2016 nicolas thouchkaieff
** Last update Sun Jun  5 15:26:28 2016 nicolas thouchkaieff
*/

#include "server.h"

void	my_fd_set(t_server *server)
{
  int	i;

  i = 0;
  FD_ZERO(&server->fd_read);
  server->fd_max = 0;
  while (i < MAX_FD)
    {
      if (server->e.fd_type[i] != FD_FREE)
	{
	  FD_SET(i, &server->fd_read);
	  server->fd_max = i;
	}
      i++;
    }
}

int	loop_server(t_server *server)
{
  int	i;

  while (1)
    {
      my_fd_set(server);
      if (select(server->fd_max + 1, &server->fd_read, NULL, NULL, NULL) == -1)
	my_perr("select");
      i = 0;
      while (i < MAX_FD)
	{
	  if (FD_ISSET(i, &server->fd_read))
	    server->e.fct_read[i](server, i);
	  i++;
	}
    }
  return (0);
}

int		main(int ac, char **av)
{
  t_server	server;

  if (get_args(ac, av, &server) == -1)
    return (-1);
  if (init_server(&server) == -1)
    return (-1);
  if (loop_server(&server) == -1)
    return (-1);
  close(server.socket);
  return (0);
}
