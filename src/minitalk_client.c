/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:13:50 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/20 12:28:06 by bajeanno         ###   ########lyon.fr   */
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
		j = 2;
		while (j < 8)
		{
			if ((argv[1][i] << j) >> j == j)
			{
				if (kill(pid, SIGUSR1) != 0)
					return (write(STDERR_FILENO, "the specified process is not running anymore or the PID is incorrect\n", 69), 1);
			}
			else
				if (kill(pid, SIGUSR2) != 0)
					return (write(STDERR_FILENO, "the specified process is not running anymore or the PID is incorrect\n", 69), 1);
			j++;
		}
		i++;
	}
	return (0);
}
