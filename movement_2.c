#include "header.h"

static void ccd_positive_y(t_data *data, double *y, double offset)
{
	int i;
	bool is_valid = true;

	i = 1;
	while (i < *y)
	{
		if (data->player.x - (int)data->player.x > 0.8001)
		{
			if (!check_if_wall(data, data->player.y + i, data->player.x + 1))
			{
				is_valid = false;
				break ;
			}
		}
		else if (data->player.x - (int)data->player.x < 0.1999)
		{
			if (!check_if_wall(data, data->player.y + i, data->player.x - 1))
			{
				is_valid = false;
				break ;
			}
		}
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (data->player.x - (int)data->player.x > 0.8001)
	{
		if (!check_if_wall(data, data->player.y + *y + offset, data->player.x + 1))
		{
			is_valid = false;
		}
	}
	else if (data->player.x - (int)data->player.x < 0.1999)
	{
		if (!check_if_wall(data, data->player.y + *y + offset, data->player.x - 1))
		{
			is_valid = false;
		}
	}
	if (!check_if_wall(data, data->player.y + *y + offset, data->player.x))
	{
		is_valid = false;
	}
	if (!is_valid)
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
		if (data->player.x - (int)data->player.x > 0.8001)
		{
			if (!check_if_wall(data, data->player.y + i, data->player.x + 1))
			{
				is_valid = false;
				break ;
			}
		}
		else if (data->player.x - (int)data->player.x < 0.1999)
		{
			if (!check_if_wall(data, data->player.y + i, data->player.x - 1))
			{
				is_valid = false;
				break ;
			}
		}
		if (!check_if_wall(data, data->player.y + i, data->player.x))
		{
			is_valid = false;
			break ;
		}
		i--;
	}
	if (data->player.x - (int)data->player.x > 0.8001)
	{
		if (!check_if_wall(data, data->player.y + *y + offset, data->player.x + 1))
		{
			is_valid = false;
		}
	}
	else if (data->player.x - (int)data->player.x < 0.1999)
	{
		if (!check_if_wall(data, data->player.y + *y + offset, data->player.x - 1))
		{
			is_valid = false;
		}
	}
	if (!check_if_wall(data, data->player.y + *y + offset, data->player.x))
	{
		is_valid = false;
	}
	if (!is_valid)
	{
		*y = (int)data->player.y + i + 1 - data->player.y - offset;
	}
}

static void	continuous_collision_detection_y(t_data *data, double *y, double offset)
{
	if (*y > 0)
		ccd_positive_y(data, y, offset);
	else if (*y < 0)
		ccd_negative_y(data, y, offset);
}

/* static bool	move_to_boundary_y(t_data *data, double *y, double offset)
{
	if (*y > 0 && data->player.y - (int)data->player.y < 0.8001)
	{
		*y = (int)data->player.y + 1 - offset - data->player.y;
	}
	else if (*y < 0 && data->player.y - (int)data->player.y > 0.1999)
	{
		*y = (int)data->player.y - offset - data->player.y;
	}
	else
		return (false);
	return (true);
} */

void	move_y(t_data *data, double y, double offset)
{
	bool	can_move;

	can_move = false;
	printf("Y Before: player.y = %.20f, player.x = %.20f, y = %.20f\n", data->player.y, data->player.x, y);
	if (fabs(y) < EPSILON) //if 0 dont move
	{
		printf("Nope fabs(y) = %.20f < EPSILON = %.20f\n", fabs(y), EPSILON);
		return;
	}
	//if (y <= -1 || y >= 1) //if distance could cause to skip grids/go through walls
	//{
		continuous_collision_detection_y(data, &y, offset);
		data->player.y += y;
		data->movement_happend = true;
		printf("Y After: player.y = %.20f, player.x = %.20f, y = %.20f\n", data->player.y, data->player.x, y);
		if (fabs(y) < EPSILON) //if 0 dont move
		{
			printf("Yep fabs(y) = %.20f < EPSILON = %.20f\n", fabs(y), EPSILON);
			return;
		}
		return ;
	//}
	/* else if (check_if_wall(data, data->player.y + y + offset, data->player.x)) //if distance is valid
	{
		can_move = true;
	}
	else if (move_to_boundary_y(data, &y, offset)) //if not valid, we move to the boundary
	{
		can_move = true;
	}
	if (fabs(y) < EPSILON) //if it got changed to 0 dont move
	{
		return;
	}
	if(can_move)
	{
		if (data->player.x - (int)data->player.x > 0.8001) //if we are potentially within boundaries in x (right side)
		{
			if (!check_if_wall(data, data->player.y + y + offset, data->player.x + 1)) //if the distance would result us to be inside the boundary of x
			{
				move_to_boundary_y(data, &y, offset);
			}
		}
		else if (data->player.x - (int)data->player.x < 0.1999) //if we are potentially within boundaries in x (left side)
		{
			if (!check_if_wall(data, data->player.y + y + offset, data->player.x - 1)) //if the distance would result us to be inside the boundary of x
			{
				move_to_boundary_y(data, &y, offset);
			}
		}
		data->player.y += y;
		data->movement_happend = true;
	} */
}