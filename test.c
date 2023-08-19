#include <stdio.h>

// Function to convert a hexadecimal character to its decimal value
int hexToDec(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return 10 + (hex - 'A');
    } else if (hex >= 'a' && hex <= 'f') {
        return 10 + (hex - 'a');
    }
    return -1; // Invalid hexadecimal character
}

// Function to convert RGB to hex color code as an integer
int rgbToHexInt(int red, int green, int blue) {
    int hexInt = 0;

    // Combine red, green, and blue components into an integer
    hexInt = (red << 16) | (green << 8) | blue;

    return hexInt;
}

int main() {
    int red = 135;
    int green = 206;
    int blue = 250;

    int hexColorInt = rgbToHexInt(red, green, blue);

    printf("Hex Color as Integer: %06X\n", hexColorInt);

    return 0;
}
