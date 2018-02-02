/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 11:28:43 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/02 11:51:24 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# include <fcntl.h>
# define MAP_DEFAULT_FILE "./maps/42.fdf"
# define CONFIG_FILE_DEFAULT "./config/config.def.txt"
# define FDF_USAGE_TITLE "usage:	"
# define FDF_USAGE_PARAM "./fdf [-f config_file] [-m map_file] [-c r/g/b-r/g/b]"
# define FDF_USAGE FDF_USAGE_TITLE FDF_USAGE_PARAM
# define FDF_WORLD_ZOOM 50
# define FDF_WORLD_X 50
# define FDF_WORLD_Y 50
# define FDF_WORLD_Z 50
# define FDF_CAM_X 50
# define FDF_CAM_Y 50
# define FDF_CAM_Z 50
# define FDF_CAM_RX 50
# define FDF_CAM_RY 50
# define FDF_CAM_RZ 50
# define FDF_PROJ_VAL 50
# define FDF_COL_FLOOR_R 0
# define FDF_COL_FLOOR_G 0
# define FDF_COL_FLOOR_B 0
# define FDF_COL_CEIL_R 0
# define FDF_COL_CEIL_G 0
# define FDF_COL_CEIL_B 0

typedef struct	s_lstmapi
{
	t_vertex			*vertex;
	struct s_lstmapi	*next;
}				t_lstmapi;
t_conf			*config_default(t_conf *conf);
int				test_args(int argc, char *argv[]);
int				get_next_word(char *s1, char *s2, int *index);
void			config_file_line(t_conf *conf, char *line, int *index);
void			map_parse_file(t_conf *conf, char *file, t_lstmapi *lstmapi);
double			ft_getnbr(char *str);
#endif
