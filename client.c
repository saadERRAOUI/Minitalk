/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:02 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/14 22:51:50 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	*encode_char(int c)
{
	int	*binary;
	int	i;

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

static void	send_char(int *c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c[i] == 0)
			kill(pid, SIGUSR1);
		else if (c[i] == 1)
			kill(pid, SIGUSR2);
		usleep(2000);
	}
	free(c);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;
	int	*seg;

	i = 0;
	if (ac == 3)
	{
		if (!ft_atoi_check(av[1], &pid) || pid < 0)
		{
			ft_putstr_fd("PID NOT VALID !\n", 1);
			return (ft_putstr_fd("Please recheck your PID param !\n", 1), 1);
		}
		while (av[2][i])
		{
			seg = encode_char(av[2][i]);
			send_char(seg, pid);
			i++;
		}
		return (0);
	}
	ft_putstr_fd("INCORRECT NUMBER OF PARAMS !\n", 1);
	return (ft_putstr_fd("Ensure that you enter the required infos !\n", 1), 1);
}
