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

# define SAFE_WRITE(fd, buf, len)											\
	do {																	\
		ssize_t ret = write(fd, buf, len);									\
		if (ret == -1) {													\
			char errbuf[256];												\
			char *err = strerror(errno);									\
			int n = snprintf(errbuf, sizeof(errbuf),						\
				"%s:%d (%s): %s (fd=%d, wanted=%zu, wrote=%zd)\n",			\
				__FILE__, __LINE__, __func__, err, fd, (size_t)(len), ret);	\
			if (n > 0) {													\
				ret = write(STDERR_FILENO, errbuf, (size_t)n);				\
				(void)ret;													\
			}																\
		}																	\
	} while (0)

#endif
