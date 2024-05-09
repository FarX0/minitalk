/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by tfalchi           #+#    #+#             */
/*   Updated: 2024/04/24 15:02:47 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "libft/ft_printf.h"

static void	ft_signal_err(void)
{
	write (2, "Error: unexpected signal behavior\n", 34);
	exit(1);
}

void	ft_print_word(char *c, int *received, int *client_pid, int *bit)
{
	ft_printf("%c", *c);
	if (*c == '\0')
	{
		ft_printf("\t<%d byte received from [%d]>\n", *received, *client_pid);
		*received = 0;
		*c = 0;
		if (kill(*client_pid, SIGUSR2) == -1)
			ft_signal_err();
		return ;
	}
	*bit = 0;
}

static void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int	client_pid = 0;
	static int	bit = 0;
	static char	c = 0;
	static int	received = 0;
	static int	current_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		client_pid = current_pid;
		bit = 0;
		c = 0;
		received = 0;
	}
	c |= (sig == SIGUSR1);
	received++;
	bit++;
	if (bit == 8)
		ft_print_word(&c, &received, &client_pid, &bit);
	c <<= 1;
	usleep(100);
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_printf("PID [%d]\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
