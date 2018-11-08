/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:27:57 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 18:36:43 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint16_t		reverse_16(int endian, uint16_t x)
{
	if (endian == TRUE)
	{
//		ft_putendl("reverse_16");
		return ((x << 8) | ((x >> 8) & 0xFF));
	}
	return (x);
}

uint32_t		reverse_32(int endian, uint32_t x)
{
	if (endian == TRUE)
	{
//		ft_putendl("reverse_32");
		x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
		return (x << 16) | (x >> 16);
	}
	return (x);
}

uint64_t		reverse_64(int endian, uint64_t x)
{
	if (endian == TRUE)
	{
//		ft_putendl("reverse_64");
		/* x = ((x << 8) & 0xFF00FF00FF00FF00ULL ) | ((x >> 8) & 0x00FF00FF00FF00FFULL ); */
		/* x = ((x << 16) & 0xFFFF0000FFFF0000ULL ) | ((x >> 16) & 0x0000FFFF0000FFFFULL ); */
		x = ((x << 8) & 0xFF00FF00FF00FF00U) | ((x >> 8) & 0x00FF00FF00FF00FFU);
		x = ((x << 16) & 0xFFFF0000FFFF0000U) | ((x >> 16) & 0x0000FFFF0000FFFFU);
		return ((x << 32) | (x >> 32));
	}
	return (x);
}

void			*move_ptr(t_binary *bin, struct stat stat, uint32_t size)
{
	void	*ret;

	ret = NULL;
	if (((off_t)size > stat.st_size) || (bin->ptr + size > bin->ptr + stat.st_size))
		return (NULL);
	return (bin->ptr + size);
}
