#include "header.h"

void	turn_left(t_data *data, int speed)
{
	data->player.direction -= speed * data->delta_time;
	data->movement_happend = true;
	if (data->player.direction < 0)
		data->player.direction += 360;
}

void	turn_right(t_data *data, int speed)
{
	data->player.direction += speed * data->delta_time;
	data->movement_happend = true;
	if (data->player.direction > 360)
		data->player.direction -= 360;
}