/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:07:49 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/05 15:32:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		sort_numericaly(size_t v1, size_t v2)
{
	if (v1 == v2)
		return (0);
	else if (v1 < v2)
		return (-1);
	else
		return (1);
}

int		rev_sort_numericaly(size_t v1, size_t v2)
{
	if (v1 < v2)
		return (1);
	if (v1 > v2)
		return (-1);
	return (0);
}

int		dont_sort(const char *s1, const char *s2)
{
	(void)s1;
	(void)s2;
	return (0);
}

int		reverse_sort(const char *s1, const char *s2)
{
	int ret;

	ret = ft_strcmp(s1, s2);
	if (ret == 0)
		return (0);
	if (ret < 0)
		return (1);
	return (-1);
}

static void	*handle_sort_flag(unsigned long opt)
{
	void *ret;

	ret = ft_strcmp;
	if (opt & FLAG_LR)
		ret = reverse_sort;
   	if (opt & FLAG_LP)
		ret = dont_sort;
	return (ret);
}

static void	push_symbol_chunk(unsigned long opt, t_symbol *new, t_symbol **symbol, int sort(const char *s1 ,const char *s2))
{
	t_symbol *tmp;

	if (!new)
		return ;
	if (opt & FLAG_LN)
	{
		if ((*symbol) == NULL || sort_numericaly((*symbol)->value, new->value) > 0)

		{
			new->next = (*symbol);
			(*symbol) = new;
		}
		else
		{
			tmp = (*symbol);
			while (tmp->next != NULL && sort_numericaly(tmp->next->value, new->value) <= 0)
				tmp = tmp->next;
			new->next = tmp->next;
			tmp->next = new;
		}
		return ;
	}

	if ((*symbol) == NULL || sort((*symbol)->name, new->name) > 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && sort(tmp->next->name, new->name) <= 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;
	void	*sort;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return ;
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = (uint32_t)list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	sort = handle_sort_flag(bin->opt);
	push_symbol_chunk(bin->opt, new, &bin->sym, sort);
}

void	parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;
	void	*sort;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return ;
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	sort = handle_sort_flag(bin->opt);
	push_symbol_chunk(bin->opt, new, &bin->sym, sort);
}
