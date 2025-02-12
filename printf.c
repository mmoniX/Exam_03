/*
Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.
*/

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int ft_char(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_str(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (str[len] != '\0')
	{
		if (write(1, &str[len], 1) < 0)
			return (-1);
		len++;
	}
	return (len);
}

int ft_nbr(int nbr)
{
	int len;

	len = 0;
	if (nbr < 0)
	{
		if (nbr == -2147483648)
		{
			len = ft_str("-2147483648");
			return (len);
		}
		if (ft_char('-') < 0)
			return (-1);
		len++;
		nbr = -nbr;
	}
	if (nbr >= 10)
		len += ft_nbr(nbr / 10);
	if (len != -1)
		len += ft_char("0123456789"[nbr % 10]);
	return (len);
}

int	ft_lowhex(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_lowhex(nb / 16);
	if (len != -1)
		len += ft_char("0123456789abcdef"[nb % 16]);
	return (len);
}

int ft_arguments (va_list args, char c)
{
	int res;

	res = 0;
	if (c == 's')
		res = ft_str(va_arg(args, char *));
	else if (c == 'd')
		res = ft_nbr(va_arg(args, int));
	else if (c == 'x')
		res = ft_lowhex(va_arg(args, unsigned int));
	return (res);
}

int ft_printf(const char *input, ...)
{
	int	i;
	int len;
	va_list args;

	i = 0;
	len = 0;
	va_start(args, input);
	while (input[i] != '\0')
	{
		if (input[i] == '%' && len != -1)
		{
			len += ft_arguments(args, input[i + 1]);
			i++;
		}
		else if (len != -1)
			len += ft_char(input[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// int main()
// {
// 	int res1 = ft_printf("%s\n", "-100");
// 	int res2 = printf("%s\n", "-100");
// 	printf("res1: %i\n", res1);
// 	printf("res2: %i\n", res2);
// 	return (0);
// }
