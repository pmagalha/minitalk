/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagalha <pmagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:17:16 by pmagalha          #+#    #+#             */
/*   Updated: 2023/06/05 15:19:36 by pmagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int sig)
{
	static int	bit = 0;
	static char	c = 0;

	if (sig == SIGUSR1)
	{
		c |= (1 << bit);
	}
	bit++;
	while (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, "Usage requires only one argument\n", 33);
		exit(1);
	}
	action.sa_handler = &signal_handler;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
