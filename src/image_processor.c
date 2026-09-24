#include "image_processor.h"

#ifndef _WIN32
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void create_image(void) {
    FILE *f;
    char file[50], type[2];
    int max, i, j, r, g, b, length, width;

    printf("Enter the name of your PPM image(EX: image.ppm): ");
    scanf("%s", file);
    f = fopen(file, "a");
    printf("Enter the type of your PPM image(EX: P3): ");
    scanf("%s", type);
    fprintf(f, "%s", type);
    printf("Enter the width of your PPM image: ");
    scanf("%d", &width);
    fprintf(f, "\n%d ", width);
    printf("Enter the height of your PPM image: ");
    scanf("%d", &length);
    fprintf(f, "%d", length);
    printf("Enter the maximum value of your PPM image(EX: 255): ");
    scanf("%d", &max);
    fprintf(f, "\n%d", max);
    printf("Enter the RGB values of your image\n");
    fprintf(f, "\n");
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            printf("Line %d pixel %d\n", i + 1, j + 1);
            scanf("%d%d%d", &r, &g, &b);
            fprintf(f, "%d %d %d ", r, g, b);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Image created successfully!\n");
    getch();
}

void adjust_brightness(void) {
    FILE *f, *t;
    char file[50], file2[50], type[2], colour;
    int max, i, j, r, g, b, length, width, fon;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    printf("Enter the file name to create with its extension(EX: image1.ppm) : ");
    scanf("%s", file2);
    f = fopen(file, "r");
    t = fopen(file2, "a");
    fscanf(f, "%s", type);
    fprintf(t, "%s\n", type);
    fscanf(f, "%d%d", &width, &length);
    fprintf(t, "%d %d\n", width, length);
    fscanf(f, "%d", &max);
    fprintf(t, "%d\n", max);
    printf("Enter the value to add or subtract(EX: -34):");
    scanf("%d", &fon);
    printf("Enter the color(EX: R,G,B): ");
    scanf(" %c", &colour);
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            fscanf(f, "%d%d%d", &r, &g, &b);
            if (r >= g && r >= b && colour == 'R') {
                r += fon;
                if (r < 0) r = 0;
                if (r > max) r = max;
            }
            if (g >= r && g >= b && colour == 'G') {
                g += fon;
                if (g < 0) g = 0;
                if (g > max) g = max;
            }
            if (b >= r && b >= g && colour == 'B') {
                b += fon;
                if (b < 0) b = 0;
                if (b > max) b = max;
            }
            fprintf(t, "%d %d %d", r, g, b);
            fprintf(t, " ");
        }
        fprintf(t, "\n");
    }
    if (fon < 0) {
        printf("Image darkened successfully!\n");
    } else {
        printf("Image lightened successfully!\n");
    }
    fclose(f);
    fclose(t);
    getch();
}

void apply_median_filter(void) {
    FILE *f, *t;
    char file[50], file2[50], type[2];
    int max, i, j, r, g, b, length, width, l, c1;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    printf("Enter the file name to create with its extension(EX: image1.ppm) : ");
    scanf("%s", file2);

    f = fopen(file, "r");
    t = fopen(file2, "a");

    if (f == NULL || t == NULL) {
        printf("File opening error.\n");
        getch();
        return;
    }

    fscanf(f, "%s", type);
    fprintf(t, "%s\n", type);
    fscanf(f, "%d%d", &width, &length);
    fprintf(t, "%d %d\n", width, length);
    fscanf(f, "%d", &max);
    fprintf(t, "%d\n", max);

    int total = width * length;
    int R[100000], G[100000], B[100000];
    for (i = 0; i < total; i++) {
        fscanf(f, "%d%d%d", &r, &g, &b);
        R[i] = r;
        G[i] = g;
        B[i] = b;
    }

    int neighbor[9], a, b_idx, temp;
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            int k = 0;
            for (l = -1; l <= 1; l++) {
                for (c1 = -1; c1 <= 1; c1++) {
                    int x = i + l;
                    int y = j + c1;
                    if (x >= 0 && x < length && y >= 0 && y < width) {
                        neighbor[k] = R[x * width + y];
                        k++;
                    }
                }
            }
            for (a = 0; a < k; a++) {
                for (b_idx = a + 1; b_idx < k; b_idx++) {
                    if (neighbor[a] > neighbor[b_idx]) {
                        temp = neighbor[a];
                        neighbor[a] = neighbor[b_idx];
                        neighbor[b_idx] = temp;
                    }
                }
            }
            int newR = neighbor[k / 2];

            k = 0;
            for (l = -1; l <= 1; l++) {
                for (c1 = -1; c1 <= 1; c1++) {
                    int x = i + l;
                    int y = j + c1;
                    if (x >= 0 && x < length && y >= 0 && y < width) {
                        neighbor[k] = G[x * width + y];
                        k++;
                    }
                }
            }
            for (a = 0; a < k; a++) {
                for (b_idx = a + 1; b_idx < k; b_idx++) {
                    if (neighbor[a] > neighbor[b_idx]) {
                        temp = neighbor[a];
                        neighbor[a] = neighbor[b_idx];
                        neighbor[b_idx] = temp;
                    }
                }
            }
            int newG = neighbor[k / 2];

            k = 0;
            for (l = -1; l <= 1; l++) {
                for (c1 = -1; c1 <= 1; c1++) {
                    int x = i + l;
                    int y = j + c1;
                    if (x >= 0 && x < length && y >= 0 && y < width) {
                        neighbor[k] = B[x * width + y];
                        k++;
                    }
                }
            }
            for (a = 0; a < k; a++) {
                for (b_idx = a + 1; b_idx < k; b_idx++) {
                    if (neighbor[a] > neighbor[b_idx]) {
                        temp = neighbor[a];
                        neighbor[a] = neighbor[b_idx];
                        neighbor[b_idx] = temp;
                    }
                }
            }
            int newB = neighbor[k / 2];

            fprintf(t, "%d %d %d ", newR, newG, newB);
        }
        fprintf(t, "\n");
    }

    fclose(f);
    fclose(t);
    printf("Median filter applied successfully!\n");
    getch();
}

void convert_to_grayscale(void) {
    FILE *f, *t;
    char file[50], file2[50], type[2];
    int max, i, j, r, g, b, length, width, intensity;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    printf("Enter the file name to create with its extension(EX: image1.ppm) : ");
    scanf("%s", file2);
    f = fopen(file, "r");
    t = fopen(file2, "a");
    fscanf(f, "%s", type);
    fprintf(t, "%s\n", type);
    fscanf(f, "%d%d", &width, &length);
    fprintf(t, "%d %d\n", width, length);
    fscanf(f, "%d", &max);
    fprintf(t, "%d\n", max);
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            fscanf(f, "%d%d%d", &r, &g, &b);
            intensity = (r + g + b) / 3;
            fprintf(t, "%d %d %d", intensity, intensity, intensity);
            fprintf(t, " ");
        }
        fprintf(t, "\n");
    }
    fclose(f);
    fclose(t);
    printf("Image converted to black and white successfully!\n");
    getch();
}

void create_negative(void) {
    FILE *f, *t;
    char file[50], file2[50], type[2];
    int max, i, j, r, g, b, length, width;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    printf("Enter the file name to create with its extension(EX: image1.ppm) : ");
    scanf("%s", file2);
    f = fopen(file, "r");
    t = fopen(file2, "a");
    fscanf(f, "%s", type);
    fprintf(t, "%s\n", type);
    fscanf(f, "%d%d", &width, &length);
    fprintf(t, "%d %d\n", width, length);
    fscanf(f, "%d", &max);
    fprintf(t, "%d\n", max);
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            fscanf(f, "%d%d%d", &r, &g, &b);
            r = 255 - r;
            b = 255 - b;
            g = 255 - g;
            fprintf(t, "%d %d %d", r, g, b);
            fprintf(t, " ");
        }
        fprintf(t, "\n");
    }
    fclose(f);
    fclose(t);
    printf("Image inverted successfully!\n");
    getch();
}

void crop_image(void) {
    FILE *f, *t;
    char file[50], file2[50], type[2];
    int max, i, j, r, g, b, length, width;
    int l1, l2, c1, c2, w, l, u = 0;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    printf("Enter the file name to create with its extension(EX: image1.ppm) : ");
    scanf("%s", file2);
    f = fopen(file, "r");
    t = fopen(file2, "a");
    fscanf(f, "%s", type);
    fprintf(t, "%s\n", type);
    fscanf(f, "%d%d", &width, &length);
    printf("Enter length1 and length2 row-wise(Note: length1<length2)\n");
    scanf("%d%d", &l1, &l2);
    while (l2 > length || l1 >= l2) {
        printf("Your row lengths are incorrect. Re-enter\n");
        scanf("%d%d", &l1, &l2);
    }
    l = l2 - l1;
    printf("Enter length1 and length2 column-wise(Note: length1<length2)\n");
    scanf("%d%d", &c1, &c2);
    while (c2 > width || c1 >= c2) {
        printf("Your column lengths are incorrect. Re-enter\n");
        scanf("%d%d", &c1, &c2);
    }
    w = c2 - c1;
    fprintf(t, "%d %d\n", w, l);
    fscanf(f, "%d", &max);
    fprintf(t, "%d\n", max);
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            fscanf(f, "%d%d%d", &r, &g, &b);
            if (i >= l1 && i <= l2) {
                if (j >= c1 && j <= c2) {
                    fprintf(t, "%d %d %d ", r, g, b);
                    u = 1;
                }
            }
        }
        if (u == 1) {
            fprintf(t, "\n");
        }
    }
    fclose(f);
    fclose(t);
    printf("Image cropped successfully!\n");
    getch();
}

void display_image_size(void) {
    FILE *f;
    char file[50], type[2];
    int length, width;

    printf("Enter the file name with its extension(EX: image.ppm) : ");
    scanf("%s", file);
    f = fopen(file, "r");
    if (f == NULL) {
        printf("File not found!\n");
        getch();
        return;
    }
    fscanf(f, "%s", type);
    fscanf(f, "%d%d", &width, &length);
    printf("Size=%dX%d\n", width, length);
    fclose(f);
    getch();
}
