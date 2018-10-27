/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:14:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 20:54:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	set_option(unsigned int *opt, int flag)
{
	if ((*opt & flag))
	{
		ft_putendl("already set");
		return (ERROR);
	}
	else
		(*opt) |= flag;
	return (SUCCESS);
}

static int	print_help(void)
{
	ft_printf("%s", NM_USAGE);
	exit(EXIT_SUCCESS);
}

static int	handle_options(unsigned int *opt, char *input)
{
	input++;
	while ((*input) != '\0')
	{
		if (*input == 'h')
			return (print_help());
		else if (*input == 'A')
			set_option(opt, FLAG_A);
		else if (*input == 'n')
			set_option(opt, FLAG_n);
		else if (*input == 'o')
			set_option(opt, FLAG_o);
		else if (*input == 'p')
			set_option(opt, FLAG_p);
		else if (*input == 'r')
			set_option(opt, FLAG_r);
		else if (*input == 'u')
			set_option(opt, FLAG_u);
		else if (*input == 'U')
			set_option(opt, FLAG_U);
		else if (*input == 'm')
			set_option(opt, FLAG_m);
		else if (*input == 'x')
			set_option(opt, FLAG_x);
		else if (*input == 'j')
			set_option(opt, FLAG_j);
		else if (*input == 't')
			set_option(opt, FLAG_t);
		else
			return (handle_error("nm", FLAG_UKW, input));
		input++;
	}
	return (SUCCESS);
}

int			handle_flags(t_binary *bin, char **av, int *count)
{
	while (av[(*count)] != NULL && *av[(*count)] == '-')
	{
		if (handle_options(&bin->opt, av[(*count)]) == ERROR)
			return (ERROR);
		(*count)++;
	}
	return (SUCCESS);
}
