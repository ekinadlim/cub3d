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
	if (*y >= 1)
		ccd_positive_y(data, y, offset);
	else if (*y <= -1)
		ccd_negative_y(data, y, offset);
}

static bool	move_to_boundary_y(t_data *data, double *y, double offset)
{
	if (*y > 0 && data->player.y - (int)data->player.y < 0.8001) //0.8
	{
		*y = (int)data->player.y + 1 - offset - data->player.y;
	}
	else if (*y < 0 && data->player.y - (int)data->player.y > 0.1999) //0.2
	{
		*y = (int)data->player.y - offset - data->player.y;
	}
	else
		return (false);
	return (true);
}

void	move_y(t_data *data, double y, double offset)
{
	bool	can_move;

	can_move = false;
	int which = 0;
	//printf("Y Before: player.y = %f, y = %f\n", data->player.y, y);
	if (fabs(y) < EPSILON)
	{
		//printf("Y After: which = 0 (zero movement), player.y = %f, y = %f\n", data->player.y, y);
		return; // Don't process zero movement
	}
	if (y <= -1 || y >= 1) //if distance could cause to skip grids/go through walls
	{
		continuous_collision_detection_y(data, &y, offset);
		can_move = true;
		which = 1;
		data->player.y += y;
		data->movement_happend = true;
		return ;
	}
	else if (check_if_wall(data, data->player.y + y + offset, data->player.x)) //if distance is valid
	{
		can_move = true;
		which = 2;
	}
	/* else if (y > 0 && data->player.y - (int)data->player.y < 0.8001) //0.8
	{
		y = (int)data->player.y + 1 - offset - data->player.y;
		can_move = true;
		which = 3;
	}
	else if (y < 0 && data->player.y - (int)data->player.y > 0.1999) //0.2
	{
		y = (int)data->player.y - offset - data->player.y;
		can_move = true;
		which = 4;
	} */
	else if (move_to_boundary_y(data, &y, offset)) //if not valid, we move to the boundary
	{
		can_move = true;
		which = 69;
	}
	if (fabs(y) < EPSILON)
	{
		//printf("Y BBBBBBBB: which = 0 (zero movement), player.y = %f, y = %f\n", data->player.y, y);
		return; // Don't process zero movement
	}
	if(can_move)
	{
		if (data->player.x - (int)data->player.x > 0.8001) //0.8 //if we are potentially within boundaries in x (right side)
		{
			if (!check_if_wall(data, data->player.y + y + offset, data->player.x + 1)) //if the distance would result us to be inside the boundary of x
			{
				//printf("DEBUG: x_fraction = %.20f\n", data->player.x - (int)data->player.x);
				//printf("3 AAAAAAAAAAA, which = %d, player.y = %f, player.x = %f, y = %f\n", which, data->player.y, data->player.x, y);
				/* if (y > 0 && data->player.y - (int)data->player.y < 0.8001) //0.8
				{
					y = (int)data->player.y + 1 - offset - data->player.y;
				}
				else if (y < 0 && data->player.y - (int)data->player.y > 0.1999) //0.2
				{
					y = (int)data->player.y - offset - data->player.y;
				} */
				move_to_boundary_y(data, &y, offset);
				//return ; //change value (also in ccd? -.-)
			}
		}
		else if (data->player.x - (int)data->player.x < 0.1999) //0.2 //if we are potentially within boundaries in x (left side)
		{
			if (!check_if_wall(data, data->player.y + y + offset, data->player.x - 1)) //if the distance would result us to be inside the boundary of x
			{
				//printf("DEBUG: x_fraction = %.20f\n", data->player.x - (int)data->player.x);
				//printf("4 AAAAAAAAAAA, which = %d, player.y = %f, player.x = %f, y = %f\n", which, data->player.y, data->player.x, y);
				/* if (y > 0 && data->player.y - (int)data->player.y < 0.8001) //0.8
				{
					y = (int)data->player.y + 1 - offset - data->player.y;
				}
				else if (y < 0 && data->player.y - (int)data->player.y > 0.1999) //0.2
				{
					y = (int)data->player.y - offset - data->player.y;
				} */
				move_to_boundary_y(data, &y, offset);
				//return ;
			}
		}
		data->player.y += y;
		data->movement_happend = true;
	}
	//printf("Y After: which = %d, player.y = %f, y = %f\n", which, data->player.y, y);
}