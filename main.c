#include <stdio.h>

typedef struct pixel {     //pixel
    unsigned short int red;   // colocar red,green and blue
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct image{     //image
    // [width]aheight][rgb]
    // 0 -> r
    // 1 -> g
    // 2 -> b

    Pixel pixel[512][512];
    unsigned int width;            
    unsigned int height;            
} Image;

int minimum(int a, int b){
    if (a > b)
       	 return b;
return a;
}
int maximum(int a ,int b){
	if (a > b)
       	 return a;
return b;
}


int calculate_average_sum(int a,int b,int c){
    float sum=a+b+c;
return sum/3;
}



Image apply_scale_grey(Image imagem) {

    for (unsigned int i = 0; i < imagem.height; ++i) {     
        for (unsigned int j = 0; j < imagem.width; ++j) {  
            int media = calculate_average_sum(imagem.pixel[i][j].red,
                                       imagem.pixel[i][j].green,
                                       imagem.pixel[i][j].blue
                                       );
            ///Fazer método para inverter pixels 
            imagem.pixel[i][j].red = media;  
            imagem.pixel[i][j].green = media;
            imagem.pixel[i][j].blue = media;
        }
   }

return imagem;
}

unsigned short int change_pixels(double a,double b,double c,Pixel pixel) { 
   
     int p = pixel.red * a + 
             pixel.green * b + 
             pixel.blue * c;

    int menor_r = minimum(255,p);
return menor_r;
}
            
Image apply_sepia(Image imagem){
  	for (unsigned int x = 0; x < imagem.height; ++x) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
            Pixel pixel;
            
          pixel.red = imagem.pixel[x][j].red;
          pixel.green = imagem.pixel[x][j].green;
          pixel.blue = imagem.pixel[x][j].blue;
            
            imagem.pixel[x][j].red=change_pixels(0.393,0.769,0.189,pixel);
            imagem.pixel[x][j].green=change_pixels(0.349,0.686,0.168,pixel); 
            imagem.pixel[x][j].blue=change_pixels(0.272,0.534,0.131,pixel); 
        }
    }
  
return imagem; 
}

Image apply_blur(Image imagem) {
    int T = 0;
    scanf("%d", &T);
        for ( unsigned short int i = 0; i < imagem.height; ++i) {
            for ( unsigned short int j = 0; j < imagem.width; ++j) {
                Pixel media = {0, 0, 0};

                int menor_h = minimum(imagem.height - 1 , i + T/2);
                int min_w = minimum(imagem.width - 1 , j + T/2); 
                
                for(unsigned short int x = maximum(0 ,i - T/2); x <= menor_h; ++x) {
                    for(unsigned short int y = maximum(0 , j - T/2); y <= min_w; ++y) {
                        media.red += imagem.pixel[x][y].red;
                        media.green += imagem.pixel[x][y].green;
                        media.blue += imagem.pixel[x][y].blue;
                    }
                }

            media.red /= T * T;
            media.green /= T * T;
            media.blue /= T * T;

            imagem.pixel[i][j].red = media.red;
            imagem.pixel[i][j].green = media.green;
            imagem.pixel[i][j].blue = media.blue;
        }
 
 	 }
 return imagem;
}
Image rotation_90_right(Image imagem) {
    Image rotacionada;
        rotacionada.width = imagem.height;
        rotacionada.height = imagem.width;

        for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
            for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
                rotacionada.pixel[i][j]= imagem.pixel[x][y];
            }
        }
    
return rotacionada;
}

Image apply_rotation(Image imagem){

    int times = 0; 
    scanf("%d", &times);
    times %= 4;
    for (int j = 0; j < times; ++j) {
    	imagem=rotation_90_right(imagem);

	}
return imagem;
}

Image mirroring(Image imagem){
    int horizontal = 0;
    scanf("%d", &horizontal);

    int width = imagem.width, height = imagem.height;

    if (horizontal == 1) width /= 2;
    else height /= 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int x = i, y = j;
			
			if (horizontal == 1) y = imagem.width - 1 - j;
            else x = imagem.height - 1 - i;

            Pixel aux1;
            aux1 = imagem.pixel[i][j];
            imagem.pixel[i][j] = imagem.pixel[x][y];
            imagem.pixel[x][y] = aux1;
        } 
    }
    return imagem;
}

Pixel sub_pixel_max(Pixel pixel){
	 pixel.red = 255 - pixel.red;
     pixel.green = 255 - pixel.green;
     pixel.blue = 255 - pixel.blue;
return pixel;
}


Image invert_colors(Image imagem) {
    for (unsigned int i = 0; i < imagem.height; ++i) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
	    	imagem.pixel[i][j]=sub_pixel_max(imagem.pixel[i][j]);
        }
    }
return imagem;
}

Image cut_image(Image imagem) {
    int x, y;
    scanf("%d %d", &x, &y);
    int width, height;
    scanf("%d %d", &width, &height);
    Image cortada;

    cortada.width = width;
    cortada.height = height;

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            cortada.pixel[i][j] = imagem.pixel[i + y][j + x];
           
         }
    }

 return cortada;
}
void print_image(Image imagem){

    printf("P3\n");
        // print width height and color of image
    printf("%u %u\n255\n", imagem.width, imagem.height);

    // print pixels of image
    for (unsigned int i = 0; i < imagem.height; ++i) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
            printf("%hu %hu %hu ", imagem.pixel[i][j].red,
                                   imagem.pixel[i][j].green,
                                   imagem.pixel[i][j].blue);

         }
        printf("\n");
    }

}

Image image_reading(Image imagem){
	char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &imagem.width, &imagem.height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < imagem.height; ++i) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
            scanf("%hu %hu %hu", &imagem.pixel[i][j].red,
                                 &imagem.pixel[i][j].green,
                                 &imagem.pixel[i][j].blue);

         }
     }
return imagem;
}

int main() {
    Image imagem;


    imagem=image_reading(imagem);
    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { // Escala de Cinza
            
                imagem = apply_scale_grey(imagem);  //ok
            
            break;
            }
            case 2: { // Filtro Sepia
            
                imagem = apply_sepia(imagem); //ok

                break;
            }
            case 3: { // Apply_blur
               
                imagem = apply_blur(imagem); //ok
             
             break;
            }
            case 4: { // Rotacao
               
                    imagem = apply_rotation(imagem); //ok
                
            break;
            }
            case 5: { // Espelhamento
            
                    imagem= mirroring(imagem);       //ok
                    
            break;
            }
           case 6: { // Inversao de Cores
            
                imagem =invert_colors(imagem);
            
            break;
            }
            case 7: { // Cortar Imagem
            
                imagem = cut_image(imagem);
            
            break;
            }
        }

    }

    // print type of image
    print_image(imagem);
 return 0;
}
