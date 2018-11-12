/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:32:52 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 20:41:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		parse_fat_header_x32(t_binary *bin, struct stat stat)
{
	int				ret;
	struct fat_arch *fat;
	t_binary		bin_cpy;

	if (!(fat = move_ptr(bin, stat, bin->offset)))
		return (ERROR);
	ft_memcpy(&bin_cpy, bin, sizeof(*bin));
	if (bin_cpy.ptr == NULL)
		return (ERROR);
	bin_cpy.ptr = move_ptr(bin, stat, reverse_32(bin->endian, fat->offset));
	if (bin_cpy.ptr == NULL)
		return (ERROR);
	bin_cpy.offset = 0;
	ret = handle_arch(&bin_cpy, stat);
	return (ret);
}

int search_for_x64(t_binary *bin, struct stat stat, uint32_t limit)
{
	uint32_t			count;
	unsigned long		tmp_off;
	struct fat_arch		*tmp;

	count = -1;
	tmp_off = bin->offset;
	while (++count < limit)
	{
		if (!(tmp = move_ptr(bin, stat, tmp_off)))
			return (0);
		if (reverse_32(bin->endian, tmp->cputype) == CPU_TYPE_X86_64)
		{
			bin->offset = tmp_off;
			return (parse_fat_header_x32(bin, stat));
		}
		tmp_off += sizeof(struct fat_arch);
	}
	return (-1);
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
	if ((ret = search_for_x64(bin, stat, limit)) != -1)
		return (ret);
	if (!(bin->opt & FLAG_MULT_FILE) && limit > 1)
		bin->opt |= FLAG_MULT_FILE;
	if (limit == 1)
		ft_printf("%s:\n", bin->path);
   	while (++count < limit)
	{
		if ((ret = parse_fat_header_x32(bin, stat)) != SUCCESS)
			return (ret);
		bin->offset += sizeof(struct fat_arch);
	}
	return (ret);
}
