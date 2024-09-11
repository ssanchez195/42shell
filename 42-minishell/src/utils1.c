/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergisan <sergisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:35:13 by davi-g            #+#    #+#             */
/*   Updated: 2024/09/09 12:35:50 by sergisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_array_full(char **array)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			j++;
		k += j;
		i++;
	}
	return (i + k - 1);
}

void	is_space(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
			|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

void	print_tokens(t_data *data)
{
	t_data	*aux;

	aux = data;
	while (aux)
	{
		ft_printf("toke: %s\n", aux->toke);
		ft_printf("type: %d\n", aux->type);
		aux = aux->next;
	}
}

t_data	ft_clean_toke(t_master *info_shell, t_data *data)
{
	if (data && data->toke)
		del_toke(data);
	global_response = 0;
	info_shell->error = 0;
	data->quote = 0;
	return (*data);
}

void	del_toke(t_data *data)
{
	t_data	*aux;

	while (data)
	{
		if (data->next)
			aux = data->next;
		/*if (data->toke != NULL)
		{
			write(1, "SEGFAULT\n", 9);
			free(data->toke);
			write(1, "DESPUES DEL FREE\n", 17);
			data->toke = NULL;
		}*/
		write(1, "Hola\n", 5);
		//free(data);
		write(1, "Hola2\n", 6);
		data = aux;
	}
	write(1, "Adios", 5);
}
