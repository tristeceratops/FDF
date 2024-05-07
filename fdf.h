#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <X11/keysym.h>
# include <fcntl.h>
# ifndef M_PI
#  define M_PI (3.14159265358979323846264338327950288)
# endif
# ifndef S_WIDTH
#  define S_WIDTH 1920
# endif
# ifndef S_HEIGHT
#  define S_HEIGHT 1080
# endif

typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
	int		is_last_in_line;
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
	t_dot	**map;
}		t_data;

void	ft_error(char *str);
t_dot	**read_map(char *path);
void	draw_line(t_dot start, t_dot end, t_data *data, int color);
t_dot	projection_iso(t_dot p);
void    draw_map(t_dot **map, t_data *img);

#endif