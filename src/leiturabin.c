#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTRADORES 100
#define MAX_OPCODE 100
#define MAX_MEMORIAS 100
#define MAX_INSTRA 100
#define MAX_INSTRB 100

typedef struct Instr {
	char opcode;
	char dst;
	char a;
	char b;

} instr_t;



int main() {
	
	int opcode[MAX_OPCODE];
	int registradores[MAX_REGISTRADORES];
	int memoria[MAX_MEMORIAS];
	int instrA[MAX_INSTRA];
	int instrB[MAX_INSTRB];
	
	memset(opcode, 0, sizeof(opcode));
	memset(registradores, 0, sizeof(registradores));
	memset(memoria, 0, sizeof(memoria));
	memset(instrA, 0, sizeof(instrA));
	memset(instrB, 0, sizeof(instrB));
	
	int resultado;
	int n, i;
	instr_t x;
	FILE *LeituraBin;
	
	
	LeituraBin = fopen("vetor.bin","rb");
		
	while(fread(&x, sizeof(instr_t), 1, LeituraBin)) {
	//	printf("%d", x);
		//printf("OPCODE: %d\tDST: %d\t INSTR A: %d\t INSTR B: %d\n", x.opcode, x.dst, x.a, x.b);
		
		switch(x.opcode)
		{
			case 0:
				add(&registradores[x.dst], x.a, x.b);
				break;
			case 1:
				addi(&registradores[x.dst], &registradores[x.a], x.b);
				break;
			case 2:
				sub(&registradores[x.dst], x.a, x.b);
				break;
			case 3:
				jlt(&registradores[x.dst], x.a, x.b);
				break;
			case 4:
				je(&registradores[x.dst], x.a, x.b);
				break;
			case 5:
				jmp(&registradores[x.dst]);
				break;
			case 6:
				ld(&registradores[x.dst], &memoria[x.a]);
				break;
			case 7:
				sd(&registradores[x.dst], &memoria[x.a]);
				break;
			case 8:
				hlt();
				break;
			case 9:
				prt(&registradores[x.dst], x.dst);
				break;
			default:
				break;
		}
		
		printf("REGISTRADORES:\n");
		
		for(i = 0; i < 10; i++) {
			printf("R%d = %d\n", i, registradores[i])	;
		}
	}
}

void add(int *registrador, int a, int b) {
	*registrador = *registrador + a + b;
}

void addi(int *registradorDst, int *registradorA, int b) {
	*registradorDst = *registradorDst + *registradorA + b;
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

void jmp(int *registrador) {
	*registrador = *registrador;
}

void ld(int *registrador, int *memoria) {
	*registrador = *memoria;
}

void sd(int *registrador, int *memoria) {
	*memoria = *registrador;
}

void hlt() {
	printf("Fim das instrucoes");
}

void prt(int *registrador, int dst) {
	printf("O valor do Registrador R%d: %d equivale ao caracter %c.", dst, *registrador, *registrador);
}
