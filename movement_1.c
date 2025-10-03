#include "header.h"

void	move_forward(t_data *data)
{
	double x = cos(data->player.direction_in_radians) * (4 * data->delta_time);
	double y = sin(data->player.direction_in_radians) * (4 * data->delta_time);
	//double offset; //can just pass either 0.2 or -0.2 inside the function to save 3 lines

	if (y < 0)
		move_y(data, y, -0.2);
	else
		move_y(data, y, 0.2);
	if (x < 0)
		move_x(data, x, -0.2);
	else
		move_x(data, x, 0.2);
}

void	move_backwards(t_data *data)
{
	double x = cos(data->player.direction_in_radians) * (-4 * data->delta_time);
	double y = sin(data->player.direction_in_radians) * (-4 * data->delta_time);
	//double offset;

	if (y < 0)
		move_y(data, y, -0.2);
	else
		move_y(data, y, 0.2);
	if (x < 0)
		move_x(data, x, -0.2);
	else
		move_x(data, x, 0.2);
}

void	move_left(t_data *data)
{
	double x = cos(data->player.direction_in_radians - M_PI_2) * (4 * data->delta_time);
	double y = sin(data->player.direction_in_radians - M_PI_2) * (4 * data->delta_time);
	//double offset;

	if (y < 0)
		move_y(data, y, -0.2);
	else
		move_y(data, y, 0.2);
	if (x < 0)
		move_x(data, x, -0.2);
	else
		move_x(data, x, 0.2);
}

void	move_right(t_data *data)
{
	double x = cos(data->player.direction_in_radians + M_PI_2) * (4 * data->delta_time);
	double y = sin(data->player.direction_in_radians + M_PI_2) * (4 * data->delta_time);
	//double offset;

	if (y < 0)
		move_y(data, y, -0.2);
	else
		move_y(data, y, 0.2);
	if (x < 0)
		move_x(data, x, -0.2);
	else
		move_x(data, x, 0.2);
}
