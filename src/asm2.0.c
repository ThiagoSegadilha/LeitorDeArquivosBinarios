#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 100

#define N_OPCODES 100

/* Conjunto de instrucoes do trabalho:
 * add <reg destino>,<reg a> <reg b> (exemplo: add r1,r2,r3)
 * addi <reg destino>,<reg a>,<immediato> (exemplo: addi r1,r2,123);
 * sub -- semelhante a addl
 * jlt <reg endereco alvo>,<reg a>,<reg b> (desvio condicional para endereco alvo caso valor de reg a seja menor que o de reg b>. Se a<b retorna o registrador alvo
 * je -- mesmo que jlt, mas no caso dos valores serem iguais
 * jmp <reg destino> (desvio incondicional). retorna o valor do registrador alvo
 * ld <reg destino>,<reg endereco> (carrega o valor contino no endereco de memoria para o registrador de destino). Pega o valor do endereço de memoria Ex: 1001, 1002... e joga no registrador destino
 * sd <reg valor>,<reg endereco> (escreve o valor presente em reg valor no endereco de memoria dado por reg endereco).
 * hlt (halt, termina o programa). finaliza as instruções
 * prt <reg valor> (imprime na tela o caracter cujo valor esta em reg valor).
 *
 *
 * Todos os registradores tem 8 bits e as instruções possuem 32 bits, como visto na struct abaixo. Considere que ha infinitos registradores, para simplificar, e memoria infinita.
 *
 * Formato das instrucoes: opcode | reg destino | reg a | reg b
 * Sendo que reg b pode conter um registrador ou um operando imediato (constate)
 */

typedef struct instr {
	char opcode;
	char dst;
	char a;
	char b;
	
} instr_t;

char find_opcode(char opcode[]) {
	char isa[N_OPCODES][10] = {"add", "addi", "sub", "jlt", "je", "jmp", "ld", "sd", "hlt", "prt"};
	int i;
	char found = 0;

	for (i = 0; i < N_OPCODES && !found; i++) {
		if (strcmp(isa[i], opcode) == 0) {
			printf("Opcode number %d\n", i);
			found = 1;
		}
		
	}
	return(i-1);	
}

void write_instr(instr_t instr, FILE *binary) {
	char zero = 0;

	fwrite(&instr.opcode, sizeof(char), 1, binary);
	fwrite(&instr.dst, sizeof(char), 1, binary);
	if (instr.a == NULL)
		instr.a = zero;
	if (instr.b == NULL)
		instr.b = zero;
		
	fwrite(&instr.a, sizeof(char), 1, binary);
	fwrite(&instr.b, sizeof(char), 1, binary);
	
	
	printf("opcode %d dst %d a %d b %d\n", instr.opcode, instr.dst, instr.a, instr.b); 
}

void remove_spaces(char line[]) {
	int len, i=0;

	while (*line != ' ') line++;
	line++;
	len = strlen(line);
	for (i = 0; i < len; i++) {
		if (line[i] == ' ') 
			memmove(line + i, line + i + 1, len - i);	
	}
}

void assemble(char line[], FILE *binary) {
	char *token[4] = {0,0,0,0}, op[10], dst[10], last, *tkptr;
	instr_t instr = {0,0,0,0};
	int i = 1;

	remove_spaces(line);
	printf("Line: %s", line);	
	
	token[0] = strtok(line, ",");
	
	sscanf(token[0], "%s %s", op, dst);
	//printf("op %s dst %s\n", op,dst);
	token[i] = strtok(NULL, ",");
	while (token[i] != NULL) {
		tkptr = token[i];
		last = tkptr[strlen(tkptr)];
		tkptr[strlen(tkptr)] = last == '\n' ? '\0' : last;
		
		token[++i] = strtok(NULL, ",");
	}
	instr.opcode = find_opcode(op);
	instr.dst = (char) atoi(dst+1);

	
	if (token[1] != NULL)
		instr.a = (char) atoi(token[1] + 1);
	else
		instr.a = NULL;
	if (token[2] != NULL)
		instr.b = (char)atoi(token[2] + (token[2][0] == 'r'));

	else
		instr.b = NULL;
	
	//printf("Instr: %d %d %d %d\n", instr.opcode, instr.dst, instr.a, instr.b);
	write_instr(instr, binary); 
	
	//printf("a %d\n", instr.dst);
}

int main(int argc, char *argv[]) {
	char line[MAX_LINE];
	FILE *fp = fopen(argv[1], "r");
	FILE *binary = fopen(argv[2], "wb");
	
	fgets(line, MAX_LINE, fp);
	while (!feof(fp)) {
			
		assemble(line, binary);
	
		fgets(line, MAX_LINE, fp);
		printf("Write\n");	
	}
	
	return(0);
}
