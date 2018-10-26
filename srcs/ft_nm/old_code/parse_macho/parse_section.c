/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:47:54 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 19:16:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char						search_specific_section_64(t_segment_64 *seg_list, uint8_t offset)
{
	uint8_t				count;
	struct section_64	*section;

	section = NULL;
	while (seg_list != NULL)
	{
		count = 0;
		section = get_section_64(seg_list->segment);
		while (++count < seg_list->segment->nsects)
		{
			ft_putendl(section->segname);
			ft_putendl(section->sectname);
			if (count == offset)
			{
				if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
					return ('T');
				else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
					return ('D');
				else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
					return ('B');
			}
			section = get_next_section_64(section);
		}
		seg_list = seg_list->next;
	}
	return ('S');
}

struct section_64			*get_next_section_64(struct section_64 *section)
{
	if (section != NULL)
		section = (struct section_64*)((char*)section + sizeof(*section));

	return (section);
}

struct section_64			*get_section_64(struct segment_command_64 *segment)
{
	struct section_64	*section;

	section = NULL;
	if (segment != NULL)
	{
		section = (struct section_64*)((char*)segment + sizeof(*segment));
		return (section);
	}
	return (NULL);
}
