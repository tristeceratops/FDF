#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"
# include <X11/keysym.h>

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct  s_3dcoord
{
	int		x;
	int		y;
	int		z;
}               t_3dcoord;

typedef struct s_2dcoord
{
	int x;
	int y;
}               t_2dcoord;

void	draw_line(t_2dcoord start, t_2dcoord end, t_data *data, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif