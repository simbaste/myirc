/*
** ring_buff.c for myirc in /Users/thouch_n/rendu/PSU/PSU_2015_myirc/src/server
**
** Made by nicolas thouchkaieff
** Login   <thouch_n@epitech.net>
**
** Started on  Wed Jun  1 10:30:09 2016 nicolas thouchkaieff
** Last update Sat Jun  4 10:52:05 2016 nicolas thouchkaieff
*/

#include "server.h"

t_ring_buff	*init_ring()
{
  t_ring_buff	*ring;

  if ((ring = malloc(sizeof(t_ring_buff))) == NULL)
    return (NULL);
  memset(ring->buffer, 0, RING_SIZE);
  ring->start = -1;
  ring->end = -1;
  ring->size  = 0;
  return (ring);
}

void	write_in_ring(t_ring_buff *ring, char *str)
{
  int	cursor;
  int	i;

  i = 0;
  ring->start = (ring->end + 1) % RING_SIZE;
  ring->end = (ring->start + strlen(str) - 1) % RING_SIZE;
  cursor = ring->start;
  ring->size = strlen(str);
  while (cursor != ring->end + 1)
    {
      ring->buffer[cursor] = str[i];
      i++;
      cursor = (cursor + 1) % RING_SIZE;
    }
}

char	*read_in_ring(t_ring_buff *ring)
{
  char	*str;
  int	i;
  int	cursor;

  i = 0;
  cursor = ring->start;
  if ((str = malloc(sizeof(char) * ring->size + 1)) == NULL)
    return (NULL);
  memset(str, 0, ring->size + 1);
  while (i < ring->size)
    {
      str[i] = ring->buffer[cursor];
      i++;
      cursor = (cursor + 1) % RING_SIZE;
    }
  return (str);
}
