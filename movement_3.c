#include "header.h"

static void ccd_positive_x(t_data *data, double *x, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < *x)
	{
		if (data->player.y - (int)data->player.y > 0.8001)
		{
			if (!check_if_wall(data, data->player.y + 1, data->player.x + i))
			{
				is_valid = false;
				break ;
			}
		}
		else if (data->player.y - (int)data->player.y < 0.1999)
		{
			if (!check_if_wall(data, data->player.y - 1, data->player.x + i))
			{
				is_valid = false;
				break ;
			}
		}
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (data->player.y - (int)data->player.y > 0.8001)
	{
		if (!check_if_wall(data, data->player.y + 1, data->player.x + *x + offset))
		{
			is_valid = false;
		}
	}
	else if (data->player.y - (int)data->player.y < 0.1999)
	{
		if (!check_if_wall(data, data->player.y - 1, data->player.x + *x + offset))
		{
			is_valid = false;
		}
	}
	if (!check_if_wall(data, data->player.y, data->player.x + *x + offset))
	{
		is_valid = false;
	}
	if (!is_valid)
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
		if (data->player.y - (int)data->player.y > 0.8001)
		{
			if (!check_if_wall(data, data->player.y + 1, data->player.x + i))
			{
				is_valid = false;
				break ;
			}
		}
		else if (data->player.y - (int)data->player.y < 0.1999)
		{
			if (!check_if_wall(data, data->player.y - 1, data->player.x + i))
			{
				is_valid = false;
				break ;
			}
		}
		if (!check_if_wall(data, data->player.y, data->player.x + i))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (data->player.y - (int)data->player.y > 0.8001)
	{
		if (!check_if_wall(data, data->player.y + 1, data->player.x + *x + offset))
		{
			is_valid = false;
		}
	}
	else if (data->player.y - (int)data->player.y < 0.1999)
	{
		if (!check_if_wall(data, data->player.y - 1, data->player.x + *x + offset))
		{
			is_valid = false;
		}
	}
	if (!check_if_wall(data, data->player.y, data->player.x + *x + offset))
	{
		is_valid = false;
	}
	if (!is_valid)
	{
		*x = (int)data->player.x + i + 1 - data->player.x - offset;
	}
}

static void	continuous_collision_detection_x(t_data *data, double *x, double offset)
{
	if (*x > 0)
		ccd_positive_x(data, x, offset);
	else if (*x < 0)
		ccd_negative_x(data, x, offset);
}

/* static bool	move_to_boundary_x(t_data *data, double *x, double offset)
{
	if (*x > 0 && data->player.x - (int)data->player.x < 0.8001)
	{
		*x = (int)data->player.x + 1 - offset - data->player.x;
	}
	else if (*x < 0 && data->player.x - (int)data->player.x > 0.1999)
	{
		*x = (int)data->player.x - offset - data->player.x;
	}
	else
		return (false);
	return (true);
} */

void	move_x(t_data *data, double x, double offset)
{
	bool	can_move;

	can_move = false;
	printf("X Before: player.y = %.20f, player.x = %.20f, x = %.20f\n", data->player.y, data->player.x, x);
	if (fabs(x) < EPSILON)
	{
		printf("Nope fabs(x) = %.20f < EPSILON = %.20f\n", fabs(x), EPSILON);
		return;
	}
	//if (x <= -1 || x >= 1)
	//{
		continuous_collision_detection_x(data, &x, offset);
		data->player.x += x;
		data->movement_happend = true;
		printf("X After: player.y = %.20f, player.x = %.20f, x = %.20f\n", data->player.y, data->player.x, x);
		if (fabs(x) < EPSILON)
		{
			printf("Yep fabs(x) = %.20f < EPSILON = %.20f\n", fabs(x), EPSILON);
			return;
		}
		return ;
	//}
	/* else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		can_move = true;
	}
	else if (move_to_boundary_x(data, &x, offset))
	{
		can_move = true;
	}
	if (fabs(x) < EPSILON)
	{
		return;
	}
	if(can_move)
	{
		if (data->player.y - (int)data->player.y > 0.8001)
		{
			if (!check_if_wall(data, data->player.y + 1, data->player.x + x + offset))
			{
				move_to_boundary_x(data, &x, offset);
			}
		}
		else if (data->player.y - (int)data->player.y < 0.1999)
		{
			if (!check_if_wall(data, data->player.y - 1, data->player.x + x + offset))
			{
				move_to_boundary_x(data, &x, offset);
			}
		}
		data->player.x += x;
		data->movement_happend = true;
	} */
}