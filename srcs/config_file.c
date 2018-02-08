/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:37:12 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/07 18:29:43 by mbaron           ###   ########.fr       */
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

static void	config_proj(t_conf *conf, char *param_name, int value)
{
	if (param_name[4] == 'v')
		conf->proj->val = value;
	else if (param_name[4] == 'c')
		conf->proj->col = value;
	else if (param_name[4] == '0')
		conf->color->floor = value;
	else if (param_name[4] == '1')
		conf->color->ceil = value;
}

void		config_file_line(t_conf *conf, char *line)
{
	char	**params;

	params = NULL;
	if (!(params = ft_strsplit(line, ' ')))
		set_error("Malloc error in config_file_line", 1);
	if (1 < ft_strsplitnb(params) && params[0][0] && params[0][0] != '#')
	{
		if (ft_strlen(params[0]) == 5 && params[0][4] == '.')
		{
			if (params[0][0] == 'w')
				config_world(conf, params[0], ft_atoi(params[1]));
			else if (params[0][0] == 'c')
				config_cam(conf, params[0], ft_atoi(params[1]));
			else if (params[0][0] == 'p')
				config_proj(conf, params[0],
					(params[0][4] == 'v' || params[0][4] == 'c')
					? (unsigned int)ft_atoi(params[1])
					: ft_atoi_hex(params[1]));
		}
	}
	ft_strsplitdel(params);
}
