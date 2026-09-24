#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    int getch(void);
#endif

void create_image(void);
void adjust_brightness(void);
void apply_median_filter(void);
void convert_to_grayscale(void);
void create_negative(void);
void crop_image(void);
void display_image_size(void);

#endif
