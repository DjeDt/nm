/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:23:09 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:58:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_data_64(void)
{
	t_sym *tmp;

	tmp = sym;
	while (tmp != NULL)
	{
		if (tmp->sym_value == 0)
			printf("%16s %c %s\n", "", tmp->sym_type, tmp->sym_name);
		else
			printf("%016lx %c %s\n", tmp->sym_value, tmp->sym_type, tmp->sym_name);
		tmp = tmp->next;
	}
}

void	print_data_32(void)
{
	t_sym *tmp;

	tmp = sym;
	while (tmp != NULL)
	{
		if (tmp->sym_value == 0)
			printf("%8s %c %s\n", "", tmp->sym_type, tmp->sym_name);
		else
			printf("%08lx %c %s\n", tmp->sym_value, tmp->sym_type, tmp->sym_name);
		tmp = tmp->next;
	}
}

void	push_chunk(t_sym *new, t_sym **head, int sort_func(const char *s1 ,const char *s2))
{
	t_sym *current;

	if (!new)
		return ;
	if ((*head) == NULL || sort_func((*head)->sym_name, new->sym_name) >= 0)
	{
		new->next = (*head);
		(*head) = new;
	}
	else
	{
		current = (*head);
		while (current->next != NULL && sort_func(current->next->sym_name, new->sym_name) < 0)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

t_sym	*new_chunk(void *sym_name, unsigned long sym_value, char type)
{
	t_sym *ret;

	ret = (t_sym*)malloc(sizeof(t_sym));
	if (!ret)
		return (NULL);
	ret->sym_type = type;
	ret->sym_name = sym_name;
	ret->sym_value = sym_value;
	ret->next = NULL;
	return (ret);
}
