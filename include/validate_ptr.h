/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_ptr.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/11 22:20:10 by rjw           #+#    #+#                 */
/*   Updated: 2025/05/09 15:58:12 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_PTR_H
# define VALIDATE_PTR_H

static inline bool	str0_ok(const char *s1)
{
	return (s1 != NULL && *s1 != '\0');
}

static inline bool	strs0_ok(const char *s1, const char *s2)
{
	return (str0_ok(s1) == true && str0_ok(s2) == true);
}

//	dp = double pointer
static inline bool	dpstr0_ok(const char **s1)
{
	return (s1 != NULL && *s1 != NULL && **s1 != '\0');
}

//	dp = double pointer
static inline bool	dpstrs0_ok(const char **s1, const char **s2)
{
	return (dpstr0_ok(s1) == true && dpstr0_ok(s2) == true);
}
#endif
