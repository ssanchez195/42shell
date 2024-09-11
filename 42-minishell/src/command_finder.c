/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:45 by sergisan          #+#    #+#             */
/*   Updated: 2024/09/02 18:08:41 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_existing_command(t_data *command, t_master *info_shell, char **env)
{
	if (global_response != 0)
	{
		info_shell->cmd_response = global_response;
		global_response = 0;
	}
	if (ft_strcmp(command->toke, "echo") == 0)
		return (echo_cmd(info_shell, command));
	else if (ft_strcmp(command->toke, "pwd") == 0)
		return (pwd_cmd());
	 else if (ft_strcmp(command->toke, "cd") == 0)
		return (cd_cmd(info_shell, command));
	else if (ft_strcmp(command->toke, "env") == 0)
		env_cmd(info_shell);
	else if (ft_strcmp(command->toke, "exit") == 0)
		return (exit_cmd(command, info_shell));
	else if (ft_strcmp(command->toke, "export") == 0)
		export_cmd(info_shell, command);
	else if (ft_strcmp(command->toke, "unset") == 0)
		unset_cmd(info_shell, command);
	else
		exe_cmd(info_shell, command, env);
	while (command && command->type != PIPE && command->type != TRUNC && command->type != APPEND && command->type != END)
		command = command->next;
	return (0);
}
