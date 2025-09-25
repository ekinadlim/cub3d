#include "header.h"

static void ccd_positive_y(t_data *data, double *y, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < *y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (!is_valid || !check_if_wall(data, data->player.y + *y + offset, data->player.x))
	{
		*y = (int)data->player.y + i - data->player.y - offset;
	}
}

static void ccd_negative_y(t_data *data, double *y, double offset)
{
	int i;
	bool is_valid = true;

	i = -1;
	while (i > *y)
	{
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (!is_valid || !check_if_wall(data, data->player.y + *y + offset, data->player.x))
	{
		*y = (int)data->player.y + i + 1 - data->player.y - offset;
	}
}

static void	continuous_collision_detection_y(t_data *data, double *y, double offset)
{
	if (*y >= 1)
		ccd_positive_y(data, y, offset);
	else if (*y <= -1)
		ccd_negative_y(data, y, offset);
}

void	move_y(t_data *data, double y, double offset)
{
	bool	can_move;

	can_move = false;
	if (y <= -1 || y >= 1)
	{
		continuous_collision_detection_y(data, &y, offset);
		can_move = true;
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x))
		can_move = true;
	else if (y > 0 && data->player.y - (int)data->player.y < 0.8)
	{
		y = (int)data->player.y + 1 - offset - data->player.y;
		can_move = true;
	}
	else if (y < 0 && data->player.y - (int)data->player.y > 0.2)
	{
		y = (int)data->player.y - offset - data->player.y;
		can_move = true;
	}
	if(can_move)
	{
		data->player.y += y;
		data->movement_happend = true;
	}
}