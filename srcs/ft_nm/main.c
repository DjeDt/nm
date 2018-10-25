/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 20:09:32 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		handle_arch(t_binary bin)
{
	int				ret;
	unsigned int	magic_number;

	magic_number = get_magic_number(bin.ptr);
	if (magic_number == MH_MAGIC_64)			/* 64-bits architecture */
		ret = handle_x64(&bin);//		ret = handle_64(&bin);				/* big endian */
	else if (magic_number == MH_CIGAM_64)
		ret = handle_specific_64(&bin);		/* little endian */
	else if (magic_number == MH_MAGIC)			/* 32-bits architecture */
		ret = handle_32(&bin);				/* big endian */
	else if (magic_number == MH_CIGAM)
		ret = handle_specific_32(&bin);		/* little endian */
	else										/* binaire inconnu */
	{
		ft_putendl_fd("unknow binary architecture", STDERR_FILENO);
		return (ERROR);
	}
	ret = 0;
	return (ret);
}

static int		ft_nm(const char *input)
{
	int			fd;
	int			ret;
	t_binary	bin;
	struct stat	stat;

	fd = 0;
	ret = setup_struct(&bin, input, fd, &stat);
	close(fd);
	if (ret == SUCCESS)
	{
		ret = handle_arch(bin);
		clean_struct(&bin, stat);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	int			count;
	int			ret;

	if (ac < 2)
		ret = ft_nm("a.out");
	else
	{
		count = 0;
		while (av[++count] != NULL)
			ret = ft_nm(av[count]);
	}
	return (ret);
}
