/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_library.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:59:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:34:53 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static unsigned int	get_extended_format(struct ar_hdr *ar_header)
{
	unsigned int ret;

	ret = ft_atoi(ar_header->ar_name + ft_strlen(AR_EFMT1));
	return (ret);
}

static int			launch_object_header(t_binary cpy, struct ar_hdr *ob, \
										unsigned int off)
{
	cpy.offset = 0;
	cpy.ptr = move_ptr(&cpy, off + get_extended_format(ob) + sizeof(*ob));
	if (cpy.ptr == NULL)
		return (ERROR);
	ft_printf("\n%s(%s):\n", cpy.path, (char*)ob + sizeof(*ob));
	cpy.offset = 0;
	return (handle_arch(&cpy));
}

static int			parse_object_header(t_binary bin)
{
	int				ret;
	t_binary		bin_cpy;
	struct ar_hdr	*ob_header;

	ret = SUCCESS;
	while (bin.ptr + bin.offset < bin.end)
	{
		ft_memcpy(&bin_cpy, &bin, sizeof(bin));
		if (!(ob_header = move_ptr(&bin, bin.offset)))
		{
			ft_printf_fd(STDERR_FILENO, "error: object header: abort.\n");
			return (ERROR);
		}
		ret = launch_object_header(bin_cpy, ob_header, bin.offset);
		bin.offset += ft_atoi(ob_header->ar_size) + sizeof(*ob_header);
	}
	return (ret);
}

int					handle_library(t_binary *bin)
{
	int				ret;
	struct ar_hdr	*ar_header;

	bin->offset = SARMAG;
	ar_header = move_ptr(bin, bin->offset);
	if (ar_header == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "error: ar_hdr not found. abort.\n");
		return (ERROR);
	}
	bin->offset += sizeof(*ar_header) + ft_atoi(ar_header->ar_size);
	ret = parse_object_header(*bin);
	return (ret);
}
