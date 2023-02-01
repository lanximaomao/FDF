
#include <unistd.h>

void ft_str_upp(char *str)
{
	while (*str)
	{
		while (*str <= 'A' || (*str > 'Z' && *str < 97) || *str > 122)
		{
			write(1, str, 1);
			str++;
		}
		if (*str >= 'A' && *str <= 'Z')
			{
				str++;
				while (*str != '\0' && *str >= 'A' && *str <= 'Z' )
				{
					*str += 32;
					write(1, str, 1);
					str++;
				}



			}
		if (*str >= 'a' && *str <= 'z')
		{
			*str+= 32;

			str++;
			while (*str )
			{
				/* code */
			}

		}
	}

}

int main(int argc, char** argv)
{
	int i;

	i = 1;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return(0);
	}
	while (i < argc)
	{
		ft_str_upp(argv[i]);
		i++;
	}
}
