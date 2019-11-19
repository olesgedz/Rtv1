// __kernel void gaussian_blur(
// 		__read_only image2d_t image,
// 		__constant float * mask,
// 		__global float * blurredImage,
// 		__private int maskSize
// 	) {

// 	const int2 pos = {get_global_id(0), get_global_id(1)};
	
// 	// Collect neighbor values and multiply with gaussian
// 	float sum = 0.0f;
// 	// Calculate the mask size based on sigma (larger sigma, larger mask)
// 	for(int a = -maskSize; a < maskSize+1; a++) {
// 		for(int b = -maskSize; b < maskSize+1; b++) {
// 			sum += mask[a+maskSize+(b+maskSize)*(maskSize*2+1)]
// 				*read_imagef(image, sampler, pos + (int2)(a,b)).x;
// 		}
// 	}

// 	blurredImage[pos.x+pos.y*get_global_size(0)] = sum;
// }


__kernel void gaussian_blur(__global int *input, __global *output , int samples, int maskSize)
{
	const int2 pos = {get_global_id(0), get_global_id(1)};
	float3 sum = 0.f;
	for(int a = -maskSize; a < maskSize+1; a++) {
		for(int b = -maskSize; b < maskSize+1; b++) {
			sum += vect_temp[(pos.x + a) + (pos.y  + b)* get_global_size(0)];
		}
	}
	output[pos.x + pos.y * get_global_size(0)] = ft_rgb_to_hex(toInt(sum.x / (float)samples),
		toInt(sum.y / (float)samples), toInt(sum.z / (float)samples));
}