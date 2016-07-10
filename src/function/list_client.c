/*
** list_client.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Tue May 24 18:25:37 2016 stephanedarcy simomba
** Last update Sun Jun  5 15:26:06 2016 nicolas thouchkaieff
*/

#include <stdlib.h>
#include "server.h"

static int	func_list(t_list_c **list, t_client *client)
{
  t_list_c	*elem;

  if ((elem = malloc(sizeof(t_list_c))) == NULL)
    return (my_err("Malloc failed.\n"));
  elem->next = NULL;
  elem->client = client;
  if ((*list)->end == NULL)
    {
      (*list)->next = elem;
      elem->prev = (*list);
      (*list)->end = elem;
    }
  else
    {
      (*list)->end->next = elem;
      elem->prev = (*list);
      (*list)->end = elem;
    }
  return (0);
}

int	my_put_end_in_list(t_list_c **list, t_client *client)
{
  if (*list == NULL)
    {
      if ((*list = malloc(sizeof(t_list_c))) == NULL)
	return (my_err("Malloc failed.\n"));
      (*list)->client = client;
      (*list)->end = NULL;
      (*list)->prev = NULL;
      (*list)->next = NULL;
    }
  else
    if (func_list(list, client) == -1)
      return (-1);
  return (0);
}

static void	change_end(t_list_c **list, t_list_c *newend)
{
  t_list_c	*tmp;

  tmp = *list;
  while (tmp)
    {
      tmp->end = newend;
      tmp = tmp->next;
    }
}

static void	listlast(t_list_c **list, t_list_c *tmp, t_client *client)
{
  t_list_c	*temp;

  if (tmp && tmp->client == client)
    {
      temp = tmp->prev;
      free(tmp);
      temp->next = NULL;
      change_end(list, temp);
    }
}

void		sup_client(t_list_c **list, t_client *client)
{
  t_list_c	*tmp;

  tmp = *list;
  if (tmp && tmp->client == client)
    {
      *list = tmp->next;
      if (*list)
	(*list)->end = tmp->end;
      free(tmp);
      return ;
    }
  while (tmp && tmp->next != NULL)
    {
      if (tmp->client == client)
	{
	  tmp->next->prev = tmp->prev;
	  tmp->prev->next = tmp->next;
	  free(tmp);
	  return ;
	}
      tmp = tmp->next;
    }
  listlast(list, tmp, client);
}
