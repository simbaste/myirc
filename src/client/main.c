/*
** main.c for client in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc/src/client
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Mon May 16 09:14:57 2016 stephanedarcy simomba
** Last update Sun Jun  5 18:52:07 2016 nicolas thouchkaieff
*/

#include "client.h"

void		init(t_client *client)
{
  client->fd = 0;
  client->connected = 0;
  client->channel = NULL;
  client->nick = strdup("nico2294");
}

int		main()
{
  t_client	client;
  char		buf[SIZE_CMD];
  int		n;

  init(&client);
  memset(buf, 0, SIZE_CMD);
  write(1, client.nick, strlen(client.nick));
  write(1, " $>", 3);
  while ((n = read(0, buf, SIZE_CMD)) > 0)
    {
      buf[n - 1] = 0;
      if (run_cmd(&client, buf) == -1)
	return (-1);
      write(1, client.nick, strlen(client.nick));
      if (client.connected)
	write(1, "(connected) ", strlen("(connected)"));
      if (client.channel)
	write(1, client.channel, strlen(client.channel));
      write(1, " $>", 3);
      memset(buf, 0, SIZE_CMD);
    }
  return (0);
}
