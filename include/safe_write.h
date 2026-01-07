/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_write.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/05/09 15:57:54 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_WRITE_H
# define SAFE_WRITE_H

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

# define safe_write(fd, buf, len)												\
	do {																		\
		ssize_t n__ = write(fd, buf, len);										\
		if (n__ == -1) {														\
			char *err__ = strerror(errno);										\
			dprintf(STDERR_FILENO, "%s: %s (fd=%d, wanted=%zu, wrote=%zd)\n",   \
				__func__, err__, fd, (size_t)(len), n__);						\
		}																		\
	} while (0)

#endif
