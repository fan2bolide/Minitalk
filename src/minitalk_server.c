/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/04 22:11:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

	g_string.str[g_string.size - 1] <<= 1;
	g_string.str[g_string.size - 1] |= (sig == SIGUSR2);
	g_string.count++;
	if (g_string.count == 8 && g_string.str[g_string.size - 1] == 0)
		return (g_string.finished = 1, (void)0);
	if (g_string.count == 8)
	{
		g_string.size++;
		newstr = ft_calloc(g_string.size, sizeof (char));
		if (!newstr)
			return (write(1, "Malloc error, exiting program\n", 30), free(g_string.str), exit(1), (void)0);
		ft_memmove(newstr, g_string.str, g_string.size - 1);
		if (g_string.str)
			free(g_string.str);
		g_string.str = newstr;
		g_string.count = 0;
	}
}

int	main(void)
{
	ft_init_string();
	signal(SIGUSR1, update_string);
	signal(SIGUSR2, update_string);
	ft_printf("%d\n", getpid());
	while (1)
	{
		if (g_string.finished)
		{
			ft_printf("%s\n", g_string.str);
			g_string.finished = 0;
			free(g_string.str);
			ft_init_string();
		}
	}
	return (0);
}
