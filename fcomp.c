#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Usage: comapre <a> <b>\n");
		return 0;
	}
	FILE *a = fopen(argv[1], "rb");
	FILE *b = fopen(argv[2], "rb");
	if (a == NULL) {
		printf("Error opening %s\n", argv[1]);
		return 1;
	}
	if (b == NULL) {
		printf("Error opening %s\n", argv[2]);
		return 1;
	}
	// get the size of each file and calc the smaller
	fseek(a, 0, SEEK_END);
	fseek(b, 0, SEEK_END);
	int a_length = ftell(a);
	int b_length = ftell(b);
	int smaller = a_length < b_length ? a_length : b_length;
	rewind(a);
	rewind(b);
	
	// read through both files until the end of the smaller
	int differences = 0;
	int a_c;
	int b_c;
	for (int i = 0; i < smaller; i++) {
		a_c = fgetc(a);
		b_c = fgetc(b);
		if (a_c != b_c) {
			differences++;
		}
	}
	if (a_length > b_length) {
		printf("%s is %d bytes bigger\n", argv[1], a_length-b_length);
	}
	else if (b_length > a_length) {
		printf("%s is %d bytes bigger\n", argv[2], b_length-a_length);
	}
	int percent = ((float)differences / (float)smaller) * 100 + 0.5;
	printf("There are %d bytes that are different (%d%)\n", differences, percent);
	fclose(a);
	fclose(b);
	return 0;
}
