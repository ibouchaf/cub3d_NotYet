/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:00:41 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/15 23:04:12 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char* decimalToHexColor(int dec) {
	char* hexColor = (char*)malloc(8); // 8 characters to store the color (# + 6 hex digits + null terminator)
	if (hexColor == NULL)
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}

	hexColor[0] = '#';
	int index = 1;
	for (int i = 0; i < 6; i++) {
		int nibble = (dec >> (4 * (5 - i))) & 0xF;
		hexColor[index++] = (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
	}
	hexColor[index] = '\0';

	return hexColor;
}

int main() {
    int decColor1 = 10220148;
    int decColor2 = 2745322;

    char* hexColor1 = decimalToHexColor(decColor1);
    if (hexColor1 != NULL) {
        printf("Decimal color %d is represented as hexadecimal color: %s\n", decColor1, hexColor1);
        free(hexColor1);
    }

    char* hexColor2 = decimalToHexColor(decColor2);
    if (hexColor2 != NULL) {
        printf("Decimal color %d is represented as hexadecimal color: %s\n", decColor2, hexColor2);
        free(hexColor2);
    }

    return 0;
}

