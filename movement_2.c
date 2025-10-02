#include "header.h"

static bool	validate_y_position(t_data *data, double y)
{
	if (data->player.x - (int)data->player.x > 0.8001)
	{
		if (!check_if_wall(data, y, data->player.x + 1))
			return (false);
	}
	else if (data->player.x - (int)data->player.x < 0.1999)
	{
		if (!check_if_wall(data, y, data->player.x - 1))
			return (false);
	}
	if (!check_if_wall(data, y, data->player.x))
		return (false);
	return (true);
}

static void ccd_positive_y(t_data *data, double *y, double offset)
{
	int i;

	i = 1;
	while (i < *y)
	{
		if (!validate_y_position(data, data->player.y + i))
		{
			*y = (int)data->player.y + i - data->player.y - offset;
			return ;
		}
		i++;
	}
	if (!validate_y_position(data, data->player.y + *y + offset))
		*y = (int)data->player.y + i - data->player.y - offset;
}

static void ccd_negative_y(t_data *data, double *y, double offset)
{
	int i;

	i = -1;
	while (i > *y)
	{
		if (!validate_y_position(data, data->player.y + i))
		{
			*y = (int)data->player.y + i + 1 - data->player.y - offset;
			return ;
		}
		i--;
	}
	if (!validate_y_position(data, data->player.y + *y + offset))
		*y = (int)data->player.y + i + 1 - data->player.y - offset;
}

static void	continuous_collision_detection_y(t_data *data, double *y, double offset)
{
	if (*y > 0)
		ccd_positive_y(data, y, offset);
	else if (*y < 0)
		ccd_negative_y(data, y, offset);
}


void	move_y(t_data *data, double y, double offset)
{
	bool	can_move;

	can_move = false;
	//printf("Y Before: player.y = %.20f, player.x = %.20f, y = %.20f\n", data->player.y, data->player.x, y);
	if (fabs(y) < EPSILON)
		return;
	continuous_collision_detection_y(data, &y, offset);
	if (fabs(y) < EPSILON)
		return;
	data->player.y += y;
	data->movement_happend = true;
	//printf("Y After: player.y = %.20f, player.x = %.20f, y = %.20f\n", data->player.y, data->player.x, y);
}