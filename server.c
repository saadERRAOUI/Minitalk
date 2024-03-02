/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:04 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/02 19:34:46 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <math.h>

static int ft_pow(int pow, int num)
{
	int _num;

	_num = num;
	if (num == 0)
		return (0);
	if (pow == 0)
		return (1);
	else if (pow == 1)
		return (num);
	while (pow-- != 1)
		num *= _num;
	return (num);
}

char decoder(int *sequence)
{
   int i = 0;
   int n = 7;
   int result = 0;
   while (i < 8)
   {
		result += (sequence[i] * pow(2, n));
		i++;
		n--;
   }
	return (char)result;
}


void hdl_signals(int signal)
{
	// printf("SIGNALS %i\n\n", signal);
	static int i;
    char c;
    static int sequence[8];

	// i = 0;
    if (signal == SIGUSR1)
        sequence[i] = 0;
    else if (signal == SIGUSR2)
        sequence[i] = 1;
	i++;
    if (i == 8)
    {
        //we have a byte: decode, write and restart
		// int  y = 0;
		// while (y < 8)
		// {
		// 	printf("%i", sequence[y]);
		// 	y++;
		// }
		// printf("\n");
        c = decoder(sequence);
        write(1, &c, 1);
        i = 0;
    }
}

int	main(int ac, char **av)
{
	int pid = getpid();
	// int *ptr = {1, 0 ,};
	printf("__GET_PID %i\n", pid);
	
	while (1)
	{
		signal(SIGUSR1, hdl_signals);
		signal(SIGUSR2, hdl_signals);
	}
	return (0);
}