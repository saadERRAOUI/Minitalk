/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:04 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/14 22:25:51 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_pow(int pow, int num)
{
	if (num == 0)
		return (0);
	if (pow == 0)
		return (1);
	else if (pow == 1)
		return (num);
	return (num * ft_pow(pow - 1, num));
}

static char	decoder(int *sequence)
{
	int	i;
	int	n;
	int	result;

	i = 0;
	n = 7;
	result = 0;
	while (i < 8)
	{
		result += (sequence[i] * ft_pow(n, 2));
		i++;
		n--;
	}
	return ((char)result);
}

static void	hdl_signals(int signal)
{
	static int	i;
	static int	sequence[8];
	char		c;

	if (signal == SIGUSR1)
		sequence[i] = 0;
	else if (signal == SIGUSR2)
		sequence[i] = 1;
	i++;
	if (i == 8)
	{
		c = decoder(sequence);
		write(1, &c, 1);
		i = 0;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("SERVER_PROCESS_ID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n[SERVER] Listening...\n", 1);
	signal(SIGUSR1, hdl_signals);
	signal(SIGUSR2, hdl_signals);
	while (1)
		pause();
	return (0);
}
