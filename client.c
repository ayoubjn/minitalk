/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:17:01 by ajana             #+#    #+#             */
/*   Updated: 2022/02/09 22:56:17 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin(unsigned int n, int ser_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (n % 2)
			kill(ser_pid, SIGUSR2);
		else
			kill(ser_pid, SIGUSR1);
		n = n / 2;
		i++;
		pause();
	}
	usleep(1000);
	i = 0;
}

void	handler1(int signum)
{
	(void)signum;
}

int	main(int ac, char **av)
{
	struct sigaction	handler;
	int					ser_pid;
	int					i;

	(void)ac;
	i = 0;
	handler.sa_handler = handler1;
	handler.sa_flags = 0;
	handler.sa_mask = 0;
	sigaction(SIGUSR1, &handler, NULL);
	ser_pid = atoi(av[1]);
	while (av[2][i])
	{
		bin((int)av[2][i], ser_pid);
		i++;
	}
	bin((int)av[2][i], ser_pid);
}
