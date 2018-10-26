/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:33:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 14:37:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_x32(t_binary *bin)
{
	uint32_t			count;
	struct mach_header	*header;
	unsigned int		lc_offset;
	struct load_command	load_command;

	count = -1;
	header = (struct mach_header)bin->ptr;
	bin->offset = sizeof(*header);
	load_command = (struct load_command*)((char*)bin->ptr + lc_ofset);
	while (++count < header->ncmds)
	{
		load_command =
	}
	return (SUCCESS);
}
