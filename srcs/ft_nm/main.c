/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 20:55:43 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			handle_arch(t_binary *bin)
{
	int				ret;
	unsigned int	magic_number;

	magic_number = *(unsigned int*)bin->ptr;
	if (magic_number == MH_MAGIC_64)
		ret = handle_x64(bin);
	else if (magic_number == MH_CIGAM_64)
		ft_putendl("ret = handle_endian_x64(&bin);");
	else if (magic_number == MH_MAGIC)
		ret = handle_x32(bin);
	else if (magic_number == MH_CIGAM)
		ft_putendl("ret = handle_endian_x32(&bin);");
	else
	{
		ft_putendl_fd("unknow binary architecture", STDERR_FILENO);
		return (ERROR);
	}
	ret = 0;
	return (ret);
}

static void			setup_struct_values(t_binary *bin)
{
	bin->opt = 0;
	bin->offset = 0;
	bin->ptr = NULL;
	bin->path = "a.out";
	bin->sym = NULL;
	bin->sect = NULL;
}

static int			ft_nm(t_binary *bin, char **av, int *count)
{
	int			ret;
	struct stat	stat;

	setup_struct_values(bin);

	if (handle_flags(bin, av, count) == ERROR)
		return (ERROR);

	if (av[(*count)] != NULL)
		bin->path = av[(*count)];

	if ((*count) > 1 && av[(*count)] != NULL)
		ft_printf("\n%s:\n", bin->path);

	if (setup_struct(bin, &stat) == ERROR)
		return (ERROR);

	ret = handle_arch(bin);
	clean_struct(bin, stat);
	return (ret);
}

int					main(int ac, char **av)
{
	int			ret;
	int			count;
	t_binary	bin;

	count = 1;
	if (ac < 2)
		ret = ft_nm(&bin, av, &count);
	else
	{
		while (av[count] != NULL && count < ac)
		{
			ret = ft_nm(&bin, av, &count);
			count++;
		}
	}
	return (ret);
}
