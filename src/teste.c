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
	int n, j, i, aux, a = 0;
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
	
	n = 0;		
	while(1) {
		
		apontador = &opcode[n];
				
		printf("OpCode: %d\t Dst: %d\t InstrA: %d\t InstrB: %d\n",opcode[n], registradoresDst[n], instrA[n], instrB[n]);
		
		
		switch(*apontador)
		{
			case 0:
				printf("ADD R%d, R%d, R%d  (Soma o valor que tem no registrador R%d com o valor que tem no registrador R%d e armazena no registrador R%d).\n", registradoresDst[n], instrA[n], instrB[n], instrA[n], instrB[n], registradoresDst[n]);
				add(&registradores[registradoresDst[n]], &registradores[instrA[n]], &registradores[instrB[n]]);
				printf("R%d: %d\t R%d: %d\t R%d: %d\n\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], registradores[instrA[n]], instrB[n], registradores[instrB[n]]);
				n++;
				break;
			case 1:
				printf("ADDI R%d, R%d, %d  (Soma o valor que tem no registrador R%d com o valor imediato %d e armazena no registrador R%d).\n", registradoresDst[n], instrA[n], instrB[n], instrA[n], instrB[n], registradoresDst[n]);
				addi(&registradores[registradoresDst[n]], &registradores[instrA[n]], instrB[n]);
				printf("R%d: %d\t R%d: %d\t Var: %d\n\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], registradores[instrA[n]], instrB[n]);
				n++;
				break;
			case 2:
				printf("SUB R%d, R%d, R%d  (Subtrai o valor que tem no registrador R%d pelo valor que tem no registrador R%d e armazena no registrador R%d).\n", registradoresDst[n], instrA[n], instrB[n], instrA[n], instrB[n], registradoresDst[n]);
				sub(&registradores[registradoresDst[n]], &registradores[instrA[n]], &registradores[instrB[n]]);
				printf("R%d: %d\t R%d: %d\t R%d: %d\n\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], registradores[instrA[n]], instrB[n], registradores[instrB[n]]);
				n++;
				break;
			case 3:
				printf("JLT R%d, R%d, R%d  (Compara o valor que tem no registrador R%d com o valor que tem no registrador R%d, se R%d < R%d, retona para a instrucao equivalente ao valor do registrador R%d).\n", registradoresDst[n], instrA[n], instrB[n], instrA[n], instrB[n], instrA[n], instrB[n], registradoresDst[n]);
				aux = jlt(&registradores[registradoresDst[n]], &registradores[instrA[n]], &registradores[instrB[n]]);
				if(aux) {
					printf("Como o valor do registrador R%d = %d. Retorna para a instrucao da linha %d\n\n", registradoresDst[n], registradores[registradoresDst[n]], registradores[registradoresDst[n]]);
					n = aux;					
				} else {
					n++;
				}
				break;
			case 4:
				printf("JLT R%d, R%d, R%d  (Compara o valor que tem no registrador R%d com o valor que tem no registrador R%d, se R%d == R%d, retona para a instrucao equivalente ao valor do registrador R%d).\n", registradoresDst[n], instrA[n], instrB[n], instrA[n], instrB[n], instrA[n], instrB[n], registradoresDst[n]);
				aux = je(&registradores[registradoresDst[n]], &registradores[instrA[n]], &registradores[instrB[n]]);
				if(aux) {
					printf("Como o valor do registrador R%d = %d. Retorna para a instrucao da linha %d\n\n", registradoresDst[n], registradores[registradoresDst[n]], registradores[registradoresDst[n]]);
					n = aux;					
				} else {
					n++;
				}
				break;
			case 5:
				aux = jmp(&registradores[registradoresDst[n]]);
				n = aux;
				break;
			case 6:
				ld(&registradores[registradoresDst[n]], &memoria[instrA[n]]);
				n++;
				break;
			case 7:
				sd(&registradores[registradoresDst[n]], &memoria[instrA[n]]);
				printf("R%d: %d\tM%d: %d\n", registradoresDst[n], registradores[registradoresDst[n]], instrA[n], memoria[instrA[n]]);
				n++;
				break;
			case 8:
				hlt();
				break;
			case 9:
				prt(&registradores[registradoresDst[n]]);
				break;
			default:
				break;
		}
		
		if(*apontador == 8) {
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

int jlt(int *registrador, int *registradorA, int *registradorB) {
	if(*registradorA < *registradorB) {
		return *registrador;
	} else {
		return NULL;
	}
}

int je(int *registrador, int a, int b) {
	if(a == b) {
		return *registrador;		
	} else {
		return NULL;
	}
}

void jmp(int *registrador) {
	return *registrador;
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
