#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"

//Prototyes
void print_binary(uint8_t number);
uint8_t logic_AND(uint8_t a, uint8_t b);
uint8_t logic_OR(uint8_t a, uint8_t b);
uint8_t logic_NAND(uint8_t a, uint8_t b);
uint8_t logic_four_AND(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
uint8_t two_bit_comparator(uint8_t a, uint8_t b);
uint8_t four_bit_vector_comparator(uint8_t va, uint8_t vb);


//Main

int main() {

	printf("*** TRUTH TABLE (4-Bit Vector Comparator) ***\n");
	printf("----------------------------------------------\n");
	printf("|| A0 | A1 | A2 | A3 | B0 | B1 | B2 | B3 | F  |\n");
	
	uint8_t vector_shift = 3;
	for (uint8_t i = 0b00000000; i < 0b11111111; i++) {
		uint8_t a0 = 0b1000000 & i >> 7;
		uint8_t b0 = 0b00001000 & i >> 3;
		uint8_t a1 = (0b01000000 & i) >> 6;
		uint8_t b1 = (0b00000100 & i) >> 2;
		uint8_t a2 = (0b00100000 & i) >> 5;
		uint8_t b2 = (0b00000010 & i) >> 1;
		uint8_t a3 = (0b00010000 & i) >> 4;
		uint8_t b3 = (0b00000001 & i);

		uint8_t output = four_bit_vector_comparator((0b11110000 & i >> 4), i);
		printf("|| %d  | %d  | %d  | %d  | %d  | %d  | %d  | %d  | %d  |\n", a0, a1, a2, a3, b0, b1, b2, b3, output);

	}
	printf("----------------------------------------------\n");
	return 0;
}

//Binary Print Helper Function
void print_binary(uint8_t number) {
	while (number) {
		if (number & 1)
			printf("1");
		else
			printf("0");

		number >>= 1;
	}
	printf("\n");
}



//Logic Gate Definitions
uint8_t logic_AND(uint8_t a, uint8_t b) {
	return 0b00000001 & (a & b);
}

uint8_t logic_OR(uint8_t a, uint8_t b) {
	return 0b00000001 & (a | b);
}

uint8_t logic_NAND(uint8_t a, uint8_t b) {
	return 0b00000001 & (~(a & b));
}

uint8_t logic_four_AND(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	return 0b00000001 & (a & b & c & d);
}

//Implementing 2 Bit Comparator Using Only Logic Gates -> Truth Table reduces to expression = (~A)B + A(~B) -> ~XOR
		//MUST IMPLEMENT WITH NAND, AND, OR -> CANNOT USE XOR
uint8_t two_bit_comparator(uint8_t a, uint8_t b) {
	uint8_t bit_a = 0b00000001 & a;
	uint8_t bit_b = 0b00000001 & b;
	uint8_t input_a = logic_AND(~bit_a, bit_b);
	uint8_t input_b = logic_AND(bit_a, ~bit_b);
	uint8_t output = logic_OR(input_a, input_b);
	return logic_NAND(output, output); // use NAND to obtain ~XOR
}


uint8_t four_bit_vector_comparator(uint8_t va, uint8_t vb) {
	
	//Get Single Bit Inputs from Vectors A and B
	uint8_t a0 = 0b00000001 & va;
	uint8_t b0 = 0b00000001 & vb;
	uint8_t a1 = (0b00000010 & va) >> 1;
	uint8_t b1 = (0b00000010 & vb) >> 1;
	uint8_t a2 = (0b00000100 & va) >> 2;
	uint8_t b2 = (0b00000100 & vb) >> 2;
	uint8_t a3 = (0b00001000 & va) >> 3;
	uint8_t b3 = (0b00001000 & vb) >> 3;

	//Compare corresponding bits using two bit comparator
	uint8_t n0 = two_bit_comparator(a0, b0);
	uint8_t n1 = two_bit_comparator(a1, b1);
	uint8_t n2 = two_bit_comparator(a2, b2);
	uint8_t n3 = two_bit_comparator(a3, b3);

	//Feed result into four input AND gate
	uint8_t result = logic_four_AND(n0, n1, n2, n3);
	return result;
}



