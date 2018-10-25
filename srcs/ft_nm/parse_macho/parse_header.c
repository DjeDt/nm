/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:36:33 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:31:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned int	get_magic_number(void *data_file)
{
	unsigned int magic_number;

	magic_number = 0;
	if (data_file != NULL)
	{
		magic_number = *(unsigned int *)data_file;
		return (magic_number);
	}
	return (ERROR);
}

struct mach_header_64	*get_header_64(void *data_file)
{
	struct mach_header_64 *header;

	if (data_file != NULL)
	{
		header = (struct mach_header_64*)data_file;
		return (header);
	}
	return (NULL);
}

struct mach_header	*get_header_32(void *data_file)
{
	struct mach_header *header;

	header = NULL;
	if (data_file != NULL)
	{
		header = (struct mach_header*)data_file;
		return (header);
	}
	return (NULL);
}
