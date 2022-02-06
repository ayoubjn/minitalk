/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:17:01 by ajana             #+#    #+#             */
/*   Updated: 2022/02/06 21:40:56 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	s = 0;

void	bin(unsigned int n, int ser_pid)
{
	while (s < 8)
	{
		if (n % 2)
			kill(ser_pid, SIGUSR2);
		else
			kill(ser_pid, SIGUSR1);
		n = n / 2;
		usleep(50);
		s++;
	}
	s = 0;
}

int	main(int ac, char **av)
{
	int	ser_pid;
	int	i;

	i = 0;
	ser_pid = atoi(av[1]);
	while (av[2][i])
	{
		bin((int)av[2][i], ser_pid);
		i++;
	}
	bin((int)av[2][i], ser_pid);
}
