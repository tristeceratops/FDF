/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ewoillar <ewoillar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/13 18:11:42 by ewoillar		  #+#	#+#			 */
/*   Updated: 2024/05/13 18:20:22 by ewoillar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

int	get_max_height(t_dot **tableau, int rows, int columns)
{
	int	maximum;
	int	i;
	int	j;

	maximum = tableau[0][0].z;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (tableau[i][j].z > maximum)
				maximum = tableau[i][j].z;
			j++;
		}
		i++;
	}
	return (maximum);
}

int	get_min_height(t_dot **tableau, int rows, int columns)
{
	int	minimum;
	int	i;
	int	j;

	minimum = tableau[0][0].z;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (tableau[i][j].z < minimum)
				minimum = tableau[i][j].z;
			j++;
		}
		i++;
	}
	return (minimum);
}

int	get_rows(t_dot **table)
{
	int	rows;

	rows = 0;
	while (table[rows] != NULL)
		rows++;
	return (rows);
}

int	get_columns(t_dot **table)
{
	int	columns;

	columns = 0;
	while (table[0][columns].is_last_in_line != 1)
		columns++;
	if (table[0][columns].is_last_in_line == 1)
		columns++;
	return (columns);
}

void	free_map(t_dot **table)
{
	int	rows;

	rows = 0;
	while (table[rows] != NULL)
	{
		free(table[rows]);
		rows++;
	}
	free(table);
}

//function to convert array of a hexadecimal value into int
int	hexarraytoint(char *hex)
{
	int		length;
	int		base;
	int		decimal;
	int		i;

	length = ft_strlen(hex);
	base = 1;
	decimal = 0;
	i = length - 1;
	if (hex[i] == '0' && hex[i - 1] == 'x')
		i -= 2;
	while (i >= 0)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			decimal += (hex[i] - 48) * base;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			decimal += (hex[i] - 55) * base;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			decimal += (hex[i] - 87) * base;
		base = base * 16;
		i--;
	}
	return (decimal);
}
