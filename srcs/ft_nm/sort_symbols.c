/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:40:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:56:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		sort(t_symbol *curr, t_symbol *new)
{
	int ret;

	if (!curr || !new)
		return (0);
	ret = ft_strcmp(curr->name, new->name);
	if (!ret || !curr->name || !new->name)
		return (curr->value >= new->value);
	return (ret);
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
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	alpha_sort(t_symbol *new, t_symbol **symbol)
{
	t_symbol	*tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || sort((*symbol), new) > 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && sort(tmp->next, new) <= 0)
			tmp = tmp->next;
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
