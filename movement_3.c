#include "header.h"

static void ccd_positive_x(t_data *data, double *x, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < *x)
	{
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (!is_valid || !check_if_wall(data, data->player.y, data->player.x + *x + offset))
	{
		*x = (int)data->player.x + i - data->player.x - offset;
	}
}

static void ccd_negative_x(t_data *data, double *x, double offset)
{
	int i;
	bool is_valid = true;

	i = -1;
	while (i > *x)
	{
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (!is_valid || !check_if_wall(data, data->player.y, data->player.x + *x + offset))
	{
		*x = (int)data->player.x + i + 1 - data->player.x - offset;
	}
}

static void	continuous_collision_detection_x(t_data *data, double *x, double offset)
{
	if (*x >= 1)
		ccd_positive_x(data, x, offset);
	else if (*x <= -1)
		ccd_negative_x(data, x, offset);
}

void	move_x(t_data *data, double x, double offset)
{
	bool	can_move;

	can_move = false;
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, &x, offset);
		can_move = true;
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
		can_move = true;
	else if (x > 0 && data->player.x - (int)data->player.x < 0.8)
	{
		x = (int)data->player.x + 1 - offset - data->player.x;
		can_move = true;
	}
	else if (x < 0 && data->player.x - (int)data->player.x > 0.2)
	{
		x = (int)data->player.x - offset - data->player.x;
		can_move = true;
	}
	if(can_move)
	{
		data->player.x += x;
		data->movement_happend = true;
	}
}