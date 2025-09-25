#include "header.h"

void	move_forward(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (4 * data->delta_time);
	double y = sin(radian) * (4 * data->delta_time);
	double offset; //can just pass either 0.2 or -0.2 inside the function to save 3 lines

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_y(data, y, offset);
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_x(data, x, offset);
}

void	move_backwards(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian) * (-4 * data->delta_time);
	double y = sin(radian) * (-4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_y(data, y, offset);
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_x(data, x, offset);
}

void	move_left(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian - (M_PI / 2)) * (4 * data->delta_time);
	double y = sin(radian - (M_PI / 2)) * (4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_y(data, y, offset);
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_x(data, x, offset);
}

void	move_right(t_data *data)
{
	double radian = data->player.direction * M_PI / 180.0;
	double x = cos(radian + (M_PI / 2)) * (4 * data->delta_time);
	double y = sin(radian + (M_PI / 2)) * (4 * data->delta_time);
	double offset;

	if (y < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_y(data, y, offset);
	if (x < 0)
		offset = -0.2;
	else
		offset = 0.2;
	move_x(data, x, offset);
}
