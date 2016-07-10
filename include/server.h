/*
** myirc.h for myorc in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc/include
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Mon May 16 09:16:45 2016 stephanedarcy simomba
** Last update Sun Jun  5 18:48:35 2016 nicolas thouchkaieff
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "myirc.h"

# define SIZE 4096
# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define MAX_FD 255
# define RING_SIZE 512

typedef void(*fct)();

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  fct		fct_read[MAX_FD];
  fct		fct_write[MAX_FD];
}		t_env;

typedef struct	s_ring_buff
{
  char		buffer[RING_SIZE];
  int		start;
  int		end;
  int		size;
}		t_ring_buff;

typedef struct		s_client
{
  char			*ip;
  int			socket;
  t_ring_buff		*buffer;
  char			*nick;
  char			*username;
  char			*realname;
  char			*channel;
  struct s_channel	*channels;
  char			*hostname;
  int			logged;
}			t_client;

typedef struct		s_list_c
{
  t_client		*client;
  struct s_list_c	*end;
  struct s_list_c	*next;
  struct s_list_c	*prev;
}			t_list_c;

typedef struct		s_channel
{
  char			*name; /* max 50 char */
  char			*topic;
  t_list_c		*list_client;
  struct s_channel	*end;
  struct s_channel	*next;
  struct s_channel	*prev;
}			t_channel;

typedef struct		s_server
{
  int			socket;
  int			port;
  struct sockaddr_in	sin;
  fd_set		fd_read;
  int			fd_max;
  t_env			e;
  t_channel		*channels;
  t_list_c		*clients;
}			t_server;

typedef struct		s_funcs
{
  char			*cmd;
  int			(*p)(t_server *server, t_client *client, char *cmd);
}			t_funcs;

t_client	*get_client_from_nick(t_list_c *list, char *name);
t_channel	*get_channel_from_name(t_channel *list, char *name);
t_client	*get_client_from_username(t_list_c *list, char *name);
t_client	*get_client_from_socket(t_list_c *list, int s);
int		get_args(int ac, char **av, t_server *server);
t_ring_buff	*init_ring();
void		write_in_ring(t_ring_buff *ring, char *str);
char		*read_in_ring(t_ring_buff *ring);
void		print_names(t_server *server, t_client *client, char *chan);
void		init_client(int cs, t_client *client);
int		init_server(t_server *server);
void		add_client(t_server *server, int s);
void		sup_client(t_list_c **list, t_client *client);
void		sup_chanel(t_channel **list, char *name);
int		add_chanel(t_channel **chanel, t_list_c *list_cient, char *nam);
int		my_put_end_in_list(t_list_c **list, t_client *client);
int		my_put_in_list(t_list_c **list, t_client *client);
int		f_nick(t_server *server, t_client *client, char *cmd);
int		f_user(t_server *server, t_client *client, char *cmd);
int		f_list(t_server *server, t_client *client, char *cmd);
int		f_join(t_server *server, t_client *client, char *cmd);
int		f_part(t_server *server, t_client *client, char *cmd);
int		f_users(t_server *server, t_client *client, char *cmd);
int		f_names(t_server *server, t_client *client, char *cmd);
int		f_privmsg(t_server *server, t_client *client, char *cmd);
int		f_send_file(t_server *server, t_client *client, char *cmd);
int		f_accept_file(t_server *server, t_client *client, char *cmd);
int		f_quit(t_server *server, t_client *client, char *cmd);

#endif /* !SERVER_H_ */
