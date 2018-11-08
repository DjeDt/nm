/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_library.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:59:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 20:58:36 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static unsigned int	get_extended_format(struct ar_hdr *ar_header)
{
	unsigned int ret;

	ret = ft_atoi(ar_header->ar_name + ft_strlen(AR_EFMT1));
	return (ret);
}

static int			parse_object_header(t_binary bin, struct stat stat)
{
	int				ret;
	t_binary		bin_cpy;
	struct ar_hdr	*ob_header;

	ret = SUCCESS;
	ft_memcpy(&bin_cpy, &bin, sizeof(bin));
	while ((off_t)bin.offset < stat.st_size)
	{
		if (!(ob_header = (struct ar_hdr*)move_ptr(&bin, stat, bin.offset)))
			return (ERROR);
		bin_cpy.offset = 0;
		bin_cpy.ptr = move_ptr(&bin, stat, bin.offset + get_extended_format(ob_header) + sizeof(*ob_header));
		ft_printf("\n%s(%s):\n", bin.path, (char*)ob_header + sizeof(*ob_header));
		ret = handle_arch(&bin_cpy, stat);
		bin.offset += ft_atoi(ob_header->ar_size) + sizeof(*ob_header);
	}
	return (ret);
}

int		handle_library(t_binary *bin, struct stat stat)
{
	int				ret;
	struct ar_hdr	*ar_header;

	bin->offset = SARMAG;
	ar_header = move_ptr(bin, stat, bin->offset);
	if (ar_header == NULL)
		return (ERROR);
	bin->offset += sizeof(*ar_header);
	bin->offset += ft_atoi(ar_header->ar_size);
	ret = parse_object_header(*bin, stat);
	return (ret);
}
