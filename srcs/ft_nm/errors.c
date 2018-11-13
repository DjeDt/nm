/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:28:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/13 14:44:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		print_error(char *error)
{
	if (error)
		ft_printf_fd(STDERR_FILENO, "%s\n", error);
}

int		handle_error(const char *input, int type, const char *error)
{
	if (type == IS_DIR)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", input, error);
	else if (type == NOT_ALLOWED)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", input, error);
	else if (type == FLAG_UKW)
		ft_printf_fd(STDERR_FILENO, "%s: %s '%c'.\n%s\n", \
					input, FLAG_UKW_STR, *error, FLAG_UKW_STR2);
	else if (type == DOUBLE_FLAG_ERR)
		ft_printf_fd(STDERR_FILENO, "%s: for the '%c' option: %s\n", \
					input, *error, DOUBLE_FLAG_ERR_STR);
	else if (type == MISSING_PTR_ERR)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", input, error);
	return (ERROR);
}
