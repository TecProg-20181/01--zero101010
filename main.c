#include <stdio.h>

typedef struct pixel {     //pixel
    unsigned short int r;   // colocar red,green and blue
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct image {     //image
    // [width][height][rgb]
    // 0 -> r
    // 1 -> g
    // 2 -> b
    unsigned short int pixel[512][512][3];
    unsigned int width;            
    unsigned int height;            
} Image;
int max(int a, int b) {
    if (a > b)
        return b;
return a;
}
int calcular_media(int argumento_1,int argumento_2,int argumento_3){
    float soma=argumento_1+argumento_2+argumento_3;
return soma/3;
}

Image aplicar_escala_cinza(Image imagem) {

    for (unsigned int i = 0; i < imagem.height; ++i) {      //ler todas as linhas
        for (unsigned int j = 0; j < imagem.width; ++j) {  //ler todas as colunas
            int media = calcular_media(imagem.pixel[i][j][0],
                                       imagem.pixel[i][j][1],
                                       imagem.pixel[i][j][2]
                                       );
            ///Fazer método para inverter pixels 
            imagem.pixel[i][j][0] = media;  
            imagem.pixel[i][j][1] = media;
            imagem.pixel[i][j][2] = media;
        }
    }

    return imagem;
}

unsigned short int transformar_pixel(double a,double b,double c,unsigned short int *pixel){
    //trocar nome p
   
    int p = pixel[0] * a + 
            pixel[1] * b + 
            pixel[2] * c;

    int menor_r = max(255,p);// usar um método para comparar 
    return menor_r;
                }
            
Image aplicar_sepia(Image imagem){
  	for (unsigned int x = 0; x < imagem.height; ++x){
        for (unsigned int j = 0; j < imagem.width; ++j) {
            unsigned short int pixel[3];
            
            pixel[0] = imagem.pixel[x][j][0];
            pixel[1] = imagem.pixel[x][j][1];
            pixel[2] = imagem.pixel[x][j][2];
            
            imagem.pixel[x][j][0]=transformar_pixel(0.393,0.769,0.189,pixel);
            imagem.pixel[x][j][1]=transformar_pixel(0.349,0.686,0.168,pixel); 
            imagem.pixel[x][j][2]=transformar_pixel(0.272,0.534,0.131,pixel); 
        }
    }
    
    return imagem; 
}

void blur(unsigned int height, unsigned short int pixel[512][512][3], unsigned int width) {
    int T = 0;
    scanf("%d", &T);
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                Pixel media = {0, 0, 0};

                int menor_h = max(height - 1 , i + T/2);
                int min_w = max(width - 1 , j + T/2); 
                //usar max() sem zoar a imagem
                for(unsigned int x = (0 > i - T/2 ? 0 : i - T/2); x <= menor_h; ++x) {
                    for(unsigned int y = (0 > j - T/2 ? 0 : j - T/2); y <= min_w; ++y) {
                        media.r += pixel[x][y][0];
                        media.g += pixel[x][y][1];
                        media.b += pixel[x][y][2];
                    }
                }

            media.r /= T * T;
            media.g /= T * T;
            media.b /= T * T;

            pixel[i][j][0] = media.r;
            pixel[i][j][1] = media.g;
            pixel[i][j][2] = media.b;
        }
    }
}

Image rotacionar90direita(Image imagem) {
    Image rotacionada;
    int quantas_vezes = 0;
    scanf("%d", &quantas_vezes);
    quantas_vezes %= 4;
    for (int j = 0; j < quantas_vezes; ++j) {
        rotacionada.width = imagem.height;
        rotacionada.height = imagem.width;

        for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
            for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
                rotacionada.pixel[i][j][0] = imagem.pixel[x][y][0];
                rotacionada.pixel[i][j][1] = imagem.pixel[x][y][1];
                rotacionada.pixel[i][j][2] = imagem.pixel[x][y][2];
            }
        }
    }
    return rotacionada;
}
Image Espelhamento(Image imagem){
    int horizontal = 0;
    scanf("%d", &horizontal);

    int width = imagem.width, height = imagem.height;

    if (horizontal == 1) width /= 2;
    else height /= 2;

    for (int i2 = 0; i2 < height; ++i2) {
        for (int j = 0; j < width; ++j) {
            int x = i2, y = j;

             if (horizontal == 1) y = imagem.width - 1 - j;
             else x = imagem.height - 1 - i2;

            Pixel aux1;
            aux1.r = imagem.pixel[i2][j][0];
            aux1.g = imagem.pixel[i2][j][1];
            aux1.b = imagem.pixel[i2][j][2];

            imagem.pixel[i2][j][0] = imagem.pixel[x][y][0];
            imagem.pixel[i2][j][1] = imagem.pixel[x][y][1];
            imagem.pixel[i2][j][2] = imagem.pixel[x][y][2];

            imagem.pixel[x][y][0] = aux1.r;
            imagem.pixel[x][y][1] = aux1.g;
            imagem.pixel[x][y][2] = aux1.b;
                    }
                }
    return imagem;
}

void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}

Image cortar_imagem(Image imagem) {
    int x, y;
    scanf("%d %d", &x, &y);
    int width, height;
    scanf("%d %d", &width, &height);
    Image cortada;

    cortada.width = width;
    cortada.height = height;

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            cortada.pixel[i][j][0] = imagem.pixel[i + y][j + x][0];
            cortada.pixel[i][j][1] = imagem.pixel[i + y][j + x][1];
            cortada.pixel[i][j][2] = imagem.pixel[i + y][j + x][2];
        }
    }

    return cortada;
}
void printar_resultados(Image imagem){

    printf("P3\n");
        // print width height and color of image
    printf("%u %u\n255\n", imagem.width, imagem.height);

    // print pixels of image
    for (unsigned int i = 0; i < imagem.height; ++i) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
            printf("%hu %hu %hu ", imagem.pixel[i][j][0],
                                   imagem.pixel[i][j][1],
                                   imagem.pixel[i][j][2]);

        }
        printf("\n");
    }

}

int main() {
    Image imagem;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &imagem.width, &imagem.height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < imagem.height; ++i) {
        for (unsigned int j = 0; j < imagem.width; ++j) {
            scanf("%hu %hu %hu", &imagem.pixel[i][j][0],
                                 &imagem.pixel[i][j][1],
                                 &imagem.pixel[i][j][2]);

        }
    }

    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { // Escala de Cinza
                imagem = aplicar_escala_cinza(imagem);  //ok
                break;
            }
            case 2: { // Filtro Sepia
                imagem = aplicar_sepia(imagem); //ok

                break;
            }
            case 3: { // Blur
               
                blur(imagem.height, imagem.pixel, imagem.width); //ok
                break;
            }
            case 4: { // Rotacao
               
                    imagem = rotacionar90direita(imagem); //ok
                
                break;
            }
            case 5: { // Espelhamento
                    imagem= Espelhamento(imagem);       //ok
                    
                break;
            }
            case 6: { // Inversao de Cores
                inverter_cores(imagem.pixel, imagem.width, imagem.height);
                break;
            }
            case 7: { // Cortar Imagem
                imagem = cortar_imagem(imagem);
                break;
            }
        }

    }

    // print type of image
    printar_resultados(imagem);
    return 0;
}
