/*
** toolbox.h for qsd in /home/quach_a/backupzappy/Zappy/inc
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 21:00:11 2015 Jonathan Quach
** Last update Sun Jul  5 21:00:11 2015 Jonathan Quach
*/

#ifndef TOOLBOX_H_
# define TOOLBOX_H_

/*
** print.c
*/
void	printstr(int, char const *);
void	safe_write(int, int, char const *);
int	display_error(char const *);

/*
** xclose.c
*/
void	xclose(int);

/*
** epurate a buffer of its excessive delimiters (void)
*/
void	epur_buffer(char *, char *);

/*
** it tries to find a char in a string (0 : -1)
*/
int	find_char_from_str(char, char *);

/*
** free a char **
*/
void	free_wordtab(char **);

/*
** count the number of words in a string (int : 0)
*/
int	get_nb_word(char *, char *);

/*
** allocate and return an array of words (char** : NULL)
*/
char	**str_to_wordtab(char *, char *);

#endif /* !TOOLBOX_H_ */
