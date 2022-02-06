/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:31:07 by ajana             #+#    #+#             */
/*   Updated: 2022/02/06 21:47:16 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global	g;

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	power(int i)
{
	int	res;

	res = 1;
	while (i)
	{
		res *= 2;
		i--;
	}
	return (res);
}

void	handler1(int signum)
{
	g.square++;
	if (g.square == 8)
	{
		g.count++;
		g.res = realloc(g.res, g.count);
		g.res[g.count - 1] = (char)g.c;
		if (g.c == 0)
		{
			ft_putstr(g.res);
			g.res = strdup("");
			g.count = 0;
		}
		g.c = 0;
		g.square = 0;
	}
}

void	handler2(int signum)
{
	g.c += power(g.square);
	g.square++;
	if (g.square == 8)
	{
		g.count++;
		g.res = realloc(g.res, g.count);
		g.res[g.count - 1] = (char)g.c;
		ft_putstr(g.res);
		if (g.c == 0)
		{
			ft_putstr(g.res);
			g.res = strdup("");
			g.count = 0;
		}
		g.c = 0;
		g.square = 0;
	}
}

int	main(void)
{
	struct sigaction	sa_handler1;
	struct sigaction	sa_handler2;
	int					pid;

	g.c = 0;
	g.count = 0;
	g.square = 0;
	g.res = strdup("");
	pid = getpid();
	printf("PID : %d\n", pid);
	sa_handler1.sa_handler = &handler1;
	sa_handler1.sa_mask = 0;
	sa_handler1.sa_flags = 0;
	sigaction(SIGUSR1, &sa_handler1, NULL);
	sa_handler2.sa_handler = &handler2;
	sa_handler2.sa_mask = 0;
	sa_handler2.sa_flags = 0;
	sigaction(SIGUSR2, &sa_handler2, NULL);
	while(1);
}
