/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminal_markup.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/13 18:20:01 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/01/30 21:16:12 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_MARKUP_H
# define TERMINAL_MARKUP_H

# define MARKUP "\033[1;32m"
# define MARKDOWN "\033[0m\n"

# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdarg.h>
# include <common_defs.h>

/**
 * @brief Prints a string with with markup given by user.
 * 
 * @note The last argument must be 0.
 * 
 * @param[in] str is which get the markup.
 * @param[in] ... varied number given for markup
 * 
 * Text Styles
 * 0	Reset All Styles
 * 1	Bold
 * 2	Dim
 * 3	Italic
 * 4	Underline
 * 5	Blink
 * 6	Rapid Blink
 * 7	Reverse Video
 * 
 * Text Colours
 * 30	Black
 * 31	Red
 * 32	Green
 * 33	Yellow
 * 34	Blue
 * 35	Magenta
 * 36	Cyan
 * 37	White
 * 
 * Background Colours
 * 40	Black
 * 41	Red
 * 42	Green
 * 43	Yellow
 * 44	Blue
 * 45	Magenta
 * 46	Cyan
 * 47	White
*/
void	markup(t_cchr *str, ...);

/**
 * @brief Prints a character with full width in terminal.
 * 
 * @param[in] c Use `const uint32_t` for Unicode characters.
 */
void	print_full_width(t_csize_t c);

#endif