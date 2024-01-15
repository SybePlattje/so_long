/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_utils_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 11:08:14 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 13:45:13 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

t_enemy	*new_enemy(int x, int y, char direction)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (enemy == NULL)
		return (NULL);
	enemy->x = x;
	enemy->y = y;
	enemy->enemy_dir = direction;
	enemy->frames = 0;
	enemy->next = NULL;
	return (enemy);
}

t_enemy	*last_enemy(t_enemy	*enemy)
{
	if (enemy == NULL)
		return (NULL);
	while (enemy->next)
		enemy = enemy->next;
	return (enemy);
}

t_enemy	**add_enemy_to_back(int x, int y, t_data *data)
{
	t_enemy	*new;
	t_enemy	*tmp;

	new = new_enemy(x, y, 'u');
	if (new == NULL)
	{
		free_enemies(data);
		return (NULL);
	}
	if (*data->enemies == NULL)
		*data->enemies = new;
	else
	{
		tmp = last_enemy(*data->enemies);
		tmp->next = new;
	}
	return (data->enemies);
}
