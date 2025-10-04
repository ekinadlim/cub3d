#include "header.h"

void	move_forward(t_data *data)
{
	double x = cos(data->player.direction_in_radians) * (MOVEMENT_SPEED * data->delta_time); //data->player.direction_sin??????
	double y = sin(data->player.direction_in_radians) * (MOVEMENT_SPEED * data->delta_time);

	move_y(data, y);
	move_x(data, x);
}

void	move_backwards(t_data *data)
{
	double x = cos(data->player.direction_in_radians) * (-MOVEMENT_SPEED * data->delta_time);
	double y = sin(data->player.direction_in_radians) * (-MOVEMENT_SPEED * data->delta_time);

	move_y(data, y);
	move_x(data, x);
}

void	move_left(t_data *data)
{
	double x = cos(data->player.direction_in_radians - M_PI_2) * (MOVEMENT_SPEED * data->delta_time);
	double y = sin(data->player.direction_in_radians - M_PI_2) * (MOVEMENT_SPEED * data->delta_time);

	move_y(data, y);
	move_x(data, x);
}

void	move_right(t_data *data)
{
	double x = cos(data->player.direction_in_radians + M_PI_2) * (MOVEMENT_SPEED * data->delta_time);
	double y = sin(data->player.direction_in_radians + M_PI_2) * (MOVEMENT_SPEED * data->delta_time);

	move_y(data, y);
	move_x(data, x);
}
