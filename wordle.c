#include <libft.h>
#include <stdio.h>

#define RESET "\033[0m" // To reset the color back to default
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GREY "\033[90m"
#define MOVE_CURSOR_UP "\033[F"
#define CLEAR_LINE "\033[2K"
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

int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

char	*str_decapitalize(char *str)
{
	size_t	i;

    if (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			str[i] = to_lower((unsigned char)str[i]);
			++i;
		}
    }
	return (str);
}

int	to_upper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

char	*str_capitalize(char *str)
{
	size_t	i;

    if (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			str[i] = to_upper((unsigned char)str[i]);
			++i;
		}
    }
	return (str);
}

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
	str_capitalize(guess);
	ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE "The word " RED, 1);
	ft_putstr_fd(guess, 1);
	ft_putstr_fd(RESET " doesn't exist\n", 1);
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
bool	guess_the_word(char *wordle_txt, char *guess)
{
	size_t	word_exist;

	word_exist = 0;
	while (true)
	{
		if (get_user_input(guess, 6, "Your answer: ", false) != 5)
		{
			if (ft_strcmp(guess, "exit\n") == 0)
			{
				ft_putstr_fd("Exiting", 1);
				return (false);
			}
			ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
			continue ;
		}
		// ft_putstr_fd("newline", 1);
		str_decapitalize(guess);
		if (does_guess_exist(wordle_txt, guess) == true)
		{
			while (word_exist-- != 0)
				ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
			break ;
		}
		++word_exist;
	}
	return (true);
}

bool	compare_words(char *target, char *guess, char *buff, uint8_t *buff_color)
{
	ft_memset(buff, '_', 6);
	buff[5] = '\0';
	ft_memset(buff_color, KO, 5);
	matches_postion(target, guess, buff, buff_color);

	uint8_t guessed_word;
	uint8_t check_color;
	guessed_word = 0;
	check_color = 0;
	while (check_color < 5)
	{
		if (buff_color[check_color] == OK)
		{
			++guessed_word;
		}
		++check_color;
	}
	if (guessed_word == 5)
		return (true);
	for (uint8_t i = 0; i < 5 && guess[i] != '\0'; ++i) {
		if (buff[i] == '_') {
			buff[i] = guess[i];
			if (is_letter_in_word(target, guess, i) == true) {
				// buff[i] = guess[i];
				buff_color[i] = SOMEWHERE;
			} 
		}

	}
	return (false);
}

void	print_guess_color(char *buff, uint8_t *buff_color)
{
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
	ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
	ft_putendl_fd(print_string, 1);
}

bool	wordle(char *wordle_txt, char *target)
{
	char	guess[6];
	char	buff[6];
	uint8_t	buff_color[5];

	if (guess_the_word(wordle_txt, guess) == false)
	{
		ft_putstr_fd("You decided to stop playing\n", 1);
		return (true);
	}
	str_capitalize(guess);
	if (compare_words(target, guess, buff, buff_color) == true)
	{
		print_guess_color(buff, buff_color);
		ft_putstr_fd("You guessed the word!\n", 1);
		return (true);
	}
	print_guess_color(buff, buff_color);
	return (false);
}

int	main(void)
{
	char	wordle_txt[WORDLE_TXT_SIZE + 1];
	int		word_index;
	char	target[6];
	uint8_t	attempts = 6;

	if (read_fd(wordle_txt) == false || initialize_psuedo_random() == false)
		return (false);
	word_index = rand() % 5758;
	cpy_num(target, wordle_txt + (word_index * 6), 5);
	str_capitalize(target);
	ft_putstr_fd("Target: ", 1);
	ft_putendl_fd(target, 1);
	while (attempts != 0)
	{
		if (wordle(wordle_txt, target) == true)
		{
			return (EXIT_SUCCESS);
		}
		--attempts;
	}
	ft_putstr_fd("You've ran out of attempts!\nThe word was ", 1);
	ft_putendl_fd(target, 1);
	return (EXIT_SUCCESS);
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
