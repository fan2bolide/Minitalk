/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/04 04:39:24 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <signal.h>

t_string	g_string;

static void	ft_init_string()
{
	g_string.str = ft_calloc(g_string.size, sizeof(char));
	g_string.size = 1;
	g_string.count = 0;
	g_string.finished = 0;
}
#include <stdio.h>
void	update_string(int sig, siginfo_t *info, void *context)
{
	char	*newstr;

	(void)context;
	usleep(5);
	g_string.str[g_string.size - 1] <<= 1;
	g_string.str[g_string.size - 1] |= (sig == SIGUSR2);
	g_string.count++;
	if (g_string.count == 8 && g_string.str[g_string.size - 1] == 0)
		return (kill(info->si_pid, SIGUSR1), g_string.finished = 1, (void)0);
	if (g_string.count == 8)
	{
		g_string.size++;
		newstr = ft_calloc(g_string.size, sizeof (char));
		if (!newstr)
			return ;
		ft_memmove(newstr, g_string.str, g_string.size - 1);
		if (g_string.str)
		{
			free(g_string.str);
			g_string.str = NULL;
		}
		g_string.str = newstr;
		g_string.count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action1;
	struct sigaction	action2;

	ft_init_string();
    action1.sa_sigaction = update_string;
	action2.sa_sigaction = update_string;
	ft_printf("%d\n", getpid());
	while (1)
	{
    	sigaction(SIGUSR1, &action1, NULL);
		sigaction(SIGUSR2, &action2, NULL);
		if (g_string.finished)
		{
			ft_printf("%s\n", g_string.str);
			g_string.finished = 0;
			free(g_string.str);
			ft_init_string();
		}
		pause();
	}
	return (0);
}
