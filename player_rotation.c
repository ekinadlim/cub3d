#include "header.h"

void	turn_left(t_data *data, double speed)
{
	data->player.direction -= speed;
	data->movement_happend = true;
	if (data->player.direction < 0)
		data->player.direction += 360;
	data->player.direction_in_radians
		= data->player.direction * PI_180;
}

void	turn_right(t_data *data, double speed)
{
	data->player.direction += speed;
	data->movement_happend = true;
	if (data->player.direction > 360)
		data->player.direction -= 360;
	data->player.direction_in_radians
		= data->player.direction * PI_180;
}