/*
** client.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/client
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sun Jun  5 18:29:08 2016 nicolas thouchkaieff
** Last update Sun Jun  5 19:24:20 2016 nicolas thouchkaieff
*/

#include "client.h"

t_funcs	g_funcs[12] = {
  {"/server", f_server},
  {"/nick", f_nick},
  {"/list", f_list},
  {"/join", f_join},
  {"/part", f_part},
  {"/users", f_users},
  {"/names", f_names},
  {"/msg", f_msg},
  {"/send_file", f_send_file},
  {"/accept_file", f_accept_file},
  {"/disconnect", f_disconnect},
  {"/quit", f_quit},
};

int			my_connect(t_client *client, char *ip, char *port)
{
  struct addrinfo	c_in;
  struct addrinfo	*info;

  memset(&c_in, 0, sizeof(struct addrinfo));
  c_in.ai_family = AF_UNSPEC;
  c_in.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(ip, port, &c_in, &info) != 0)
    return (my_perr("getaddrinfo"));
  if ((client->fd = socket(info->ai_family, info->ai_socktype,
			   info->ai_protocol)) == -1)
    return (my_perr("socket"));
  if (connect(client->fd, info->ai_addr, info->ai_addrlen) == -1)
    {
      close(client->fd);
      return (my_perr("connect"));
    }
  freeaddrinfo(info);
  return (0);
}

static void	msg_cmd(t_client *client, char *cmd)
{
  char		tmp[SIZE_CMD];

  if (client->connected)
    {
      if (client->channel)
	{
	  sprintf(tmp, "%s :%s", client->channel, cmd);
	  f_msg(client, epur_str(tmp));
	}
      else
	printf("error: not in channel.\n");
    }
  else
    printf("error: not connected.\n");
}

int		run_cmd(t_client *client, char *cmd)
{
  int		i;
  char		*ft;

  i = 0;
  cmd = epur_str(cmd);
  ft = strtok(strdup(cmd), " ");
  if (ft != NULL && ft[0] == '/')
    {
      while (i < 12)
	{
	  if (strcasecmp(ft, g_funcs[i].cmd) == 0)
	    return (g_funcs[i].p(client, epur_str(strdup(&cmd[strlen(ft)]))));
	  i++;
	}
      printf("command : '%s' not found\n", ft);
    }
  else
    msg_cmd(client, cmd);
  return (0);
}
