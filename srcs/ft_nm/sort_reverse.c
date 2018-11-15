/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:56:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:56:50 by ddinaut          ###   ########.fr       */
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
	if ((*symbol) == NULL || sort((*symbol), new) <= 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next && sort(tmp->next, new) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}
