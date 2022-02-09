/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:31:07 by ajana             #+#    #+#             */
/*   Updated: 2022/02/09 22:53:57 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global	g;

void	byte(void)
{
	if (!g.res)
		g.res = strdup("");
	g.count++;
	g.res = ft_realloc(g.res, g.count);
	g.res[g.count - 1] = (char)g.c;
	g.res[g.count] = 0;
	if (g.c == 0)
	{
		ft_putstr(g.res);
		free(g.res);
		g.res = NULL;
		g.count = 0;
	}
	g.c = 0;
	g.square = 0;
}

void	handler1(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g.square++;
	if (g.square == 8)
		byte();
	kill(info->si_pid, SIGUSR1);
}

void	handler2(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)signum;
	g.c += power(g.square);
	g.square++;
	if (g.square == 8)
		byte();
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_handler1;
	struct sigaction	sa_handler2;
	int					pid;

	g.c = 0;
	g.count = 0;
	g.square = 0;
	pid = getpid();
	printf("PID : %d\n", pid);
	sa_handler1.sa_sigaction = &handler1;
	sa_handler1.sa_mask = 0;
	sa_handler1.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_handler1, NULL);
	sa_handler2.sa_sigaction = &handler2;
	sa_handler2.sa_mask = 0;
	sa_handler2.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa_handler2, NULL);
	while (1)
		;
}
