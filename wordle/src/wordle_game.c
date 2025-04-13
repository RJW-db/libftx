#include <wordle.h>

//	Static Function
static bool	play_round(char *word_list, char *target);

int	main(void)
{
	char	word_list[WORDLE_TXT_SIZE + 1];
	char	target[WORD_LENGTH + 1];
	int		target_index;
	uint8_t	attempts;

	if (load_word_list(word_list) == false || seed_random(&target_index) == false)
		return (false);
	cpy_num(target, word_list + (target_index * (WORD_LENGTH + 1)), WORD_LENGTH);
	str_capitalize(target);
	// ft_putstr_fd("Target: ", 1);
	// ft_putendl_fd(target, 1);

	attempts = 6;
	while (attempts != 0)
	{
		if (play_round(word_list, target) == true)
		{
			return (EXIT_SUCCESS);
		}
		--attempts;
	}
	ft_putstr_fd("You've ran out of attempts!\nThe word was ", 1);
	ft_putendl_fd(target, 1);
	return (EXIT_SUCCESS);
}

static bool	play_round(char *word_list, char *target)
{
	char	guess[WORD_LENGTH + 1];
	uint8_t	colors[WORD_LENGTH];

	if (get_user_guess(word_list, guess) == false)
	{
		ft_putstr_fd("You decided to stop playing\n", 1);
		return (true);
	}
	str_capitalize(guess);
	if (check_guess(target, guess, colors) == true)
	{
		print_guess_color(guess, colors);
		ft_putstr_fd("You guessed the word!\n", 1);
		return (true);
	}
	print_guess_color(guess, colors);
	return (false);
}
