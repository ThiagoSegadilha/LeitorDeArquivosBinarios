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
	int registradoresDst[MAX_REGISTRADORES];
	int instrA[MAX_INSTRA];
	int instrB[MAX_INSTRB];
	
	memset(opcode, 0, sizeof(opcode));
	memset(registradores, 0, sizeof(registradores));
	memset(memoria, 0, sizeof(memoria));
	memset(instrA, 0, sizeof(instrA));
	memset(instrB, 0, sizeof(instrB));
	
	int *apontador;
	int resultado;
	int n, i, a = 0;
	instr_t x;
	FILE *LeituraBin;
	
	
	
	LeituraBin = fopen("vetor.bin","rb");
		
	i = 0;
	while(fread(&x, sizeof(instr_t), 1, LeituraBin)) {
				
		opcode[i] = x.opcode;
		registradoresDst[i] = x.dst;
		instrA[i] = x.a;
		instrB[i] = x.b;
		
		
		i++;
	}
	
	for(n = 0; n < 10; n++) {
		apontador = &opcode[n];
		printf("Apontador: %d\t OpCode: %d\t Dst: %d\t InstrA: %d\t InstrB: %d\n", *apontador, opcode[n], registradoresDst[n], instrA[n], instrB[n]);
		
		
		switch(*apontador)
		{
			case 0:
				add(&registradores[x.dst], &registradores[x.a], &registradores[x.b]);
				break;
			case 1:
				addi(&registradores[registradoresDst[n]], &registradores[instrA[n]], instrB[n]);
				printf("R%d: %d\t R%d: %d\t Var: %d\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], registradores[instrA[n]], instrB[n]);
				break;
			case 2:
				sub(&registradores[registradoresDst[n]], &registradores[instrA[n]], &registradores[instrB[n]]);
				printf("R%d: %d\t R%d: %d\t R%d: %d\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], registradores[instrA[n]], instrB[n], registradores[instrB[n]]);
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
	}
}

void add(int *registrador, int *registradorA, int *registradorB) {
	*registrador = *registradorA + *registradorB;
}

void addi(int *registradorDst, int *registradorA, int b) {
	*registradorDst = *registradorA + b;
}

void sub(int *registrador, int *registradorA, int *registradorB) {
	*registrador = *registradorA - *registradorB;
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
	printf("Fim das instrucoes\n");
}

void prt(int *registrador, int dst) {
	printf("O valor do Registrador R%d: %d equivale ao caracter %c.\n", dst, *registrador, *registrador);
}
