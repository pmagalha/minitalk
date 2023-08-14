/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagalha <pmagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:17:13 by pmagalha          #+#    #+#             */
/*   Updated: 2023/06/05 15:16:25 by pmagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_sender(int pid, const char *str)
{
	int		i;
	char	c;
	int		j;

	j = 0;
	i = 0;
	while ((str[j]) != '\0')
	{
		c = str[j];
		i = 0;
		while (i < 8)
		{
			if ((c >> i) & 1)
			{
				kill(pid, SIGUSR1);
			}
			else
			{
				kill(pid, SIGUSR2);
			}
			usleep(1000);
			i++;
		}
		j++;
	}
}

static void	ft_sender2(pid_t pid)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		kill(pid, SIGUSR2);
		usleep(100);
	}
}

static void	bonus_signal(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_printf("Message received!");
	}
	exit(1);
}

int	main(int argc, char **argv)
{
	struct sigaction	bonus;
	pid_t				pid;
	const char			*str;

	bonus.sa_handler = &bonus_signal;
	bonus.sa_flags = 0;
	sigemptyset(&bonus.sa_mask);
	str = argv[2];
	if (argc != 3)
	{
		write(STDERR_FILENO, "Usage: ./client [PID] [message]\n", 32);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0))
	{
		write(STDERR_FILENO, "Invalid PID\n", 12);
		exit(1);
	}
	sigaction(SIGUSR2, &bonus, NULL);
	ft_sender(pid, str);
	ft_sender2(pid);
	while (1)
		pause();
}
