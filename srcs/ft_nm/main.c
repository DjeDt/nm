/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/07 19:00:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void			setup_struct_values(t_binary *bin, char *path)
{
	bin->offset = 0;
	bin->ptr = NULL;
	bin->sym = NULL;
	bin->sect = NULL;
	bin->path = path;
}

int			handle_arch(t_binary *bin, struct stat stat)
{
	int				ret;
	unsigned int	magic_number;

	ret = 0;
	magic_number = *(unsigned int*)bin->ptr;
	if (magic_number == MH_MAGIC_64)
		ret = handle_x64(bin, stat);
	else if (magic_number == MH_CIGAM_64)
	{
		ft_putendl("1");
		exit(1);
		bin->opt |= FLAG_ENDIAN;
		ret = handle_x64(bin, stat);
//		ft_putendl("ret = handle_endian_x64(&bin);");
	}
	else if (magic_number == MH_MAGIC)
		ret = handle_x32(bin);
	else if (magic_number == MH_CIGAM)
	{
		ft_putendl("ret = handle_endian_x32(&bin);");
		ft_putendl("2");
		exit(1);
		bin->opt |= FLAG_ENDIAN;
		ret = handle_x32(bin);
	}
	else if (magic_number == FAT_MAGIC)
	{
		ft_putendl("fat magic");
		ret = handle_fat(bin, stat);
	}
	else if (magic_number == FAT_CIGAM)
	{
		ft_putendl("fat cygam");
		bin->opt |= FLAG_ENDIAN;
		ret = handle_fat(bin, stat);
	}
	else if (ft_strncmp(bin->ptr, ARMAG, SARMAG) == 0)
		ret = handle_library(bin, stat);
	else
	{
		ft_putendl_fd("unknow architecture", STDERR_FILENO);
		ret = ERROR;
	}
	return (ret);
}

static int			ft_nm(t_binary *bin, char *path)
{
	int			ret;
	struct stat	stat;

	setup_struct_values(bin, path);
	if (setup_struct(bin, &stat) != SUCCESS)
		return (ERROR);
  	ret = handle_arch(bin, stat);
	clean_struct(bin, stat);
	return (ret);
}

/*
  options a faire en premier :

  n : Sort numerically rather than alphabetically.
  p : Don't sort; display in symbol-table order.
  r : Sort in reverse order.

  g : Display only global (external) symbols.
  u : Display only undefined symbols.
  j : Just display the symbol names (no value or type).
  U : Don't display undefined symbols.
  x : Display the symbol table entry's fields in hexadecimal, along with the name as a string.
*/
int					main(int ac, char **av)
{
	int			ret;
	int			count;
	t_binary	bin;

	count = 1;
	if (search_for_flags(&bin, av, count) != SUCCESS)
		return (ERROR);
	if (bin.opt & FLAG_NO_FILE)
		ret = ft_nm(&bin, "a.out");
	while (count < ac)
	{
		if (*av[count] != '-')
			ret = ft_nm(&bin, av[count]);
		count++;
	}
	return (ret);
}
