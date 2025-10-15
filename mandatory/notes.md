PARSER

	Spaces can be anywhere except in the map

	Textures:
		valid 4 directions
		files are valid textures

	Colors:
		valid Floor/Ceiling character
		valid rgb values seperated by commas
		convert to hex

	Map:
		valid chars
		closed/surrounded by walls
		maybe replace spaces with walls so the player cant go through

EXECUTION

	Movement:

	Raycasting:
		dda?

	Display:

main.c:238:19: runtime error: -inf is outside the range of representable values of type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior main.c:238:19 in 
main.c:239:17: runtime error: inf is outside the range of representable values of type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior main.c:239:17 in 
main.c:277:11: runtime error: inf is outside the range of representable values of type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior main.c:277:11 in 
main.c:278:19: runtime error: signed integer overflow: -2147483648 * 51 cannot be represented in type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior main.c:278:19 in 
main.c:280:19: runtime error: -nan is outside the range of representable values of type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior main.c:280:19 in

//maybe limit map size just in case of int overflow
//use inline function??? (probably not)
//make t_data *data const if function will not modify it???
//what is 'X'?
