/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/16 18:31:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_arch(t_binary fileinfo)
{
	int				ret;
	unsigned int	magic_number;

	magic_number = get_magic_number(fileinfo.ptr);
	if (magic_number == MH_MAGIC_64)			/* 64-bits architecture */
		ret = handle_64(&fileinfo);				/* big endian */
	else if (magic_number == MH_CIGAM_64)
		ret = handle_specific_64(&fileinfo);		/* little endian */
	else if (magic_number == MH_MAGIC)			/* 32-bits architecture */
		ret = handle_32(fileinfo);				/* big endian */
	else if (magic_number == MH_CIGAM)
		ret = handle_specific_32(fileinfo);		/* little endian */
	else										/* binaire inconnu */
	{
		ft_putendl_fd("unknow binary architecture", STDERR_FILENO);
		return (ERROR);
	}
	ret = 0;
	return (ret);
}

int		ft_nm(char *file)
{
	int			ret;
	t_binary	fileinfo;

	ret = ERROR;
	ret = setup_struct(&fileinfo, file);
	if (ret == SUCCESS)
		ret = handle_arch(fileinfo);
	clean_struct(&fileinfo);
	return (ret);
}

int		main(int ac, char **av)
{
	int			count;
	int			ret;

	count = 1;
	ret = SUCCESS;
	if (ac < 2)
	{
		ret = ft_nm("a.out");
		return (ret);
	}
	while (av[count] != NULL)
		ret = ft_nm(av[count++]);
	return (ret);
}
