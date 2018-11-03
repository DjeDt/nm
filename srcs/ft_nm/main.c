/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/03 14:13:11 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			handle_arch(t_binary *bin)
{
	int				ret;
	unsigned int	magic_number;

	ret = SUCCESS;
	magic_number = *(unsigned int*)bin->ptr;
	if (magic_number == MH_MAGIC_64)
		ret = handle_x64(bin);
	else if (magic_number == MH_CIGAM_64)
		ft_putendl("ret = handle_endian_x64(&bin);");
	else if (magic_number == MH_MAGIC)
		ret = handle_x32(bin);
	else if (magic_number == MH_CIGAM)
		ft_putendl("ret = handle_endian_x32(&bin);");
	else if (ft_strncmp((char*)bin->ptr, ARMAG, SARMAG) == 0)
		handle_library(bin);
	else
	{
		ft_putendl_fd("unknow binary architecture", STDERR_FILENO);
		ret = ERROR;
	}
	return (ret);
}

static void			setup_struct_values(t_binary *bin, char *path)
{
	bin->offset = 0;
	bin->ptr = NULL;
	bin->sym = NULL;
	bin->sect = NULL;
	if (path == NULL)
		bin->path = "a.out";
	else
		bin->path = path;
}

static int			ft_nm(t_binary *bin, char **av, int *count)
{
	int			ret;
	struct stat	stat;

	while ((av[(*count)] != NULL) && (*av[(*count)] == '-'))
		(*count)++;
	setup_struct_values(bin, av[(*count)]);
	if (setup_struct(bin, &stat) == ERROR)
		return (ERROR);
	if (bin->opt & FLAG_NAME)
		ft_printf("\n%s:\n", bin->path);
	ret = handle_arch(bin);
	clean_struct(bin, stat);
	return (ret);
}

void print_opt(unsigned long int i)
{
	if (i & FLAG_UA)
		ft_printf("%c is set\n", 'A');
	if (i & FLAG_LN)
		ft_printf("%c is set\n", 'n');
	if (i & FLAG_LO)
		ft_printf("%c is set\n", 'o');
	if (i & FLAG_LP)
		ft_printf("%c is set\n", 'p');
	if (i & FLAG_LR)
		ft_printf("%c is set\n", 'r');
	if (i & FLAG_LU)
		ft_printf("%c is set\n", 'u');
	if (i & FLAG_UU)
		ft_printf("%c is set\n", 'U');
	if (i & FLAG_LM)
		ft_printf("%c is set\n", 'm');
	if (i & FLAG_LX)
		ft_printf("%c is set\n", 'x');
	if (i & FLAG_LJ)
		ft_printf("%c is set\n", 'j');
	if (i & FLAG_LT)
		ft_printf("%c is set\n", 't');
}

/*
  options a faire en premier :
  g : Display only global (external) symbols.
  n : Sort numerically rather than alphabetically.
  o : Prepend file or archive element name to each output line, rather than only once.
  p : Don't sort; display in symbol-table order.
  r : Sort in reverse order.
  u : Display only undefined symbols.
  U : Don't display undefined symbols.
  x : Display the symbol table entry's fields in hexadecimal, along with the name as a string.
  j : Just display the symbol names (no value or type).
*/
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
		if (search_for_flags(&bin, av, count) != SUCCESS)
			return (ERROR);
//		print_opt(bin.opt);
		while (av[count] != NULL && count < ac)
		{
			ret = ft_nm(&bin, av, &count);
			count++;
		}
	}
	return (ret);
}
