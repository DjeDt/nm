/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:40:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 20:15:21 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	rev_sort_numericaly(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ((*symbol)->value <= new->value))
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && (tmp->next->value > new->value))
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	rev_alpha_sort(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ft_strcmp((*symbol)->name, new->name) <= 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next && ft_strcmp(tmp->next->name, new->name) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	sort_numericaly(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ((*symbol)->value > new->value))
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && (tmp->next->value <= new->value))
		{
			tmp = tmp->next;
		}
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	alpha_sort(t_symbol *new, t_symbol **symbol)
{
	int			ret;
	t_symbol	*tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ft_strcmp((*symbol)->name, new->name) > 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL)
		{
			ret = ft_strcmp(tmp->next->name, new->name);
			if (!ret || !tmp->next->name || !new->name)
			{
				if (tmp->next->value >= new->value)
					break ;
			}
			else if (ret > 0)
				break ;
			tmp = tmp->next;
		}
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	no_sort(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if (*symbol == NULL)
		(*symbol) = new;
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
