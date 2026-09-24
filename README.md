# PPM Image Processor (C Project)

A C-based command-line utility for manipulating and processing **Portable Pixmap (PPM / P3)** ASCII images, supporting pixel transformations, filters, and image metadata manipulation.

## Academic Context & Background

- **University:** University of Yaoundé 1 (UY1), Cameroon
- **Current Academic Level:** 3rd Year Computer Science Student (L3)
- **Project Origin:** Course practical exercise for **INF231 (Data Structures / Algorithms)** during 2nd Year (L2)
- **Supervising Professor:** Pr. Melatagia

This repository highlights foundational algorithms developed independently during my undergraduate studies at UY1 as part of my practical work in procedural C programming and image manipulation.

## Features

1. **PPM Creation:** Generate dynamic P3 ASCII PPM files with customized dimensions and RGB values.
2. **Channel Brightness Adjustment:** Dynamically lighten or darken selective RGB channels.
3. **Median Filter Implementation:** Apply noise-reduction algorithms using 3x3 pixel neighborhood sorting.
4. **Grayscale Conversion:** Transform color images into black & white using intensity averaging.
5. **Color Inversion (Negative):** Compute 255-channel inverse values for full negative processing.
6. **Sub-region Cropping:** Extract custom sub-matrices from source image coordinates.
7. **Metadata Inspector:** Parse header specifications for dimension inspections.

## Build and Compilation Instructions

### Compilation via Makefile

To compile using GCC on Linux/macOS or MinGW on Windows:

```bash
make
