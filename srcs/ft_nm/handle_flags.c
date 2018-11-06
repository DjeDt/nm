/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:14:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/06 18:55:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	set_option(unsigned long int *opt, int flag, char c)
{
	if ((*opt & flag))
	{
		handle_error("input", DOUBLE_FLAG_ERR, &c);
		return (FLAG_ERROR);
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

static int	handle_options(unsigned long int *opt, char *input)
{
	input++;
	while ((*input) != '\0')
	{
		if (*input == 'h')
			return (print_help());
		else if (*input == 'A')
			set_option(opt, FLAG_UA, (*input));
		else if (*input == 'n')
			set_option(opt, FLAG_LN, (*input));
		else if (*input == 'p')
			set_option(opt, FLAG_LP, (*input));
		else if (*input == 'r')
			set_option(opt, FLAG_LR, (*input));
		else if (*input == 'u')
			set_option(opt, FLAG_LU, (*input));
		else if (*input == 'U')
			set_option(opt, FLAG_UU, (*input));
		else if (*input == 'm')
			set_option(opt, FLAG_LM, (*input));
		else if (*input == 'x')
			set_option(opt, FLAG_LX, (*input));
		else if (*input == 'j')
			set_option(opt, FLAG_LJ, (*input));
		else if (*input == 't')
			set_option(opt, FLAG_LT, (*input));
		else
			return (handle_error("ft_nm", FLAG_UKW, input));
		input++;
	}
	return (SUCCESS);
}

int			search_for_flags(t_binary *bin, char **av, int count)
{
	int ret;
	int	flag_name;

	bin->opt = 0;
	flag_name = 0;
	ret = SUCCESS;
	while (av[count] != NULL)
	{
		if (*av[count] == '-')
		{
			if ((ret = handle_options(&bin->opt, av[count])) != SUCCESS)
				return (ret);
		}
		else
			flag_name++;
		count++;
	}
	if (flag_name >= 2)
		set_option(&bin->opt, FLAG_NAME, '\0');
	return (ret);
}
