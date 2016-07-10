/*
** list_chanel.c for list_chanel in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc/src/function
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 20 06:19:14 2016 stephanedarcy simomba
** Last update Mon Jun 20 23:05:46 2016 stephanedarcy simomba
*/

#include <stdlib.h>
#include "server.h"

static int	func_list(t_channel **chanel, t_list_c *list_client, char *name)
{
  t_channel	*elem;

  if ((elem = malloc(sizeof(t_channel))) == NULL)
    return (my_err("Malloc failed.\n"));
  elem->next = NULL;
  elem->list_client = list_client;
  elem->name = name;
  elem->topic = NULL;
  if ((*chanel)->end == NULL)
    {
      (*chanel)->next = elem;
      elem->prev = (*chanel);
      (*chanel)->end = elem;
    }
  else
    {
      (*chanel)->end->next = elem;
      elem->prev = (*chanel)->end;
      (*chanel)->end = elem;
    }
  return (0);
}

int	add_chanel(t_channel **chanel, t_list_c *list_client, char *name)
{
  if (*chanel == NULL)
    {
      printf("nul\n");
      if ((*chanel = malloc(sizeof(t_channel))) == NULL)
	return (my_err("Malloc failed.\n"));
      (*chanel)->list_client = list_client;
      (*chanel)->name = name;
      (*chanel)->topic = NULL;
      (*chanel)->end = NULL;
      (*chanel)->prev = NULL;
      (*chanel)->next = NULL;
    }
  else
    if (func_list(chanel, list_client, name) == -1)
      return (-1);
  return (0);
}

static void	change_end(t_channel **list, t_channel *newend)
{
  t_channel	*tmp;

  tmp = *list;
  while (tmp)
    {
      tmp->end = newend;
      tmp = tmp->next;
    }
}

static void	listlast(t_channel **list, t_channel *tmp, char *name)
{
  t_channel	*temp;

  if (tmp && strcmp(tmp->name, name) == 0)
    {
      temp = tmp->prev;
      free(tmp);
      temp->next = NULL;
      change_end(list, temp);
    }
}

void		sup_chanel(t_channel **list, char *name)
{
  t_channel	*tmp;

  tmp = *list;
  if (tmp && strcmp(tmp->name, name) == 0)
    {
      *list = tmp->next;
      if (*list)
	(*list)->end = tmp->end;
      free(tmp);
      return ;
    }
  while (tmp && tmp->next != NULL)
    {
      if (strcmp(tmp->name, name) == 0)
	{
	  tmp->next->prev = tmp->prev;
	  tmp->prev->next = tmp->next;
	  free(tmp);
	  return ;
	}
      tmp = tmp->next;
    }
  listlast(list, tmp, name);
}
