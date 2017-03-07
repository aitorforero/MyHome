#ifndef _Image_h
#define _Image_h

typedef struct {
  uint16_t        width;    
  uint16_t        height;  
  uint8_t         paletteLength;   
  uint8_t         transparentColor;  
  uint8_t         bitsPerPixel;  
  Const uint16_t   *palette; 
  Const uint16_t   *pixels;  
} ImageData;

class Image
{
    public:
        static void draw(int16_t x, int16_t y, const  ImageData *data) 
        {
            uint16_t i,j;
            for(j = 0; j < data->height; j++) {
                for(i = 0; i < data->width; i++) {
                    uint16_t pos = (j * data->width + i) * data->bitsPerPixel;
                    
                    uint16_t dataPos = pos / 16;
                    uint8_t dataDesp = pos % 16;
                    
                    uint16_t color = pgm_read_word(data->pixels+dataPos) << (data->bitsPerPixel - dataDesp);
                    if (dataDesp + bitsPerPixel > 16) 
                    {
                       color +=  pgm_read_word(data->pixels+dataPos+1) >> //TODO
                    }
                    
                    drawPixel(x+i, y+j, color);
                }
            }
        }
}

#endif