#include <wrap_functions.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

typedef struct ok
{
	size_t i;
}	t_ok;

bool	set_malloc_amount(size_t size, void *ptr)
{
	static	t_ok *ok = NULL;

write(1, "hello\n", 6);
	if (ok == NULL)
	{
		ok = (t_ok *)ptr;
	}
	else if (ok->i > 0)
	{
		write(1, "middle\n", 7);
		ok->i--;
	} else {
		write(1, "SHOULDN'T see this message, use malloc_toggle()\n", 48);
		return (false);
	}
	return (true);
}

#include <libft.h>
int main(void)
{
	t_ok	ok;
	ok.i = 2;
	write(1, "first\n", 6);

	malloc_handler(0, &ok, set_malloc_amount);
	malloc_toggle(SET_MALLOC);
	// malloc_toggle(SET_MALLOC);
	char *str = malloc(5);
	free(str);
	char *arr = ft_strdup("mooi\n");
	if (arr)
		write(1, arr, 5);
	// free(arr);
	return (0);
}