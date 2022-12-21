/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:13:50 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/21 17:04:46 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	pid;

	if (argc != 3)
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		j = 0;
		while (j < 8)
		{
			if (((argv[2][i] << j) & 0b10000000) == 0)
			{
				if (kill(pid, SIGUSR1) != 0)
					return (write(STDERR_FILENO, "the specified process is not running anymore or the PID is incorrect\n", 69), 1);
				ft_printf("sent 0\n");
			}
			else
			{
				if (kill(pid, SIGUSR2) != 0)
					return (write(STDERR_FILENO, "the specified process is not running anymore or the PID is incorrect\n", 69), 1);
				ft_printf("sent 1\n");
			}
			j++;
			sleep(1);
		}
		i++;
		// ft_printf("\n");
	}
	while (1)
		if (kill(pid, SIGUSR1) != 0)
			return (0);
	return (0);
}
