/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:37:12 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/03 15:32:35 by mbaron           ###   ########.fr       */
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
	if (param_name[5] == '.')
	{
		if (param_name[4] == 'f')
		{
			if (param_name[6] == 'r')
				conf->color->floor->r = value;
			else if (param_name[6] == 'g')
				conf->color->floor->g = value;
			else if (param_name[6] == 'b')
				conf->color->floor->b = value;
		}
		else if (param_name[4] == 'c')
		{
			if (param_name[6] == 'r')
				conf->color->ceil->r = value;
			else if (param_name[6] == 'g')
				conf->color->ceil->g = value;
			else if (param_name[6] == 'b')
				conf->color->ceil->b = value;
		}
	}
}

void		config_file_line(t_conf *conf, char *line)
{
	char	**params;

	params = NULL;
	if (!(params = ft_strsplit(line, ' ')))
		set_error("Malloc error in config_file_line", 1);
	if (1 < ft_strsplitnb(params))
	{
		if (ft_strlen(params[0]) == 5 && params[0][4] == '.')
		{
			if (params[0][0] == 'w')
				config_world(conf, params[0], ft_atoi(params[1]));
			else if (params[0][0] == 'c')
				config_cam(conf, params[0], ft_atoi(params[1]));
			else if (params[0][0] == 'p')
				conf->proj->val = ft_atoi(params[1]);
		}
		else if (ft_strlen(params[0]) == 7 && params[0][6] == '.'
			&& params[0][0] == 'c')
		config_color(conf, params[0], ft_atoi(params[1]));
	}
	ft_strsplitdel(params);
}
