// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   multiply.c                                         :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2025/05/05 14:43:53 by rde-brui      #+#    #+#                 */
// /*   Updated: 2025/05/05 15:59:21 by rde-brui      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include <libft.h>
// #include <stdio.h>
// typedef struct s_multiply
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*s3;
	
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	s1_len;
// }

// void	add_to_str(size_t c1, char *s2, char *s3, size_t s2_len)
// {
// 	size_t onthouden = 0;
// 	size_t accumalative = c1 * (s2[s2_len] - '0');
// 	if (accumalative > 10)
// 		onthouden / 10;
// 	s3
// 	printf("%zu\n", c1);
// 	printf("%c\n", s2[s2_len]);
// 	printf("%ld\n", accumalative);
// 	exit(0);
// }

// char	*multiply_str(char *s1, char *s2)
// {
// 	s1 = "12";
// 	s2 = "34";
// 	size_t s1_len = ft_strlen(s1) - 1;
// 	size_t s2_len = ft_strlen(s2) - 1;
// 	char	*s3 = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (s3 == NULL)
// 		return (NULL);
	
// 	size_t reset_len;
// 	// size_t pow_of_10 = 0;
// 	size_t s3_i = s1_len + s2_len - 1;
// 	// size_t onthouden = 0;

// 	while (s1_len != 0)
// 	{
// 		reset_len = s2_len;
// 		add_to_str(s1[s1_len] - '0', s2, s3, reset_len);
// 		// size_t accumalative = (s1[s1_len] - '0') * (s2[reset_len] - '0');
// 		// printf("%c\n", s1[s1_len]);
// 		// printf("%c\n", s2[reset_len]);
// 		// printf("%ld\n", accumalative);
// 		// exit(0);
// 		// s3[s3_i] = (s1[s1_len] - '0');
// 	}
	
// 	// puts(s1);
// 	// printf("%d\n", '7' - '0');
// 	// printf("%d\n", 81 % 10);
// 	// printf("%d\n", 81 / 10);
// 	(void)s1;
// 	(void)s2;
// 	return (NULL);
// }
