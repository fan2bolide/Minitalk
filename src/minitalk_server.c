/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:37 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/21 16:24:14 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

t_string	g_string;

static void	ft_init_string()
{
	g_string.str = ft_calloc(g_string.size, sizeof(char));
	g_string.size = 1;
	g_string.count = 0;
	g_string.finished = 0;
}

void	update_string(int sig)
{
	char	*newstr;

	if (g_string.count == 8)
	{
		g_string.size++;
		newstr = ft_calloc(g_string.size, sizeof (char));
		if (!newstr)
			return ;
		ft_memmove(newstr, g_string.str, g_string.size - 1);
		free(g_string.str);
		g_string.str = newstr;
		g_string.count = 0;
	}
	g_string.str[g_string.size - 1] |= (sig == SIGUSR2) << (7 - g_string.count);
	g_string.count++;
	if (g_string.count == 8 && g_string.str[g_string.size - 1] == 0)
	{
		g_string.finished = 1;
	}
	ft_printf("received %d\n", (sig == SIGUSR2));
}

#include <stdio.h>
int	main(void)
{
	ft_init_string();
	signal(SIGUSR1, update_string);
	signal(SIGUSR2, update_string);
	fprintf(stderr, "%d\n", getpid());
	while (1)
	{
		if (g_string.finished)
			return (ft_printf("%s\n", g_string.str), 0);
	}
	return (0);
}
