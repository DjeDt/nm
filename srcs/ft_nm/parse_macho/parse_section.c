/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:47:54 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/22 14:09:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

struct section_64			*get_specific_section_64(struct segment_command_64 *segment, const char *needle)
{
	unsigned int		count;
	struct section_64	*section;

	count = 0;
	if (segment != NULL)
	{
		section = get_section_64(segment);
		while (section != NULL && (++count < segment->nsects))
		{
			if (ft_strcmp(section->sectname, needle) == 0)
				return (section);
			section = get_next_section_64(section);
		}
	}
	return (NULL);
}

void						print_section_64_info(struct section_64 *section, unsigned int *offset, t_binary *fileinfo)
{
	if (section != NULL)
	{
		printf("--- Section info:\nname: %s\naddr = %llu\nsize = %llu\nsection offset= %u\nalign = %u\n",
			   section->sectname,
			   section->addr,
			   section->size,
			   section->offset,
			   section->align
			);
		(*offset) += sizeof(struct segment_command_64);

		/* struct section_64 *test = (struct section_64*)((char*)fileinfo->ptr + (*offset)); */
		/* if (test == section) */
		/* 	printf("offset is ok\n"); */
		/* else */
		/* 	printf("offset is not ok: %p | %p\n", section, test); */
		printf("\n");
	}
	(void)fileinfo;
}

struct section_64			*get_section_64(struct segment_command_64 *segment)
{
	struct section_64	*section;

	section = NULL;
	if (segment != NULL)
	{
		section = (struct section_64*)segment + sizeof(*segment);
		return (section);
	}
	return (NULL);
}

struct section_64			*get_next_section_64(struct section_64 *section)
{
	if (section != NULL)
		section = (struct section_64*)section + sizeof(*section);
	return (section);
}
