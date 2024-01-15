/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collectible_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 10:40:03 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 11:26:04 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_collectible	*last_node(t_collectible	*collect)
{
	if (collect == NULL)
		return (NULL);
	while (collect->next)
		collect = collect->next;
	return (collect);
}

t_collectible	*new_collectible(int x, int y)
{
	t_collectible	*collectible;

	collectible = ft_calloc(sizeof(t_collectible), 1);
	if (collectible == NULL)
		return (NULL);
	collectible->x = x;
	collectible->y = y;
	collectible->next = NULL;
	return (collectible);
}

t_collectible	**add_back(t_collectible **head, int x, int y)
{
	t_collectible	*new;
	t_collectible	*tmp;

	new = new_collectible(x, y);
	if (new == NULL)
	{
		free_collectables(head);
		return (NULL);
	}
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = last_node(*head);
		tmp->next = new;
	}
	return (head);
}

int	collectible_size(t_collectible **head)
{
	int				size;
	t_collectible	*current;

	size = 0;
	current = *head;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	set_collectibles(t_data *data, char **new_lines)
{
	int	i;
	int	ii;

	data->collectible = ft_calloc(sizeof(t_collectible *),
			data->max_collectibles);
	if (data->collectible == NULL)
		return (1);
	i = 0;
	while (new_lines[i])
	{
		ii = 0;
		while (new_lines[i][ii])
		{
			if (new_lines[i][ii] == 'C')
			{
				data->collectible = add_back(data->collectible, i, ii);
				if (data->collectible == NULL)
					return (free(data->collectible), 1);
			}
			ii++;
		}
		i++;
	}
	return (0);
}
