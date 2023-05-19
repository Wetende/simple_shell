#ifndef MY_HEADER_H
#define MY_HEADER_H


void print_words(char **words);:
/* Declaration of _getenv function */
char *_getenv(const char *name);

/* Declaration of _unsetenv function */
int _unsetenv(const char *name);

/* Declaration of get_input function */
void get_input(void);

/* Declaration of split_string function */
char **split_string(char *str, const char *delimiters);

/* Declaration of print_arguments function */
void print_arguments(char **words);

#endif /* MY_HEADER_H */

