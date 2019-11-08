__kernel void  kerlnel_vect (__global int * data)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	data[x + y * get_global_size(0)] = 0xFF0000;
}
