/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 11:28:43 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 16:52:25 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# include <fcntl.h>
# define MAP_FILE_DEFAULT "./maps/42.fdf"
# define CONFIG_FILE_DEFAULT "./config/config.def.txt"
# define FDF_USAGE_TITLE "usage:	"
# define FDF_USAGE_PARAM "./fdf [-f config_file] [-m map_file] [-c r/g/b-r/g/b]"
# define FDF_USAGE FDF_USAGE_TITLE FDF_USAGE_PARAM

typedef struct	s_lstmapi
{
	t_vtx				*vertex;
	struct s_lstmapi	*next;
}				t_lstmapi;
/*
**	File config.c
*/
int				is_param(const char *param, int argc, char *argv[]);
/*
**	File config_default.c
*/
void			config_set_params(t_conf *conf, t_param **ps);
/*
**	File config_file.c
*/
void			config_file(t_conf *conf, int argc, char *argv[]);
/*
**	File config_map.c
*/
void			map_parse_file(t_conf *conf, char *file);
/*
**	File config_map_create.c
*/
void			map_create(t_conf *conf, t_lstmapi *lstmapi);
#endif
