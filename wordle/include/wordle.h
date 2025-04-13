#ifndef WORDLE_H
# define WORDLE_H
#include <libft.h>
#include <stdio.h>
#include <is_ctype1_str.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

#define RESET "\033[0m" // To reset the color back to default
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GREY "\033[90m"
#define MOVE_CURSOR_UP "\033[F"
#define CLEAR_LINE "\033[2K"
#define PATH_WORLD_TXT "wordle.txt"
#define WORDLE_TXT_SIZE 34542
#define WORD_LENGTH 5

enum e_correct
{
	KO,
	SOMEWHERE,
	OK
};

//	wordle_io
bool	load_word_list(char *word_list);
bool	seed_random(int *target_index);
void	print_guess_color(char *buff, uint8_t *colors);
bool	get_user_guess(char *word_list, char *guess);

//	wordle_logic
bool	check_guess(char *target, char *guess, uint8_t *colors);
bool	letter_in_word(char *target, char *guess, uint8_t guess_index);
#endif
