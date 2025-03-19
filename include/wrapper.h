/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrap_functions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 02:01:03 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/19 03:17:50 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAP_FUNCTIONS_H
# define WRAP_FUNCTIONS_H

# include <stdbool.h>
# include <stdio.h>			//	perror
# include <dlfcn.h>			//	dlsym, dlerror
# include <stdarg.h>		//	va_list
# include <fcntl.h>			//	mode_t
# include <unistd.h>
# include <errno.h>

# define _GNU_SOURCE		//	RTLD_NEXT
# define OG_MALLOC_ENABLED true
# define OG_MALLOC_DISABLED false
# define RETRIEVE_MALLOC true
# define SET_MALLOC false
# define ERR_HANDLING_BUFFER 1024

/**
 * @brief Wrapper for the malloc function on macOS.
 * Using dlsym with RTLD_NEXT ensures that the real malloc function is
 * resolved without causing recursion, as dlsym does not call malloc
 * when resolving core system functions already loaded in memory.
 */

/**
 * @brief Handles dynamic symbol resolution for wrapped functions.
 *
 * This function is used to intercept and manage calls to dynamically loaded
 * symbols, allowing custom behavior or testing for specific functions.
 */
void	*dlsym_handler(void *handle, const char *function_name);

/**
 * @brief Wrapper for the open system call.
 *
 * Intercepts calls to the open system call to provide custom behavior,
 * such as logging, testing, or modifying parameters before delegating
 * to the original open function.
 *
 * @param[in] path: The file path to open.
 * @param[in] oflag: Flags specifying the access mode and behavior.
 * @param[in] ...: Optional mode_t argument for file permissions (if O_CREAT is used).
 *
 * Return: File descriptor on success, or -1 on failure with errno set.
 */
int		open(const char *path, int oflag, ...);

/**
 * @brief A generic handler for managing wrapped functions.
 *
 * This function provides a common interface for handling various wrapped
 * system calls or library functions. It can be customized to perform
 * pre-processing, post-processing, or error handling for the wrapped
 * function.
 *
 * @param[in] ptr Pointer to an argument that will be passed to the custom 
 *                function for additional context or data, e.g. a struct.
 * @param[in] custom Function pointer to a custom handler that intercepts 
 *                   and overrides the behavior of the main function.
 * @return: The result of the wrapped function, or an error code on failure.
 */
bool	general_handler(void *ptr, bool (*custom)(void *));

/**
 * @brief Toggles a boolean or state variable.
 *
 * This function flips the value of a given boolean or state variable
 * between true and false (or 1 and 0). Useful for managing on/off states
 * or enabling/disabling functionality.
 *
 * @param[in,out] state Pointer to the variable to be toggled.
 */
bool	general_toggle(bool check);

/**
 * @brief Handles and logs error messages.
 *
 * This function writes the provided error message to the standard error
 * output (STDERR) in chunks, ensuring proper handling of long messages.
 * It also appends a newline character to the message.
 *
 * @param[in] str The error message to be logged.
 */
void	wrap_error_handling(const char *str);

/**
 * @brief Wrapper for the malloc function on Linux.
 *
 * This function allows custom behavior for memory allocation by replacing
 * calls to malloc with calls to __wrap_malloc during linking.
 *
 * @details To compile with the malloc wrapper, use the following command:
 * gcc -I <include_path> -Wl,--wrap=malloc main.c libft.a
 *
 * Note: The `-Wl,--wrap=malloc` flag instructs the linker to redirect all
 * calls to malloc to __wrap_malloc, enabling custom handling of memory
 * allocation.
 *
 * @param[in] size The size of the memory block to allocate.
 * @return A pointer to the allocated memory block, or NULL on failure.
 */
void	*__wrap_malloc(size_t size);
void	*__real_malloc(size_t size);

/**
 * @brief Custom malloc function that allows for custom behavior.
 * 
 * @attention If the custom function decides to fail, set errno = ENOMEM.
 * @attention don't use optimization flags like -Ofast or -03
 * This function wraps the standard malloc function and allows for custom 
 * behavior to be executed before the actual memory allocation.
 * If a custom function is set using malloc_handler,
 * it will be called before the actual allocation.
 * The custom function can decide whether to proceed with the allocation or not.
 * 
 * @param[in] size The size of the memory allocation.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
*/
void	*malloc(size_t size);

/**
 * @brief malloc_handler - A wrapper function for custom malloc behavior.
 * @attention Ensure to call `reset_static_pointers_and_errno()` at the end of
 * the scope to reset static pointers and errno to their default states.
 * @attention don't use optimization flags like -Ofast or -03
 * 
 * @param[in] size The size of the memory allocation.
 * @param[in] ptr: Pointer to custom struct used in the custom function.
 * @param[in] custom: A custom function to handle malloc behavior.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 * 
 * This function allows you to set a custom malloc function that can be used
 * to handle memory allocation. The custom function should have the following
 * signature:
 * 
 * bool custom_malloc_func(size_t size, void *ptr);
 * 
 * Example usage:
 * 
 * typedef struct	set_limit{
 *      int max_malloc_usage = 3;
 * }	t_set_limit;
 * 
 * bool my_custom_malloc(size_t size, void *ptr)
 * {
 *     t_set_limit limit = (t_set_limit)ptr
 *     if (limit->max_malloc_usage != 0) {
 *         errno = ENOMEM;
 *         return (false);
 *     }
 *     limit->max_malloc_usage--;
 *     return (true);
 * }
 * 
 * malloc_handler(0, &my_struct, my_custom_malloc);
*/
bool	malloc_handler(size_t size, void *ptr, bool (*custom)(size_t, void *));

/**
 * @brief Toggles or retrieves the current malloc behavior.
 *
 * @param[in] check Indicates the operation to perform:
 *                  - Use `RETRIEVE_MALLOC` to retrieve the current malloc state.
 *                  - Use `SET_MALLOC` to toggle the malloc state.
 *
 * @return The current state of malloc behavior after the operation.
 *         - `true` indicates standard malloc is enabled.
 *         - `false` indicates custom malloc is enabled.
 */
bool	malloc_toggle(bool check);
bool	malloc_toggle(bool check);

/**
 * @brief Resets the malloc testing state.
 *
 * This function resets the number of malloc attempts to 0 and ensures
 * that errno is cleared if a zero-sized malloc call does not fail.
 *
 * @param[in,out] malloc_attempts Pointer to the malloc attempts counter
 *                                to be reset.
 */
void	reset_malloc_state(size_t *malloc_attempts);

#endif