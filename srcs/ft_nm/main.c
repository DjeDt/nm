/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 14:44:11 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		handle_arch(t_binary bin)
{
	int				ret;
	unsigned int	magic_number;

	magic_number = *(unsigned int*)bin.ptr;
	if (magic_number == MH_MAGIC_64)			/* 64-bits architecture */
		ret = handle_x64(&bin);//		ret = handle_64(&bin);				/* big endian */
	else if (magic_number == MH_CIGAM_64)
		ft_putendl("ret = handle_endian_x64(&bin);");
	else if (magic_number == MH_MAGIC)			/* 32-bits architecture */
		ret = handle_x32(&bin);				/* big endian */
	else if (magic_number == MH_CIGAM)
		ft_putendl("ret = handle_endian_x32(&bin);");		/* little endian */
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
		ret = SUCCESS;
		count = 0;
		while (av[++count] != NULL)
			ret = ft_nm(av[count]);
	}
	return (ret);
}
