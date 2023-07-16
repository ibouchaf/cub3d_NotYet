/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:00:41 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/16 17:41:54 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* decimalToHexColor(int dec) {
	char* hexColor = (char*)malloc(8); // 8 characters to store the color (# + 6 hex digits + null terminator)
	if (hexColor == NULL)
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}

	hexColor[0] = '#';
	int index = 0;
	for (int i = 0; i < 6; i++) {
		int nibble = (dec >> (4 * (5 - i))) & 0xF;
		hexColor[index++] = (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
	}
	hexColor[index] = '\0';

	return hexColor;
}
unsigned int hexColorToUInt(const char* colorStr) {
    if (colorStr[0] == '#') {
        // Skip the '#' character
        colorStr++;

        // Convert the hexadecimal string to an unsigned int
        unsigned int result = 0;

        for (int i = 0; i < 6; i++) {
            char c = toupper(colorStr[i]);

            result <<= 4; // Shift left by 4 bits to make room for the next digit

            if (c >= '0' && c <= '9') {
                result |= (c - '0'); // Convert digit (0-9) to integer
            } else if (c >= 'A' && c <= 'F') {
                result |= (c - 'A' + 10); // Convert letter (A-F) to integer
            } else {
                // Invalid character in the input string
                return 0;
            }
        }

        return result;
    } else {
        // Invalid input format, return 0 or handle error as needed
        return 0;
    }
}

// int main() {
//     const char *colorStr = "#9BF274";
//     unsigned int colorValue = hexColorToUInt(colorStr);
//     printf("0x%06X\n", colorValue); // Output: 0x9BF274

//     return 0;
// }


// int main() {
//     int decColor1 = 10220148;
//     int decColor2 = 2745322;

//     char* hexColor1 = decimalToHexColor(decColor1);
//     if (hexColor1 != NULL) {
//         printf("Decimal color %X is represented as hexadecimal color: %s\n", decColor1, hexColor1);
//         free(hexColor1);
//     }

//     char* hexColor2 = decimalToHexColor(decColor2);
//     if (hexColor2 != NULL) {
//         printf("Decimal color %d is represented as hexadecimal color: %s\n", decColor2, hexColor2);
//         free(hexColor2);
//     }

//     return 0;
// }

unsigned int intToHexColor(unsigned int num) {
    unsigned int result = 0;

    // Convert each nibble (4 bits) of the integer to its corresponding hex digit
    for (int i = 5; i >= 0; i--) {
        unsigned int nibble = (num >> (i * 4)) & 0xF; // Extract the next nibble
        result <<= 4; // Shift left by 4 bits to make room for the next digit
        result |= nibble;
    }

    return result;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str = "10,220,148";
  int value = atoi(str);
  printf("%d\n", value);
  return 0;
}
// int RGBToDecimal(char *s) {
// 	char **color = ft_split(s);
// 	int	red;
// 	int	green;
// 	int	blue;

//     int decimal_value = (color[0] << 16) + (green << 8) + blue;
//     return decimal_value;
// }


// int main() {
//     unsigned int inputColor = 10220148;
//     unsigned int hexColor = intToHexColor(inputColor);
//     printf("0x%06X\n", hexColor); // Output: 0x29E3EA

//     return 0;
// }
