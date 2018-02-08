/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 11:28:43 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/07 18:52:26 by mbaron           ###   ########.fr       */
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
# define FDF_WORLD_ZOOM 50
# define FDF_WORLD_X 50
# define FDF_WORLD_Y 50
# define FDF_WORLD_Z 50
# define FDF_CAM_X 50
# define FDF_WORLD_ROT 0
# define FDF_CAM_Y 50
# define FDF_CAM_Z 50
# define FDF_CAM_RX 0
# define FDF_CAM_RY 0
# define FDF_CAM_RZ 0
# define FDF_PROJ_VAL 1
# define FDF_PROJ_COL 1
# define FDF_COL_FLOOR 0x000000
# define FDF_COL_CEIL 0xFFFFFF

typedef struct	s_lstmapi
{
	t_vertex			*vertex;
	struct s_lstmapi	*next;
}				t_lstmapi;
t_conf			*config_default();
t_control		*config_control_init_pointers(const char *title, int nb);
int				test_args(int argc, char *argv[]);
void			config_file_line(t_conf *conf, char *line);
void			map_parse_file(t_conf *conf, char *file);
#endif
