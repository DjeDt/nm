/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:07:49 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 15:29:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	push_symbol_chunk(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ft_strcmp((*symbol)->name, new->name) >= 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && ft_strcmp(tmp->next->name, new->name) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return ;
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = (uint32_t)list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	push_symbol_chunk(new, &bin->sym);
}

void	parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return ;
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	push_symbol_chunk(new, &bin->sym);
}
