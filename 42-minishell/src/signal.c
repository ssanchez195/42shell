/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:33:28 by davi-g            #+#    #+#             */
/*   Updated: 2024/07/15 17:57:14 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
    {
        global_response = 130;
	    rl_on_new_line();
        ft_putstr("\n");
	    rl_redisplay();
	    rl_replace_line("", 0);
    }
    return ;
}

void	handle_eof(char *input)
{
    if (!input)
	{
        ft_putstr("Exiting minishell\n");
        exit(0);
    }
}
