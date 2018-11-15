/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:31:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 17:49:40 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "libft.h"
# include "printf.h"

# include <ar.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>

typedef	struct		s_binary
{
	int				endian;
	unsigned long	opt;
	uint32_t		offset;
	char			*ptr;
	char			*end;
	char			*path;
}					t_binary;

/*
**	Return values
*/

# define NOPE 2
# define ERROR 1
# define SUCCESS 0

/*
**	Options define
*/
# define FLAG_LT (1 << 0)
# define FLAG_NO_FILE (1 << 10)
# define FLAG_MULT_FILE (1 << 11)

/*
** main struct
*/
int						setup_struct(t_binary *bin, struct stat *stat);
int						clean_struct(t_binary *bin, struct stat stat);

/*
** x64
*/
int						handle_x64(t_binary *bin);

/*
** x32
*/
int						handle_x32(t_binary *bin);

/*
** library and fat
*/

/*
** utils
*/
int						search_for_flags(t_binary *bin, char **av, int count);
int						print_error(char *error);

/*
** endianess and offset
*/
void					*move_ptr(t_binary *bin, uint32_t size);
uint16_t				reverse_16(int endian, uint16_t x);
uint32_t				reverse_32(int endian, uint32_t x);
uint64_t				reverse_64(int endian, uint64_t x);

#endif
