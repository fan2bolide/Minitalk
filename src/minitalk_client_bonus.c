/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:13:50 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/06 07:22:08 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sighandler(int sig)
{
	ft_printf("received call back : %d\n", sig);
}

static int	send_byte(char byte, int pid)
{
	size_t	j;

	j = 0;
	while (j < 8)
	{
		if (((byte << j) & 0b10000000) == 0)
		{
			if (kill(pid, SIGUSR1) != 0)
				return (write(STDERR_FILENO, "PID is incorrect\n", 17), 1);
		}
		else if (kill(pid, SIGUSR2) != 0)
			return (write(STDERR_FILENO, "PID is incorrect\n", 17), 1);
		ft_printf("%d\n", ((byte << j) & 0b10000000));
		j++;
		pause();
	}
	return (0);
}

int	main(int argc, char **argv)
{
	size_t	i;
	int		pid;

	if (argc != 3)
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, sighandler);
	i = 0;
	while (argv[2][i])
	{
		if (send_byte(argv[2][i], pid))
			return (1);
		i++;
	}
	if (send_byte(0, pid))
		return (1);
	return (0);
}
