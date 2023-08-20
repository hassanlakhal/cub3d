#include "cub3d.h"

// Function to convert a hexadecimal character to its decimal value
// int hexToDec(char hex) {
//     if (hex >= '0' && hex <= '9') {
//         return hex - '0';
//     } else if (hex >= 'A' && hex <= 'F') {
//         return 10 + (hex - 'A');
//     } else if (hex >= 'a' && hex <= 'f') {
//         return 10 + (hex - 'a');
//     }
//     return -1; // Invalid hexadecimal character
// }

// // Function to convert RGB to hex color code as an integer
// int rgbToHexInt(int red, int green, int blue) {
//     int hexInt = 0;

//     // Combine red, green, and blue components into an integer
//     hexInt = (red << 16) | (green << 8) | blue;

//     return hexInt;
// }

// int main() {
//     int red = 135;
//     int green = 206;
//     int blue = 250;

//     int hexColorInt = rgbToHexInt(red, green, blue);

//     printf("Hex Color as Integer: %06X\n", hexColorInt);

//     return 0;
// }

typedef struct s_data1
{
    unsigned int *clo;
    int img_width; 
    int img_height;
    int bpp;
    int size_l; 
    int endian;
    void *img;
    void *img1;
    
} t_data1;


static int my_mlx_get_pixel(t_data1 *info, int x, int y)
{
	 unsigned int *dst;
	dst = info->clo + (y * info->size_l + x * (info->bpp / 8));
	return *dst;
}
static void my_mlx_put_pixel(t_data1 *info, int x, int y,int pixel)
{
	 unsigned int *dst;
	dst = info->clo + (y * info->size_l + x * (info->bpp / 8));
	*dst = pixel;
}

int main(void)
{
    void *mlx, *win;
    t_data1 info;
    // unsigned int *data;
    // int img_width, img_height;
    // int bpp, size_l, endian;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 640, 480, "mlx_title");
  
    info.img = mlx_xpm_file_to_image(mlx, "./texture/wall.xpm", &info.img_width, &info.img_height); 
    info.img1 = mlx_new_image(mlx, 640, 480);
     
    info.clo =(unsigned int *) mlx_get_data_addr(info.img, &info.bpp, &info.size_l, &info.endian);
    
    int a = my_mlx_get_pixel(&info,1,1);
   
    int i;
    int j;
    i = 0;
    printf("====%d====\n",a);
   while (i < 10)
   {
        j = 0;
        while (j < 10)
        {
             my_mlx_put_pixel(&info,1 + j,1 + i,a);
             j++; 
        }
     i++;  
   }
    //  for(int i = 0; i < img_height; i++)
    //     for (int j = 0; j < img_width; j++)
    //         if (i % 2 == 0)
    //             data[size_l / 4 * i + j] = 0xFFFFFFF;
    // }
   // exit(12);
    mlx_put_image_to_window(mlx, win, info.img, 100, 200);
    //exit(0);
    mlx_loop(mlx);

    return 0;
}