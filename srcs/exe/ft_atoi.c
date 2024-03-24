/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:32:44 by ranki             #+#    #+#             */
/*   Updated: 2024/03/24 04:06:02 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_short(int *i, char *s, int *sign)
{
	while (s[*i] == '\f' || s[*i] == ' ' || s[*i] == '\n'
		|| s[*i] == '\t' || s[*i] == '\v' || s[*i] == '\r' )
		(*i)++;
	if (s[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (s[*i] == '+')
		(*i)++;
	return (*i);
}

int	ft_atoi(char *s)
{
	int				sign;
	int				n;
	int				i;
	unsigned int	test;

	n = 0;
	sign = 1;
	i = 0;
	i = ft_atoi_short(&i, s, &sign);
	while (s[i] != 0 && s[i] >= '0' && s[i] <= '9')
	{
		test = 10 * n + (s[i] - '0');
		if (!((test <= 2147483647 && sign == 1)
				|| (test <= 2147483648 && sign == -1)))
			return (n);
		n = 10 * n + (s[i] - '0');
		i++;
	}
	return (n * sign);
}

int	ft_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return (-1);
}
