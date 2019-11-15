__kernel void  kerlnel_vect (__global int * data, int w, int h, int img_w, int img_h, __global int * img)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x == 200 && y == 200)
	{
		printf("%d %d\n", w, h);
		printf("w: %d h:%d\n", img_w, img_h);
	}
	if (x < img_w && y < img_h)
	{
		data[x + y * get_global_size(0)] = img[x + y * img_w];
	}
	else
		data[x + y * get_global_size(0)] = ((x / (w / 256 + 1) << 16) | (y/(h / 256 + 1) << 8));
}
