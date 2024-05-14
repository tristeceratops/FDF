#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <X11/keysym.h>
# include <fcntl.h>
# define BASE_COLOR 0xf8f8f8
# define TOP_COLOR 0xff5500
typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
	int		is_last_in_line;
	int x_pad;
	int y_pad;
	int zoom;
	int	color;
}		t_dot;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_width;
	int		win_height;
	int		zoom;
	int		x_pad;
	int		y_pad;
	int		min_z;
	int		max_z;
	t_dot	**map;
}		t_data;

void	ft_error(char *str);
t_dot	**read_map(char *path, t_data data);
void	draw_line(t_dot start, t_dot end, t_data *data, int *color);
t_dot	projection_iso(t_dot p);
void	draw_map(t_dot **map, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	 get_min_height(t_dot **tableau, int lignes, int colonnes);
int	 get_max_height(t_dot **tableau, int lignes, int colonnes);
int	 get_rows(t_dot **table);
int	 get_columns(t_dot **table);
t_dot	**fill_color_tab(t_data data);

#endif