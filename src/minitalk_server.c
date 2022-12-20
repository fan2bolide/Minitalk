/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:37 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/20 12:26:54 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

void sighandle(int sig)
{
	ft_printf("signal received fdsa : %d\n\n", sig);
}

static char	get_byte(void)
{
	if (signal(SIGUSR1, sighandle) == SIG_ERR)
		return (ft_printf("usr1\n"), 0);
	if (signal(SIGUSR2, sighandle) == SIG_ERR)
		return (ft_printf("usr2\n"), 1);
	return (0);
}

int	main(void)
{
	int pid;

	pid = getpid();
	ft_printf("%d\n", pid);
	char byte = get_byte();
	while (1)
	{
		sleep(3);
		ft_printf("%c\n", byte);
		get_byte();
	}
	return (0);
}