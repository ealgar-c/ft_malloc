/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:05:50 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 14:37:01 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static bool	ft_aux(char c, int dot, bool post)
{
	if (!c && dot == 0)
		return (true);
	if (!c && dot == 1 && post)
		return (true);
	return (false);
}

bool	ft_check_atod(char *str)
{
	int		i;
	int		dot;
	bool	post;

	i = 0;
	dot = 0;
	post = false;
	if (str[i] == '-')
		i++;
	while (str[i] && (ft_isdigit(str[i]) == 1 || str[i] == '.'))
	{
		if (str[i] == '.')
			dot++;
		if (dot != 0 && ft_isdigit(str[i]) == 1)
			post = true;
		i++;
	}
	if (ft_aux(str[i], dot, post))
		return (true);
	return (false);
}

static double	ft_pow(double base, int exp)
{
	double	result;
	int		i;

	result = 1.0;
	if (exp < 0)
	{
		i = 0;
		while (i < -exp)
		{
			result *= base;
			i++;
		}
		return (1.0 / result);
	}
	i = 0;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}

double	ft_atod(char *str)
{
	char	*save;
	int		i;
	double	res;
	double	n;
	bool	neg;

	i = 0;
	neg = false;
	if (str[i] == '-')
	{
		str = ft_substr(str, 1, ft_strlen(str) - 1);
		neg = true;
	}
	while (str[i] && str[i] != '.')
		i++;
	save = ft_substr(str, 0, i);
	n = ft_atoi(save);
	free(save);
	save = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	res = ft_atoi(save) / ft_pow(10, ft_strlen(save));
	res += n;
	free(save);
	if (neg)
		return (free(str), res * -1);
	return (res);
}
