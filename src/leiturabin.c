#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTRADORES 100

typedef struct Instr {
	char opcode;
	char dst;
	char a;
	char b;

} instr_t;



int main() {
	
	int registradores[MAX_REGISTRADORES];
	//int register1, register2, register3, register4, register5, register6, register7, register8, register9, register10 = 0;
	//register1 = register2 = register3 = register4 = register5 = register6 = register7 = register8 = register9 = register10 = 0;
	int resultado;
	int n;
	instr_t x;
	FILE *LeituraBin;
	
	
	LeituraBin = fopen("soma.bin","rb");
		
	while(fread(&x, sizeof(instr_t), 1, LeituraBin)) {
	//	printf("%d", x);
		//printf("OPCODE: %d\tDST: %d\t INSTR A: %d\t INSTR B: %d\n", x.opcode, x.dst, x.a, x.b);
		
		switch(x.opcode)
		{
			case 0:
				add(&registradores[x.dst], x.a, x.b);
			case 1:
				addi(&registradores[x.dst], x.a, x.b);
			case 2:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Resultado: %d, %d\n", resultado, registradores[x.dst]);
			case 3:
				sub(&registradores[x.dst], x.a, x.b);
			case 4:
				sub(&registradores[x.dst], x.a, x.b);
			case 5:
				sub(&registradores[x.dst], x.a, x.b);
			case 6:
				sub(&registradores[x.dst], x.a, x.b);
			case 7:
				sub(&registradores[x.dst], x.a, x.b);
			case 8:
				sub(&registradores[x.dst], x.a, x.b);
			case 9:
				sub(&registradores[x.dst], x.a, x.b);
			default:
				break;
		}
	}
}

void add(int *registrador, int a, int b) {
	*registrador = a + b;
}

void addi(int *registrador, int a, int b) {
	*registrador = a + b;
}

void sub(int *registrador, int a, int b) {
	*registrador = a - b;
}

void jlt(int *registrador, int a, int b) {
	*registrador = a - b;
}

void je(int *registrador, int a, int b) {
	*registrador = a - b;
}

void jmp(int *registrador, int a, int b) {
	*registrador = a - b;
}

void ld(int *registrador, int a, int b) {
	*registrador = a - b;
}

void sd(int *registrador, int a, int b) {
	*registrador = a - b;
}

void hlt(int *registrador, int a, int b) {
	*registrador = a - b;
}

void prt(int *registrador, int a, int b) {
	*registrador = a - b;
}
