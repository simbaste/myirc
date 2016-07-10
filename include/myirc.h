/*
** myirc.h for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/include
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Sat Jun  4 10:49:13 2016 nicolas thouchkaieff
** Last update Sat Jun  4 19:14:00 2016 nicolas thouchkaieff
*/

#ifndef MYIRC_H_
# define MYIRC_H_

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <signal.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

int             my_err(char *str);
int             my_perr(char *str);
ssize_t         my_send(int socket, char *msg);
char            *epur_str(char *str);

#endif /* !MYIRC_H_ */
