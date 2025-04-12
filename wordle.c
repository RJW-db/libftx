#include <libft.h>
#include <stdio.h>

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GREY "\033[90m"
#define RESET "\033[0m" // To reset the color back to default
// (25 * 2) + 5 + 1
// 5 * 5 = 25,   25 + 5 + 1
#define PATH_WORLD_TXT "wordle.txt"
#define WORDLE_TXT_SIZE 34542
enum e_correct
{
	KO,
	SOMEWHERE,
	OK
};


bool	is_letter_in_word(char *target, char *guess, uint8_t guess_index)
{
	char	buff_letter = guess[guess_index];
	uint8_t	count_appearances_guess = 0;
	uint8_t	i = 0;

	while (i < 5) {
		if (guess[i] == buff_letter) {
			++count_appearances_guess;
		}
		++i;
	}
	i = 0;
	uint8_t	count_appearances_target = 0;
	while (target[i] != '\0') {
		if (target[i] == buff_letter) {
			++count_appearances_target;
		}
		++i;
	}
	// printf("c %c\ncount_appearances_target %hu\ncount_appearances_guess %hu\n", buff_letter, count_appearances_target, count_appearances_guess);
	if (count_appearances_guess <= count_appearances_target) {
		return (true);
	}
	return (false);
}
void	matches_postion(char *target, char *guess, char *buff, uint8_t *buff_color)
{
	uint8_t i;

	i = 0;
	while (i < 5)
	{
		if (target[i] == guess[i])
		{
			buff[i] = guess[i];
			buff_color[i] = OK;

		}
		++i;
	}
}

bool	does_guess_exist(char *txt, char *guess)
{
	size_t	index = 0;

	while (index < WORDLE_TXT_SIZE)
	{
		if (ft_strcmp(txt + index, guess) == 0) {
			// write(1, txt + index, 5);
			// write(1, guess, 5);
			return (true);
		}
		index += 6;
	}
	puts("Niet bestaand");
	return (false);
}

#include <stdlib.h>
#include <time.h>
#include <fcntl.h>


bool	read_fd(char *wordle_txt)
{
	const int	fd = open(PATH_WORLD_TXT, O_RDONLY);

	if (fd == -1)
	{
		perror("Error opening " PATH_WORLD_TXT);
		return (false);
	}
	if (read(fd, wordle_txt, WORDLE_TXT_SIZE) == -1)
	{
		perror("Error reading " PATH_WORLD_TXT);
		return (false);
	}
	if (close(fd) == -1)
	{
		perror("Error closing " PATH_WORLD_TXT);
		return (false);
	}
	wordle_txt[WORDLE_TXT_SIZE] = '\0';
	return (true);
}

bool	initialize_psuedo_random(void)
{
	const time_t	current_time = time(NULL);

	if (current_time == (time_t)-1)
	{
		perror("Error: Failed to retrieve the current time");
		return (false);
	}
	srand((unsigned int)current_time);
	return (true);
}

int	main(void)
{
	char		wordle_txt[WORDLE_TXT_SIZE + 1];

	if (read_fd(wordle_txt) == false || initialize_psuedo_random() == false)
		return (EXIT_FAILURE);

	for (int k = 0; k < 15; ++k)
	{
		int word = rand() % 5758;
		printf("%d\n", word);
		write(1, wordle_txt + (word * 6), 6);
	}

	uint8_t buff_color[5];
	char buff[6];
	char *target = "hello";
	char guess[6];

	ft_memset(buff, '_', 6);
	buff[5] = '\0';
	ft_memset(buff_color, KO, 5);
	while (true) {
		if (get_user_input(guess, 6, "Your answer: ") != 5) {
			if (ft_strcmp(guess, "exit\n") == 0) {
				puts("Exiting");
				return (0);
			}
			continue ;
		}
		if (does_guess_exist(wordle_txt, guess) == true) {
			break ;
		}
	}
	printf("%s\n", guess);
	exit(0);
	matches_postion(target, guess, buff, buff_color);
	// printf("%s<\n", buff);

	for (uint8_t i = 0; i < 5 && guess[i] != '\0'; ++i) {
		if (buff[i] == '_') {
			buff[i] = guess[i];
			if (is_letter_in_word(target, guess, i) == true) {
				// buff[i] = guess[i];
				buff_color[i] = SOMEWHERE;
			} 
		}

	}
	char print_string[35]; // 35 = (5 letters * 5 color chars) + 5 letters + 1 terminator + 4 RESET chars
	uint8_t print_index = 0;
	for (uint8_t i = 0; i < 5; ++i) {
		if (buff_color[i] == KO)
		{
			print_index += cpy_str(print_string + print_index, GREY);
		}
		else if (buff_color[i] == SOMEWHERE)
		{
			print_index += cpy_str(print_string + print_index, YELLOW);
		}
		else 
		{
			print_index += cpy_str(print_string + print_index, GREEN);
		}
		print_string[print_index] = buff[i];
		++print_index;
	}
	cpy_str0(print_string + print_index, RESET);
	// printf("%s\n", buff);
	printf("%s\n", print_string);
	printf("print_string %zu\n", ft_strlen(print_string));
	return (0);
}





// uint8_t	count_occurences(char *buff, char c)
// {
// 	uint8_t count;
// 	uint8_t i;

// 	count = 0;
// 	i = 0;
// 	while (i < 6)
// 	{
// 		if (buff[i] == c)
// 			++count;
// 		++i;
// 	}
// 	return (count);
// }
