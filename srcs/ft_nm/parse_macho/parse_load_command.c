/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_load_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:45:56 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:33:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

struct load_command	*get_load_command_32(struct mach_header *header)
{
	struct load_command	*load_command;

	load_command = NULL;
	if (header != NULL)
	{
		load_command = (void*)header + sizeof(*header);
		return (load_command);
	}
	return (NULL);
}

struct load_command	*get_load_command_64(struct mach_header_64 *header, t_binary *fileinfo)
{
	struct load_command	*load_command;

	load_command = NULL;
	if (header != NULL)
	{
		fileinfo->offset += sizeof(*header);
		load_command = (void*)header + sizeof(*header);
		return (load_command);
	}
	return (NULL);
}

struct load_command	*next_load_command(struct load_command *load_command, t_binary *fileinfo)
{
	if (load_command != NULL)
	{
		fileinfo->offset += load_command->cmdsize;
		load_command = (void*)load_command + load_command->cmdsize;
	}
	return (load_command);
}
