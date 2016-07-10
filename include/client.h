/*
** client.h for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/include
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sat Jun  4 10:55:57 2016 nicolas thouchkaieff
** Last update Sun Jun  5 18:48:12 2016 nicolas thouchkaieff
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "myirc.h"

# define SIZE 4096
# define SIZE_CMD 512

typedef struct	s_client
{
  int		fd;
  int		connected;
  char		*channel;
  char		*nick;
}		t_client;

typedef struct	s_funcs
{
  char		*cmd;
  int		(*p)(t_client *client, char *cmd);
}		t_funcs;

typedef struct s_data
{
  int		*tab;
  char		*last;
  char		*code;
}		t_data;

int		my_connect(t_client *client, char *ip, char *port);
int		first_connect(t_client *client);
int		read_serv(t_client *client, char *cmd);
t_data		init_data(int *tab, char *last, char *code);
int		run_cmd(t_client *client, char *cmd);
int		f_server(t_client *client, char *cmd);
int		f_nick(t_client *client, char *cmd);
int		f_list(t_client *client, char *cmd);
int		f_join(t_client *client, char *cmd);
int		f_part(t_client *client, char *cmd);
int		f_users(t_client *client, char *cmd);
int		f_names(t_client *client, char *cmd);
int		f_msg(t_client *client, char *cmd);
int		f_send_file(t_client *client, char *cmd);
int		f_accept_file(t_client *client, char *cmd);
int		f_disconnect(t_client *client, char *cmd);
int		f_quit(t_client *client, char *cmd);

#endif /* !CLIENT_H_ */
