/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 21:02:46 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:38:11 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

struct segment_command	*get_segment_32(struct load_command *load_command)
{
	struct segment_command	*segment;

	segment = NULL;
	if (load_command != NULL)
	{
		segment = (struct segment_command*)((char*)load_command);
		return (segment);
	}
	return (NULL);
}

struct segment_command_64	*get_segment_64(struct load_command *load_command)
{
	struct segment_command_64	*segment;

	segment = NULL;
	if (load_command != NULL)
	{
		segment = (struct segment_command_64*)((char*)load_command);
		return (segment);
	}
	return (NULL);
}
