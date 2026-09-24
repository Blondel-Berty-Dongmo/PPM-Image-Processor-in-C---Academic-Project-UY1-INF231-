#include "image_processor.h"

int main(void) {
    int ch;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        printf("1. Create a PPM image\n");
        printf("2. Darken or lighten your image\n");
        printf("3. Apply the median filter to your image\n");
        printf("4. Convert your image to black and white\n");
        printf("5. Create the negative of your image\n");
        printf("6. Crop your image\n");
        printf("7. Display the size of your image\n");
        printf("0. EXIT\n");
        printf("Select option: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: create_image(); break;
            case 2: adjust_brightness(); break;
            case 3: apply_median_filter(); break;
            case 4: convert_to_grayscale(); break;
            case 5: create_negative(); break;
            case 6: crop_image(); break;
            case 7: display_image_size(); break;
            case 0: return 0;
            default:
                printf("Incorrect Number\n");
                getch();
                break;
        }
    } while (ch != 0);

    return 0;
}
