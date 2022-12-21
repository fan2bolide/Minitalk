/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:15:44 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/21 13:29:17 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

typedef struct s_string
{
	char	*str;
	int		count;
	size_t	size;
	char	finished;
}			t_string;

#endif