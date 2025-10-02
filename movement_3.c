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
		else if (!check_if_wall(data, data->player.y, data->player.x + i))
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
	else if (!check_if_wall(data, data->player.y, data->player.x + *x + offset))
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
		else if (!check_if_wall(data, data->player.y, data->player.x + i))
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
	else if (!check_if_wall(data, data->player.y, data->player.x + *x + offset))
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
	if (*x >= 1)
		ccd_positive_x(data, x, offset);
	else if (*x <= -1)
		ccd_negative_x(data, x, offset);
}

static bool	move_to_boundary_x(t_data *data, double *x, double offset)
{
	if (*x > 0 && data->player.x - (int)data->player.x < 0.8001) // 0.8
	{
		*x = (int)data->player.x + 1 - offset - data->player.x;
	}
	else if (*x < 0 && data->player.x - (int)data->player.x > 0.1999) //0.2
	{
		*x = (int)data->player.x - offset - data->player.x;
	}
	else
		return (false);
	return (true);
}

void	move_x(t_data *data, double x, double offset)
{
	bool	can_move;

	can_move = false;
	int which = 0;
	//printf("X Before: player.x = %f, x = %f\n", data->player.x, x);
	if (fabs(x) < EPSILON)
    {
        //printf("X After: which = 0 (zero movement), player.x = %f, x = %f\n", data->player.x, x);
        return; // Don't process zero movement
    }
	if (x <= -1 || x >= 1)
	{
		continuous_collision_detection_x(data, &x, offset);
		can_move = true;
		which = 1;
		data->player.x += x;
		data->movement_happend = true;
		return ;
	}
	else if (check_if_wall(data, data->player.y, data->player.x + x + offset))
	{
		can_move = true;
		which = 2;
	}
	/* else if (x > 0 && data->player.x - (int)data->player.x < 0.8001) // 0.8
	{
		x = (int)data->player.x + 1 - offset - data->player.x;
		can_move = true;
		which = 3;
	}
	else if (x < 0 && data->player.x - (int)data->player.x > 0.1999) //0.2
	{
		x = (int)data->player.x - offset - data->player.x;
		can_move = true;
		which = 4;
	} */
	else if (move_to_boundary_x(data, &x, offset))
	{
		can_move = true;
		which = 420;
	}
	if (fabs(x) < EPSILON)
    {
        //printf("X BBBBBBBB: which = 0 (zero movement), player.x = %f, x = %f\n", data->player.x, x);
        return; // Don't process zero movement
    }
	if(can_move)
	{
		if (data->player.y - (int)data->player.y > 0.8001) // 0.8
		{
			if (!check_if_wall(data, data->player.y + 1, data->player.x + x + offset))
			{
				//printf("DEBUG: y_fraction = %.20f\n", data->player.y - (int)data->player.y);
				//printf("1 AAAAAAAAAAA, which = %d, player.y = %f, player.x = %f, x = %f\n", which, data->player.y, data->player.x, x);
				/* if (x > 0 && data->player.x - (int)data->player.x < 0.8001) // 0.8
				{
					x = (int)data->player.x + 1 - offset - data->player.x;
				}
				else if (x < 0 && data->player.x - (int)data->player.x > 0.1999) //0.2
				{
					x = (int)data->player.x - offset - data->player.x;
				} */
				move_to_boundary_x(data, &x, offset);
				//return ;
			}
		}
		else if (data->player.y - (int)data->player.y < 0.1999) //0.2
		{
			if (!check_if_wall(data, data->player.y - 1, data->player.x + x + offset))
			{
				//printf("DEBUG: y_fraction = %.20f\n", data->player.y - (int)data->player.y);
				//printf("2 AAAAAAAAAAA, which = %d, player.y = %f, player.x = %f, x = %f\n", which, data->player.y, data->player.x, x);
				/* if (x > 0 && data->player.x - (int)data->player.x < 0.8001) // 0.8
				{
					x = (int)data->player.x + 1 - offset - data->player.x;
				}
				else if (x < 0 && data->player.x - (int)data->player.x > 0.1999) //0.2
				{
					x = (int)data->player.x - offset - data->player.x;
				} */
				move_to_boundary_x(data, &x, offset);
				//return ;
			}
		}
		data->player.x += x;
		data->movement_happend = true;
	}
	//printf("X After: which = %d, player.x = %f, x = %f\n", which, data->player.x, x);
}