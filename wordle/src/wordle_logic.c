#include <wordle.h>

//	Static Functions
static uint8_t	find_exact_matches(char *target, char *guess, uint8_t *colors);


bool	check_guess(char *target, char *guess, uint8_t *colors)
{
	uint8_t	i;

	ft_memset(colors, KO, WORD_LENGTH);
	if (find_exact_matches(target, guess, colors) == WORD_LENGTH)
		return (true);
	i = 0;
	while (i < WORD_LENGTH)
	{
		if (colors[i] == KO && letter_in_word(target, guess, i) == true)
			colors[i] = SOMEWHERE;
		++i;
	}
	return (false);
}

bool	letter_in_word(char *target, char *guess, uint8_t guess_index)
{
	const char	buff_letter = guess[guess_index];
	uint8_t	count_appearances_guess;
	uint8_t	count_appearances_target;
	uint8_t	i;

	i = 0;
	count_appearances_guess = 0;
	while (i < WORD_LENGTH)
	{
		if (guess[i] == buff_letter)
			++count_appearances_guess;
		++i;
	}
	i = 0;
	count_appearances_target = 0;
	while (target[i] != '\0')
	{
		if (target[i] == buff_letter)
			++count_appearances_target;
		++i;
	}
	return (count_appearances_guess <= count_appearances_target);
}

static uint8_t	find_exact_matches(char *target, char *guess, uint8_t *colors)
{
	uint8_t guessed_letters;
	uint8_t i;

	i = 0;
	guessed_letters = 0;
	while (i < WORD_LENGTH)
	{
		if (target[i] == guess[i])
		{
			colors[i] = OK;
			++guessed_letters;
		}
		++i;
	}
	return (guessed_letters);
}
