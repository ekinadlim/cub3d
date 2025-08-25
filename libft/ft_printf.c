/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:54:09 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/29 19:17:14 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_conversion(char *str, int *i, va_list ap, int *count);

static void	ft_traverse(char *str, int *i, int *count)
{
	while (str[*i] && str[*i] != '%')
	{
		write(1, &str[*i], 1);
		(*count)++;
		(*i)++;
	}
}

static int	ft_check_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_space(char *str, int *i, va_list ap, int *count)
{
	while (str[*i + 1] == ' ')
		(*i)++;
	if (str[*i + 1] == '\0')
		return ((*count) = -1);
	else if (ft_check_set(str[*i + 1], "csdiuxXp%") == 0)
		ft_conversion(str, i, ap, count);
	else
		ft_printchar('%', count);
	return (0);
}

static int	ft_conversion(char *str, int *i, va_list ap, int *count)
{
	if (str[*i + 1] == 'c')
		ft_printchar(va_arg(ap, int), count);
	else if (str[*i + 1] == 's')
		ft_printstr(va_arg(ap, char *), count);
	else if ((str[*i + 1] == 'd' || str[*i + 1] == 'i'))
		ft_check_negative(va_arg(ap, int), str[*i], count);
	else if (str[*i + 1] == 'u')
		ft_printunbr(va_arg(ap, unsigned int), count);
	else if (str[*i + 1] == '%')
		ft_printchar('%', count);
	else if (str[*i + 1] == 'x' || str[*i + 1] == 'X')
		ft_printhex(va_arg(ap, unsigned int), str[*i + 1], count);
	else if (str[*i + 1] == 'p')
		ft_printptr(va_arg(ap, unsigned long), str[*i], count);
	else if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
	{
		ft_check_space(str, i, ap, count);
		return (0);
	}
	else
	{
		ft_printchar('%', count);
		return ((*i)++);
	}
	return ((*i) += 2);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (format == 0)
		return (-1);
	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		ft_traverse((char *)format, &i, &count);
		if (format[i] == '%')
			ft_conversion((char *)format, &i, ap, &count);
		if (count == -1)
		{
			va_end(ap);
			return (-1);
		}
	}
	va_end(ap);
	return (count);
}

/*int main()
{
	printf("\n");
	printf("%d", ft_printf("% c", 'a'));
	printf("\n");
	printf("%d", printf("% c", 'a'));
	printf("\n");
	printf("%d", ft_printf("%d%", -42949672951599));
	printf("\n");
	printf("%d", printf("%d%", -42949672951599));
	printf("\n");
	printf("%d", ft_printf("%d", "ok"));
	printf("\n");
	printf("%d", printf("%d", "ok"));
	printf("\n");
	printf("%d", ft_printf(0, 0, 0));
	printf("\n");
	printf("%d", printf(0, 0, 0));
	printf("\n");
	ft_printf("%p%p", 0, 0);
	printf("\n");
	printf("%p%p", 0, 0); //on mac 0x00x0
	printf("\n");
	printf("%d", ft_printf("wtf%  iw9w ", 2, 120, 212));
	printf("\n");
	printf("%d", printf("wtf%  iw9w ", 2, 120, 212));
	printf("\n");
	ft_printf("%x%w", 0, 0);
	printf("\n");
	printf("%x%w", 0, 0);
	printf("\n");
	printf("%d", ft_printf("wtf% i% wi", 2, 120, 212));
	printf("\n");
	printf("%d", printf("wtf% i% wi", 2, 120, 212));
	printf("\n");
	printf("%d", ft_printf("hey %wttit is 11", 18));
	printf("\n");
	printf("%d", printf("hey %wttit is 11", 18));
	printf("\n");
	printf("%d", ft_printf("hey 1%%%   w"));
	printf("\n");
	printf("%d", ft_printf("hey 1%%%   "));
	printf("\n");
	printf("%d", printf("hey 1%%%   w"));
	printf("\n");
	printf("%d", printf("hey 1%%%   "));
	printf("\n");
	printf("%d", ft_printf("w% i, %d, %s, %wtti", 1, 123, "HI"));
	printf("\n");
	printf("%d", printf("w% i, %d, %s, %wtti", 1, 123, "HI"));
	printf("\n");
}*/
