#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTRADORES 100

#define MAX_MEMORIAS 100

typedef struct Instr {
	char opcode;
	char dst;
	char a;
	char b;

} instr_t;



int main() {
	
	int registradores[MAX_REGISTRADORES];
	int memoria[MAX_MEMORIAS];
	memset(registradores, 0, sizeof(registradores));
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
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 1:
				addi(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 2:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 3:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 4:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 5:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 6:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 7:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 8:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			case 9:
				sub(&registradores[x.dst], x.a, x.b);
				printf("Registrador R%d = %d\n", x.dst, registradores[x.dst]);
				break;
			default:
				break;
		}
	}
}

void add(int *registrador, int a, int b) {
	*registrador = *registrador + a + b;
}

void addi(int *registrador, int a, int b) {
	*registrador = *registrador + a + b;
}

void sub(int *registrador, int a, int b) {
	*registrador = *registrador + a - b;
}

void jlt(int *registrador, int a, int b) {
	if(a < b) {
		*registrador = *registrador;		
	}
}

void je(int *registrador, int a, int b) {
	if(a == b) {
		*registrador = *registrador;		
	}
}

void jmp(int *registrador, int a, int b) {
	*registrador = *registrador;
}

void ld(int *registrador, int *memoria) {
	*registrador = *memoria;
}

void sd(int *registrador, int *memoria) {
	*memoria = *registrador;
}

void hlt(int *registrador, int a, int b) {
	printf("Fim das instrucoes");
}

void prt(int *registrador, int a) {
	printf("O valor do Registrador R%d: equivale ao caracter %c.", a, a);
}
