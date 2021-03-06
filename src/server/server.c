/*
** server.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 14:46:30 2016 nicolas thouchkaieff
** Last update Sun Jun  5 19:18:49 2016 nicolas thouchkaieff
*/

#include "server.h"

t_funcs	g_funcs[11] = {
  {"NICK", f_nick},
  {"USER", f_user},
  {"LIST", f_list},
  {"JOIN", f_join},
  {"PART", f_part},
  {"USERS", f_users},
  {"NAMES", f_names},
  {"PRIVMSG", f_privmsg},
  {"SENDFILE", f_send_file},
  {"ACCEPTFILE", f_accept_file},
  {"QUIT", f_quit},
};

static int	run_func(t_server *server, t_client *client, char *cmd)
{
  int		i;
  char		*ft;

  i = 0;
  ft = strtok(strdup(cmd), " \n");
  while (i < 11)
    {
      if (ft != NULL && strcasecmp(ft, g_funcs[i].cmd) == 0)
	return (g_funcs[i].p(server, client, epur_str(strdup(&cmd[strlen(ft)]))));
      i++;
    }
  dprintf(client->socket, ":127.0.0.1 421 %s :Unknown command\r\n", ft);
  return (0);
}

static int	run_cmd(t_server *server, t_client *client)
{
  int		n;
  char		*cmd;
  char		*new;

  n = 0;
  cmd = strdup(read_in_ring(client->buffer));
  cmd = epur_str(cmd);
  while ((new = strtok(strdup(&cmd[n]), "\r\n")))
    {
      run_func(server, client, new);
      n += strlen(new) + 2;
    }
  return (0);
}

static void	client_read(t_server *server, int fd)
{
  int		r;
  char		buf[RING_SIZE];
  t_client	*client;

  client = get_client_from_socket(server->clients, fd);
  memset(buf, 0, RING_SIZE);
  r = recv(fd, buf, RING_SIZE, 0);
  if (r > 0)
    {
      write_in_ring(client->buffer, buf);
      if (buf[r - 1] == '\n' && buf[r - 2] == '\r')
	run_cmd(server, client);
    }
  else
    {
      sup_client(&server->clients, client);
      printf("%d: Connection closed\n", fd);
      close(fd);
      server->e.fd_type[fd] = FD_FREE;
    }
}

void			add_client(t_server *server, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  t_client		*client;
  char			ip[INET_ADDRSTRLEN];

  if ((client = malloc(sizeof(t_client))) == NULL)
    return ;
  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  init_client(cs, client);
  client->ip = strdup(inet_ntop(client_sin.sin_family,
				(struct sockaddr *)&client_sin.sin_addr, ip,
				INET_ADDRSTRLEN));
  my_put_end_in_list(&server->clients, client);
  server->e.fd_type[cs] = FD_CLIENT;
  server->e.fct_read[cs] = client_read;
  server->e.fct_write[cs] = NULL;
}
