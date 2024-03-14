/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:02 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/14 13:47:35 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	ft_atoi(const char *str)
{
	long	number;
	int		i;
	int		is_negative;

	number = 0;
	i = 0;
	is_negative = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
	{
		is_negative = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (number < 0 && is_negative == -1)
			return (0);
		else if (number < 0 && is_negative == 1)
			return (-1);
		number = number * 10 + str[i++] - '0';
	}
	return (number * is_negative);
}

static int  *encode_char(int c)
{
	int	*binary;
	int	i;
	int _c;

	i = 8;
	binary = (int *)malloc(sizeof(int) * 8);
	if (!binary)
		return (NULL);
	while (i-- != -1) 
	{
		binary[i] = c % 2;
		c /= 2;
	}
	return (binary);
}

static void send_char(int *c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c[i] == 0)//SIGUSR1
			kill(pid, SIGUSR1);
		else if (c[i] == 1)//SIGUSR2
			kill(pid, SIGUSR2);
		usleep(2000);
	}
	free(c);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;
	int *seg;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid < 0)
			return (1);
		while (av[2][i])
		{
			seg = encode_char(av[2][i]);
			send_char(seg, pid);
			i++;
		}
	}
	return (0);
}