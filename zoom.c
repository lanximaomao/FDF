#include <stdio.h>

//int zoom(t_map input)
//{
//	if (input.size_x > input.size_y)
//		return (1000/input.size_x);
//	else
//		return(1000/input.size_y);
//}

int main()
{
	int scale;

	//input.size_x = 10;
	//input.size_y = 13;

	scale = 1000 / 13;
	printf("%d\n", scale);
	return (0);
}
