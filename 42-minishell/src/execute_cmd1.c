/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:48:11 by davi-g            #+#    #+#             */
/*   Updated: 2024/09/07 19:27:41 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
>: Redirecciona la salida de un comando a un archivo, sobrescribiendo el contenido del archivo si ya existe. Por ejemplo, echo "Hola" > archivo.txt escribirá "Hola" en archivo.txt, reemplazando cualquier contenido previo.

>>: Redirecciona la salida de un comando a un archivo, añadiendo la salida al final del archivo sin borrar su contenido actual. Por ejemplo, echo "Mundo" >> archivo.txt añadirá "Mundo" al final de archivo.txt, preservando lo que ya estaba en el archivo.

<: Redirecciona la entrada de un archivo a un comando. Por ejemplo, sort < archivo.txt tomará el contenido de archivo.txt como entrada para el comando sort, que ordenará las líneas del archivo.

<<: Se utiliza para redireccionar la entrada a un comando desde el terminal hasta que se encuentre una línea que contenga el delimitador especificado. Esto se conoce como "here document" (documento aquí). Por ejemplo:
 */
void	handle_redirection(t_master *info_shell, t_data *cmd, char **env)
{
    int fd;

	fd = -1;
	(void)info_shell;
	(void)env;
	while (cmd && cmd->type != TRUNC && cmd->type != APPEND && cmd->type != INPUT)
		cmd = cmd->next;
    if (cmd->type == TRUNC)
    {
		write(1, "TRUNC\n", 6);
        fd = open(cmd->next->toke, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);		
    }
    else if (cmd->type == APPEND)
    {
		write(1, "APPEND", 6);
        fd = open(cmd->next->toke, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
    }
    else if (cmd->type == INPUT)
    {
		write(1, "INPUT", 5);
        fd = open(cmd->next->toke, O_RDONLY);
        dup2(fd, STDIN_FILENO);
    }
	//exe_cmd(info_shell, cmd, env);
	if (fd != -1)
	    close(fd);
}

int pipeline_checker(t_master *info_shell, t_data *cmd)
{
    t_data *current;
    int     boolean;

    boolean = 0;
    current = cmd;
    while (current)
    {
        if (current->type == PIPE)
        {
            boolean = 1;
            break;
        }
        else if (current->type == END)
            break;
        current = current->next;
    }
    if (boolean == 1)
    {
        execute_pipeline(info_shell, current, 0);
        return (boolean);
    }
    return (boolean);

}

int	redirection_checker(t_data *cmd)
{
	while (cmd)
	{
		if (cmd->type == PIPE)
			break;
		if (cmd->type == TRUNC || cmd->type == APPEND || cmd->type == INPUT)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

t_data    *redirection(t_master *info_shell, t_data *current_cmd)
{
    if (pipeline_checker(info_shell, current_cmd) == 1)
    {
        while (current_cmd && current_cmd->type != PIPE)
            current_cmd = current_cmd->next;
        if (current_cmd->type == PIPE)
            current_cmd = current_cmd->next;
    }
    else if (current_cmd->next && redirection_checker(current_cmd->next) == 1)
    {
        handle_redirection(info_shell, current_cmd, info_shell->env);
        exe_existing_command(current_cmd, info_shell, info_shell->env);
        current_cmd = current_cmd->next;
    }
    else
		exe_existing_command(current_cmd, info_shell, info_shell->env);
	while (current_cmd && (current_cmd->type == CMD || current_cmd->type == ARG))
		current_cmd = current_cmd->next;
	if (current_cmd)
		current_cmd = current_cmd->next;
    return (current_cmd);
}

void	while_commands(t_master *info_shell, t_data *cmd)
{
    t_data  *current_cmd;

    current_cmd = cmd;
    while (current_cmd)
    {
        if (current_cmd->type == CMD)
            current_cmd = redirection(info_shell, current_cmd);
        if (current_cmd)
		{
        	current_cmd = current_cmd->next;
		}
    }
}