#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //lib to use TRUE
#include <stdint.h> //lib to use typedef

typedef uint8_t BYTE;

int FILE_BLOCK_SIZE = 512; //var to keep the size of the buffer

void process_file(FILE *file);
bool is_jpeg_header(BYTE file[]);

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }
    
    //open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    process_file(file);    
    
    fclose(file);
}

void process_file(FILE *file)
{
    
    int jpeg_number = 0;
    FILE *jpeg_file;
    
    while (true)
    {
        BYTE file_block[FILE_BLOCK_SIZE];
        int read_bytes = fread(&file_block, FILE_BLOCK_SIZE, 1, file);
        if (read_bytes != 1)
        {
            break;
        }
        
        //verifica se é um JPEG válido
        if (is_jpeg_header(file_block))
        {
            if (jpeg_number > 0)
            {
                fclose(jpeg_file);
            }
            
            //create file name
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_number);
            jpeg_number++;
            
            //printf("jpeg found %s\n", filename);
            jpeg_file = fopen(filename, "w");
        }
        
        if (jpeg_number > 0)
        {
            fwrite(file_block, FILE_BLOCK_SIZE, 1, jpeg_file);
        }
    }
    if (jpeg_number > 0)
    {
        fclose(jpeg_file);
    }
}

bool is_jpeg_header(BYTE file_block[])
{
    return file_block[0] == 0xff 
           && file_block[1] == 0xd8 
           && file_block[2] == 0xff 
           && (file_block[3] >= 0xe0     && file_block[3] <= 0xef);
}