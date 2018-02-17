/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 11:28:43 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 15:19:20 by mbaron           ###   ########.fr       */
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
	t_vertex			*vertex;
	struct s_lstmapi	*next;
}				t_lstmapi;
t_conf			*config_default(void);
void			config_file(t_conf *conf, int argc, char *argv[]);
int				is_param(const char *param, int argc, char *argv[]);
int				test_args(int argc, char *argv[]);
void			config_set_params_name(t_param **ps);
void			config_set_params_value(t_control *c, t_param **ps);
void			config_set_params_minmax(t_param **ps);
void			config_set_params_keys(t_param **ps);
void			config_set_params(t_conf *conf, t_param **ps);
void			map_parse_file(t_conf *conf, char *file);
void			map_create(t_conf *conf, t_lstmapi *lstmapi);
#endif
