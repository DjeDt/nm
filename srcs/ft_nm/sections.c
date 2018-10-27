/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:08:09 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 12:12:38 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

static t_section	*create_section_chunk_x32(struct section *section)
{
	t_section *new;

	if (!(new = (t_section*)malloc(sizeof(char) * sizeof(t_section))))
		return (NULL);
	new->segname = section->segname;
	new->sectname = section->sectname;
	new->addr = section->addr;
	new->offset = section->offset;
	new->size = section->size;
	new->next = NULL;
	return (new);
}

static t_section	*create_section_chunk_x64(struct section_64 *section)
{
	t_section *new;

	if (!(new = (t_section*)malloc(sizeof(char) * sizeof(t_section))))
		return (NULL);
	new->segname = section->segname;
	new->sectname = section->sectname;
	new->addr = section->addr;
	new->offset = section->offset;
	new->size = section->size;
	new->next = NULL;
	return (new);
}

void	push_section_chunk_x32(struct section *chunk, t_section **section)
{
	t_section *tmp;

	if (*section == NULL)
		(*section) = create_section_chunk_x32(chunk);
	else
	{
		tmp = (*section);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x32(chunk);
	}
}

void		push_section_chunk_x64(struct section_64 *chunk, t_section **section)
{
	t_section *tmp;

	if (*section == NULL)
		(*section) = create_section_chunk_x64(chunk);
	else
	{
		tmp = (*section);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x64(chunk);
	}
}
