/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:37:12 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 18:52:58 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void	config_world(t_conf *conf, char *param_name, int value)
{
	if (param_name[4] == 'x')
		conf->world->x = value;
	else if (param_name[4] == 'y')
		conf->world->y = value;
	else if (param_name[4] == 'z')
		conf->world->z = value;
	else if (param_name[4] == 's')
		conf->world->zoom = value;
	else if (param_name[4] == 'r')
		conf->world->rot = value;
}

static void	config_cam(t_conf *conf, char *param_name, int value)
{
	if (param_name[4] == 'x')
		conf->camera->x = value;
	else if (param_name[4] == 'y')
		conf->camera->y = value;
	else if (param_name[4] == 'z')
		conf->camera->z = value;
	else if (param_name[4] == 'a')
		conf->camera->rx = value;
	else if (param_name[4] == 'b')
		conf->camera->ry = value;
	else if (param_name[4] == 'c')
		conf->camera->rz = value;
}

static void	config_color(t_conf *conf, char *param_name, int value)
{
	if (!ft_strcmp(ft_strsub(param_name, 4, 2), "f."))
	{
		if (param_name[6] == 'r')
			conf->color->floor->r = value;
		else if (param_name[6] == 'g')
			conf->color->floor->g = value;
		else if (param_name[6] == 'b')
			conf->color->floor->b = value;
	}
	else if (!ft_strcmp(ft_strsub(param_name, 4, 2), "c."))
	{
		if (param_name[6] == 'r')
			conf->color->ceil->r = value;
		else if (param_name[6] == 'g')
			conf->color->ceil->g = value;
		else if (param_name[6] == 'b')
			conf->color->ceil->b = value;
	}
}

void		config_file_line(t_conf *conf, char *line, int *index)
{
	char	param_name[32];
	char	param_value[32];
	int		value;

	if (get_next_word(param_name, line, index))
	{
		if (get_next_word(param_value, line, index))
		{
			value = ft_atoi(param_value);
			if (!ft_strcmp(ft_strsub(param_name, 0, 4), "wor.")
				&& ft_strlen(param_name) == 5)
				config_world(conf, param_name, value);
			else if (!ft_strcmp(ft_strsub(param_name, 0, 4), "cam.")
				&& ft_strlen(param_name) == 5)
				config_cam(conf, param_name, value);
			else if (!ft_strcmp(ft_strsub(param_name, 0, 4), "col.")
				&& ft_strlen(param_name) == 7)
				config_color(conf, param_name, value);
			else if (!ft_strcmp(param_name, "pro"))
				conf->proj->val = value;
		}
	}
}
