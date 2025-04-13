#include <wordle.h>

//	Static Function
static bool	does_guess_exist(char *txt, char *guess);

bool	load_word_list(char *word_list)
{
	const int	fd = open(PATH_WORLD_TXT, O_RDONLY);

	if (fd == -1)
	{
		perror("Error opening " PATH_WORLD_TXT);
		return (false);
	}
	if (read(fd, word_list, WORDLE_TXT_SIZE) == -1)
	{
		perror("Error reading " PATH_WORLD_TXT);
		return (false);
	}
	if (close(fd) == -1)
	{
		perror("Error closing " PATH_WORLD_TXT);
		return (false);
	}
	word_list[WORDLE_TXT_SIZE] = '\0';
	return (true);
}

bool	seed_random(int *target_index)
{
	const time_t	current_time = time(NULL);

	if (current_time == (time_t)-1)
	{
		perror("Error: Failed to retrieve the current time");
		return (false);
	}
	srand((unsigned int)current_time);
	*target_index = rand() % ((WORDLE_TXT_SIZE / 6) + 1);
	return (true);
}

// 35 = (5 letters * 5 color chars) + 5 letters + 1 terminator + 4 RESET chars
void	print_guess_color(char *buff, uint8_t *colors)
{
	char	formatted_output[35];
	uint8_t index = 0;
	uint8_t	letter_index;

	letter_index = 0;
	while (letter_index < WORD_LENGTH)
	{
		if (colors[letter_index] == KO)
			index += cpy_str(formatted_output + index, GREY);
		else if (colors[letter_index] == SOMEWHERE)
			index += cpy_str(formatted_output + index, YELLOW);
		else 
			index += cpy_str(formatted_output + index, GREEN);
		formatted_output[index] = buff[letter_index];
		++index;
		++letter_index;
	}
	cpy_str0(formatted_output + index, RESET);
	ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
	ft_putendl_fd(formatted_output, 1);
}

bool	get_user_guess(char *word_list, char *guess)
{
	size_t	word_exist;

	word_exist = 0;
	while (true)
	{
		if (get_user_input(guess, 6, "Your answer: ", false) != WORD_LENGTH || \
			str_isalpha(guess) == false)
		{
			if (ft_strcmp(guess, "exit\n") == 0)
				return (false);
			ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
			continue ;
		}
		str_decapitalize(guess);
		if (does_guess_exist(word_list, guess) == true)
		{
			while (word_exist-- != 0)
				ft_putstr_fd(MOVE_CURSOR_UP CLEAR_LINE, 1);
			break ;
		}
		++word_exist;
	}
	return (true);
}

static bool	does_guess_exist(char *txt, char *guess)
{
	size_t	index = 0;

	while (index < WORDLE_TXT_SIZE)
	{
		if (ft_strcmp(txt + index, guess) == 0) {
			// write(1, txt + index, WORD_LENGTH);
			// write(1, guess, WORD_LENGTH);
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
