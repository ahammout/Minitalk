/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:48:32 by ahammout          #+#    #+#             */
/*   Updated: 2022/03/15 20:06:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int	client_pid;
	static int	bit;
	static int	c;

	(void)context;
	if ((*info).si_pid != client_pid)
	{
		c = 0;
		bit = 0;
		client_pid = (*info).si_pid;
	}
	c <<= 1;
	c = c | (sig == SIGUSR2);
	bit ++;
	if (bit == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	pid = getpid();
	action.sa_sigaction = &sig_handler;
	ft_printf("====> Here is the process ID : [ %d ]\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		pause();
	}
	exit(EXIT_FAILURE);
}