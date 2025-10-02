#include "header.h"

static bool	validate_x_position(t_data *data, double x)
{
	if (data->player.y - (int)data->player.y > 0.8001)
	{
		if (!check_if_wall(data, data->player.y + 1, x))
			return (false);
	}
	else if (data->player.y - (int)data->player.y < 0.1999)
	{
		if (!check_if_wall(data, data->player.y - 1, x))
			return (false);
	}
	if (!check_if_wall(data, data->player.y, x))
		return (false);
	return (true);
}

static void ccd_positive_x(t_data *data, double *x, double offset)
{
	int i;

	i = 1;
	while (i < *x)
	{
		if (!validate_x_position(data, data->player.x + i))
		{
			*x = (int)data->player.x + i - data->player.x - offset;
			return ;
		}
		i++;
	}
	if (!validate_x_position(data, data->player.x + *x + offset))
		*x = (int)data->player.x + i - data->player.x - offset;
}

static void ccd_negative_x(t_data *data, double *x, double offset)
{
	int i;

	i = -1;
	while (i > *x)
	{
		if (!validate_x_position(data, data->player.x + i))
		{
			*x = (int)data->player.x + i + 1 - data->player.x - offset;
			return ;
		}
		i--;
	}
	if (!validate_x_position(data, data->player.x + *x + offset))
		*x = (int)data->player.x + i + 1 - data->player.x - offset;
}

static void	continuous_collision_detection_x(t_data *data, double *x, double offset)
{
	if (*x > 0)
		ccd_positive_x(data, x, offset);
	else if (*x < 0)
		ccd_negative_x(data, x, offset);
}

void	move_x(t_data *data, double x, double offset)
{
	bool	can_move;

	can_move = false;
	//printf("X Before: player.y = %.20f, player.x = %.20f, x = %.20f\n", data->player.y, data->player.x, x);
	if (fabs(x) < EPSILON)
		return;
	continuous_collision_detection_x(data, &x, offset);
	if (fabs(x) < EPSILON)
		return;
	data->player.x += x;
	data->movement_happend = true;
	//printf("X After: player.y = %.20f, player.x = %.20f, x = %.20f\n", data->player.y, data->player.x, x);
}