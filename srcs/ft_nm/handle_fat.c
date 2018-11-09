/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:32:52 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/09 18:58:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		parse_fat_header_x32(t_binary *bin, struct stat stat)
{
	int				ret;
	struct fat_arch *fat;
	t_binary		bin_cpy;

	fat = move_ptr(bin, stat, bin->offset);
	ft_memcpy(&bin_cpy, bin, sizeof(*bin));
	if (bin_cpy.ptr == NULL)
		return (ERROR);
	bin_cpy.ptr = move_ptr(bin, stat, reverse_32(bin->endian, fat->offset));
	ret = handle_arch(&bin_cpy, stat);
	return (ret);
}

int		handle_fat(t_binary *bin, struct stat stat)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct fat_header	*fat_header;

	count = -1;
	ret = SUCCESS;
	if (!(fat_header = (struct fat_header*)move_ptr(bin, stat, bin->offset)))
		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_FHDR_STR));
	limit = reverse_32(bin->endian, fat_header->nfat_arch);
	bin->offset += sizeof(*fat_header);
	if (!(bin->opt & FLAG_MULT_FILE))
		bin->opt |= FLAG_MULT_FILE;
	while (++count < limit)
	{
		if ((ret = parse_fat_header_x32(bin, stat)) != SUCCESS)
			return (ERROR);
		bin->offset += sizeof(struct fat_arch);
	}
	return (ret);
}
