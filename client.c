/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:02 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/01 17:13:12 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int  *encode_char(int c)
{
	int	*binary;
	int	i;
	int _c;

	i = 7;
	// _c = (int)c;
	// printf("____CHAR %i\n\n", c);
	binary = (int *)malloc(sizeof(int) * 8);
	if (!binary)
		return (NULL);
	while (i-- != -1)
	{
		binary[i] = c % 2;
		c /= 2;
	}
	// printf("\n");
	return (binary);
}

static void send_char(int *c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c[i] == 0) //SIGUSR1
			kill(pid, SIGUSR1);
		else if (c[i] == 1)//SIGUSR2
			kill(pid, SIGUSR2);
		usleep(500);
	}
	free(c);
}

int	main(int ac, char **av)
{
	int	i;
	int *seg;

	i = 0;
	while (av[2][i])
	{
		// printf("av[2][%i] = %c\n", i, av[2][i]);
		seg = encode_char(av[2][i]);
		send_char(seg, atoi(av[1]));
		i++;
	}
	return (0);
}