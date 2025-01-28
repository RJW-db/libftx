/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common_defs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 17:31:48 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/19 03:39:45 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_DEFS_H
# define COMMON_DEFS_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>			//	int32, uint32
# include <unistd.h>			//	ssize_t STDOUT_FILENO

// # include <sys/types.h>			//	ssize_t

// # include <errno.h>
// # include <stdio.h>				//	perror
// # include <stdlib.h>			//	malloc
// # include <limits.h>			//	INT_MAX PATH_MAX, LLONG_MAX
# if defined(__linux__)
#  include <linux/limits.h>
# endif

//	unsigned datatypes
typedef unsigned char	t_uchr;
//	const datatypes
typedef const void		t_cvoid;
typedef const bool		t_cbool;
typedef const char		t_cchr;
typedef const t_uchr	t_cuchr;
typedef const int8_t	t_cint8;
typedef const int16_t	t_cint16;
typedef const int32_t	t_cint32;
typedef const int64_t	t_cint64;
typedef const uint8_t	t_cuint8;
typedef const uint16_t	t_cuint16;
typedef const uint32_t	t_cuint32;
typedef const uint64_t	t_cuint64;
typedef const size_t	t_csize_t;
typedef const ssize_t	t_cssize_t;
typedef const float		t_cfloat;
typedef const double	t_cdouble;
#endif