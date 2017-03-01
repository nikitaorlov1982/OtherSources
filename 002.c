#include <stdio.h>
#include <stdlib.h>

typedef struct _entry {
	char *str;
	int bytes;
	int operands;
} entry;

entry table[] = {

	/*	BEGIN OF TABLE!!!	*/

	{ "nop",		1, 0 },		/*	0x00	*/
	{ "ajmp\t%d",		2, 1 },		/*	0x01	*/
	{ "ljmp\t%d", 		3, 1 },		/*	0x02	*/
	{ "rr\tA",		1, 0 },		/*	0x03	*/
	{ "inc\tA",		1, 0 },		/*	0x04	*/
	{ "inc\t%d",		2, 1 },		/*	0x05	*/
	{ "inc\t@R0",		1, 0 },		/*	0x06	*/
	{ "inc\t@R1",		1, 0 },		/*	0x07	*/
	{ "inc\tR0",		1, 0 },		/*	0x08	*/
	{ "inc\tR1",		1, 0 },		/*	0x09	*/
	{ "inc\tR2",		1, 0 },		/*	0x0a	*/
	{ "inc\tR3",		1, 0 },		/*	0x0b	*/
	{ "inc\tR4",		1, 0 },		/*	0x0c	*/
	{ "inc\tR5",		1, 0 },		/*	0x0d	*/
	{ "inc\tR6",		1, 0 },		/*	0x0e	*/
	{ "inc\tR7",		1, 0 },		/*	0x0f	*/
	
	{ "jbc\t%d, %d",	3, 2 },		/*	0x10	*/	
	{ "acall\t%d",		2, 1 },		/*	0x11	*/
	{ "lcall\t%d",		3, 1 },		/*	0x12	*/
	{ "rrc\tA",		1, 0 },		/*	0x13	*/
	{ "dec\tA",		1, 0 },		/*	0x14	*/
	{ "dec\t%d",		2, 1 },		/*	0x15	*/
	{ "dec\t@R0",		1, 0 },		/*	0x16	*/
	{ "dec\t@R1",		1, 0 },		/*	0x17	*/
	{ "dec\tR0",		1, 0 },		/*	0x18	*/
	{ "dec\tR1",		1, 0 },		/*	0x19	*/
	{ "dec\tR2",		1, 0 },		/*	0x1a	*/
	{ "dec\tR3",		1, 0 },		/*	0x1b	*/
	{ "dec\tR4", 		1, 0 },		/*	0x1c	*/
	{ "dec\tR5", 		1, 0 },		/*	0x1d	*/
	{ "dec\tR6", 		1, 0 },		/*	0x1e	*/
	{ "dec\tR7", 		1, 0 },		/*	0x1f	*/
	
	{ "jb\t%d, %d",		3, 2 },		/*	0x20	*/	
	{ "ajmp\t%d",		2, 1 },		/*	0x21	*/
	{ "ret",		1, 0 }, 	/*	0x22	*/
	{ "rl\tA",		1, 0 },		/*	0x23	*/
	{ "add\tA, #%d",	2, 1 },		/*	0x24	*/
	{ "add\tA, %d",		2, 1 },		/*	0x25	*/
	{ "add\tA, @R0",	1, 0 },		/*	0x26	*/
	{ "add\tA, @R1",	1, 0 },		/*	0x27	*/
	{ "add\tA, R0",		1, 0 },		/*	0x28	*/
	{ "add\tA, R1",		1, 0 },		/*	0x29	*/
	{ "add\tA, R2",		1, 0 },		/*	0x2a	*/
	{ "add\tA, R3",		1, 0 },		/*	0x2b	*/
	{ "add\tA, R4",		1, 0 },		/*	0x2c	*/
	{ "add\tA, R5",		1, 0 },		/*	0x2d	*/
	{ "add\tA, R6",		1, 0 },		/*	0x2e	*/
	{ "add\tA, R7",		1, 0 },		/*	0x2f	*/
	
	{ "jnb\t%d, %d",	3, 2 },		/*	0x30	*/	
	{ "acall\t%d",		2, 1 },		/*	0x31	*/
	{ "reti",		1, 0 },		/*	0x32	*/
	{ "rlc\tA",		1, 0 },		/*	0x33	*/
	{ "addc\tA, #%d",	2, 1 },		/*	0x34	*/
	{ "addc\tA,%d",		2, 1 },		/*	0x35	*/
	{ "addc\tA, @R0",	1, 0 },		/*	0x36	*/
	{ "addc\tA, @R1",	1, 0 },		/*	0x37	*/
	{ "addc\tA, R0",	1, 0 },		/*	0x38	*/
	{ "addc\tA, R1",	1, 0 },		/*	0x39	*/
	{ "addc\tA, R2",	1, 0 },		/*	0x3a	*/
	{ "addc\tA, R3",	1, 0 },		/*	0x3b	*/
	{ "addc\tA, R4",	1, 0 },		/*	0x3c	*/
	{ "addc\tA, R5",	1, 0 },		/*	0x3d	*/
	{ "addc\tA, R6",	1, 0 },		/*	0x3e	*/
	{ "addc\tA, R7",	1, 0 },		/*	0x3f	*/
	
	{ "jc\t%d",		2, 1 },		/*	0x40	*/
	{ "ajmp\t%d",		2, 1 }, 	/*	0x41	*/
	{ "orl\t%d, A",		2, 2 },		/*	0x42	*/
	{ "orl\t%d, #%d",	3, 2 },		/*	0x43	*/
	{ "orl\tA, #%d",	2, 1 },		/*	0x44	*/
	{ "orl\tA, %d",		2, 1 },		/*	0x45	*/
	{ "orl\tA, @R0",	1, 0 },		/*	0x46	*/
	{ "orl\tA, @R1",	1, 0 }, 	/*	0x47	*/
	{ "orl\tA, R0",		1, 0 },		/*	0x48	*/
	{ "orl\tA, R1",		1, 0 },		/*	0x49	*/
	{ "orl\tA, R2",		1, 0 },		/*	0x4a	*/
	{ "orl\tA, R3",		1, 0 },		/*	0x4b	*/
	{ "orl\tA, R4",		1, 0 },		/*	0x4c	*/
	{ "orl\tA, R5",		1, 0 },		/*	0x4d	*/
	{ "orl\tA, R6",		1, 0 },		/*	0x4e	*/
	{ "orl\tA, R7",		1, 0 },		/*	0x4f	*/
	
	{ "jnc\t%d",		2, 1 },		/*	0x50	*/
	{ "acall\t%d",		2, 1 },		/*	0x51	*/
	{ "anl\t%d, A",		2, 1 },		/*	0x52	*/
	{ "anl\t%d, #%d",	3, 2 },		/*	0x53	*/
	{ "anl\tA, #%d",	2, 1 },		/*	0x54	*/
	{ "anl\tA, %d",		2, 1 },		/*	0x55	*/
	{ "anl\tA, @R0",	1, 0 },		/*	0x56	*/
	{ "anl\tA, @R1",	1, 0 },		/*	0x57	*/
	{ "anl\tA, R0",		1, 0 },		/*	0x58	*/
	{ "anl\tA, R1",		1, 0 },		/*	0x59	*/
	{ "anl\tA, R2",		1, 0 },		/*	0x5a	*/
	{ "anl\tA, R3",		1, 0 },		/*	0x5b	*/
	{ "anl\tA, R4",		1, 0 },		/*	0x5c	*/
	{ "anl\tA, R5",		1, 0 },		/*	0x5d	*/
	{ "anl\tA, R6",		1, 0 },		/*	0x5e	*/
	{ "anl\tA, R7",		1, 0 },		/*	0x5f	*/
	
	{ "jz\t%d",		2, 1 },		/*	0x60	*/
	{ "ajmp\t%d",		2, 1 },		/*	0x61	*/
	{ "xrl\t%d, A",		2, 1 },		/*	0x62	*/
	{ "xrl\t%d, #%d",	3, 2 },		/*	0x63	*/
	{ "xrl\tA, #%d",	2, 1 },		/*	0x64	*/
	{ "xrl\tA, %d",		2, 1 },		/*	0x65	*/
	{ "xrl\tA, @R0",	1, 0 },		/*	0x66	*/
	{ "xrl\tA, @R1",	1, 0 },		/*	0x67	*/
	{ "xrl\tA, R0",		1, 0 },		/*	0x68	*/
	{ "xrl\tA, R1",		1, 0 },		/*	0x69	*/
	{ "xrl\tA, R2",		1, 0 },		/*	0x6a	*/
	{ "xrl\tA, R3",		1, 0 },		/*	0x6b	*/
	{ "xrl\tA, R4",		1, 0 },		/*	0x6c	*/
	{ "xrl\tA, R5",		1, 0 },		/*	0x6d	*/
	{ "xrl\tA, R6",		1, 0 },		/*	0x6e	*/
	{ "xrl\tA, R7",		1, 0 },		/*	0x6f	*/
	
	{ "jnz\t%d",		2, 1 },		/*	0x70	*/
	{ "acall\t%d",		2, 1 },		/*	0x71	*/
	{ "orl\tC, %d",		2, 1 },		/*	0x72	*/
	{ "jmp\t@A + DPTR",	1, 0 },		/*	0x73	*/
	{ "mov\tA, #%d",	2, 1 },		/*	0x74	*/
	{ "mov\t%d, #%d",	3, 2 },		/*	0x75	*/
	{ "mov\t@R0, #%d",	2, 1 },		/*	0x76	*/
	{ "mov\t@R1, #%d",	2, 1 },		/*	0x77	*/
	{ "mov\tR0, #%d",	2, 1 },		/*	0x78	*/
	{ "mov\tR1, #%d",	2, 1 },		/*	0x79	*/
	{ "mov\tR2, #%d",	2, 1 },		/*	0x7a	*/
	{ "mov\tR3, #%d",	2, 1 },		/*	0x7b	*/
	{ "mov\tR4, #%d",	2, 1 },		/*	0x7c	*/
	{ "mov\tR5, #%d",	2, 1 },		/*	0x7d	*/
	{ "mov\tR6, #%d",	2, 1 },		/*	0x7e	*/
	{ "mov\tR7, #%d",	2, 1 },		/*	0x7f	*/
	
	{ "sjmp\t%d",		2, 1 },		/*	0x80	*/
	{ "ajmp\t%d",		2, 1 },		/*	0x81	*/
	{ "anl\tC, %d",		2, 1 },		/*	0x82	*/
	{ "movc\tA, @A + PC",	1, 0 },		/*	0x83	*/
	{ "div\tAB",		1, 0 },		/*	0x84	*/
	{ "mov\t%d, %d",	3, 2 },		/*	0x85	*/
	{ "mov\t%d, @R0",	2, 1 },		/*	0x86	*/
	{ "mov\t%d, @R1",	2, 1 },		/*	0x87	*/
	{ "mov\t%d, R0",	2, 1 },		/*	0x88	*/
	{ "mov\t%d, R1",	2, 1 },		/*	0x89	*/
	{ "mov\t%d, R2",	2, 1 },		/*	0x8a	*/
	{ "mov\t%d, R3",	2, 1 },		/*	0x8b	*/
	{ "mov\t%d, R4",	2, 1 },		/*	0x8c	*/
	{ "mov\t%d, R5",	2, 1 },		/*	0x8d	*/
	{ "mov\t%d, R6",	2, 1 },		/*	0x8e	*/
	{ "mov\t%d, R7",	2, 1 },		/*	0x8f	*/
	
	{ "mov\tDPTR, #%d",	3, 1 },		/*	0x90	*/
	{ "acall\t%d",		2, 1 },		/*	0x91	*/
	{ "mov\t%d, C",		2, 1 },		/*	0x92	*/
	{ "movc\tA, @A + DPTR", 1, 0 },		/*	0x93	*/
	{ "subb\tA, #%d",	2, 1 },		/*	0x94	*/
	{ "subb\tA, %d",	2, 1 },		/*	0x95	*/
	{ "subb\tA, @R0",	1, 0 },		/*	0x96	*/
	{ "subb\tA, @R1",	1, 0 },		/*	0x97	*/
	{ "subb\tA, R0",	1, 0 },		/*	0x98	*/
	{ "subb\tA, R1",	1, 0 },		/*	0x99	*/
	{ "subb\tA, R2",	1, 0 },		/*	0x9a	*/
	{ "subb\tA, R3",	1, 0 },		/*	0x9b	*/
	{ "subb\tA, R4",	1, 0 },		/*	0x9c	*/
	{ "subb\tA, R5",	1, 0 },		/*	0x9d	*/
	{ "subb\tA, R6",	1, 0 },		/*	0x9e	*/
	{ "subb\tA, R7",	1, 0 },		/*	0x9f	*/
	
	{ "orl\tC, %d",		2, 1 },		/*	0xa0	*/
	{ "ajmp\t%d",		2, 1 },		/*	0xa1	*/
	{ "mov\tC, %d",		2, 1 },		/*	0xa2	*/
	{ "inc\tDPTR",		1, 0 },		/*	0xa3	*/
	{ "mul\tAB",		1, 0 },		/*	0xa4	*/
	{ "; opcode 0xa5 is reserved!!!", 1, 0 }, /*	0xa5	*/
	{ "mov\t@R0, %d",	2, 1 },		/*	0xa6	*/
	{ "mov\t@R1, %d",	2, 1 },		/*	0xa7	*/
	{ "mov\tR0, %d",	2, 1 },		/*	0xa8	*/
	{ "mov\tR1, %d",	2, 1 },		/*	0xa9	*/
	{ "mov\tR2, %d",	2, 1 },		/*	0xaa	*/
	{ "mov\tR3, %d",	2, 1 },		/*	0xab	*/
	{ "mov\tR4, %d",	2, 1 },		/*	0xac	*/
	{ "mov\tR5, %d",	2, 1 },		/*	0xad	*/
	{ "mov\tR6, %d",	2, 1 },		/*	0xae	*/
	{ "mov\tR7, %d",	2, 1 },		/*	0xaf	*/
	
	{ "anl\tC, %d",		2, 1 },		/*	0xb0	*/
	{ "acall\t%d",		2, 1 },		/*	0xb1	*/
	{ "cpl\t%d",		2, 1 },		/*	0xb2	*/
	{ "cpl\tC",		1, 0 },		/*	0xb3	*/
	{ "cjne\tA, #%d, %d",	3, 2 },		/*	0xb4	*/
	{ "cjne\tA, %d, %d",	3, 2 },		/*	0xb5	*/
	{ "cjne\t@R0, #%d, %d",	3, 2 },		/*	0xb6	*/
	{ "cjne\t@R1, #%d, %d", 3, 2 },		/*	0xb7	*/
	{ "cjne\tR0, #%d, %d", 	3, 2 },		/*	0xb8	*/
	{ "cjne\tR1, #%d, %d", 	3, 2 },		/*	0xb9	*/
	{ "cjne\tR2, #%d, %d", 	3, 2 },		/*	0xba	*/
	{ "cjne\tR3, #%d, %d", 	3, 2 },		/*	0xbb	*/
	{ "cjne\tR4, #%d, %d", 	3, 2 },		/*	0xbc	*/
	{ "cjne\tR5, #%d, %d", 	3, 2 },		/*	0xbd	*/
	{ "cjne\tR6, #%d, %d", 	3, 2 },		/*	0xbe	*/
	{ "cjne\tR7, #%d, %d", 	3, 2 },		/*	0xbf	*/
	
	{ "push\t%d",		2, 1 },		/*	0xc0	*/
	{ "ajmp\t%d",		2, 1 }, 	/*	0xc1	*/
	{ "clr\t%d",		2, 1 },		/*	0xc2	*/
	{ "clr\tC",		1, 0 },		/*	0xc3	*/
	{ "swap\tA",		1, 0 },		/*	0xc4	*/
	{ "xch\tA, %d",		2, 1 },		/*	0xc5	*/
	{ "xch\tA, @R0",	1, 0 },		/*	0xc6	*/
	{ "xch\tA, @R1",	1, 0 },		/*	0xc7	*/
	{ "xch\tA, R0",		1, 0 },		/*	0xc8	*/
	{ "xch\tA, R1",		1, 0 },		/*	0xc9	*/
	{ "xch\tA, R2",		1, 0 },		/*	0xca	*/
	{ "xch\tA, R3",		1, 0 },		/*	0xcb	*/
	{ "xch\tA, R4",		1, 0 },		/*	0xcc	*/
	{ "xch\tA, R5",		1, 0 },		/*	0xcd	*/
	{ "xch\tA, R6",		1, 0 },		/*	0xce	*/
	{ "xch\tA, R7",		1, 0 },		/*	0xcf	*/
	
	{ "pop\t%d",		2, 1 },		/*	0xd0	*/
	{ "acall\t%d",		2, 1 },		/*	0xd1	*/
	{ "setb\t%d",		2, 1 },		/*	0xd2	*/
	{ "setb\tC",		1, 0 },		/*	0xd3	*/
	{ "da\tA",		1, 0 },		/*	0xd4	*/
	{ "djnz\t%d, %d",	3, 2 },		/*	0xd5	*/
	{ "xchd\tA, @R0",	1, 0 },		/*	0xd6	*/
	{ "xchd\tA, @R1",	1, 0 },		/*	0xd7	*/
	{ "djnz\tR0, %d",	2, 1 },		/*	0xd8	*/
	{ "djnz\tR1, %d",	2, 1 },		/*	0xd9	*/
	{ "djnz\tR2, %d",	2, 1 },		/*	0xda	*/
	{ "djnz\tR3, %d",	2, 1 },		/*	0xdb	*/
	{ "djnz\tR4, %d",	2, 1 },		/*	0xdc	*/
	{ "djnz\tR5, %d",	2, 1 },		/*	0xdd	*/
	{ "djnz\tR6, %d",	2, 1 },		/*	0xde	*/
	{ "djnz\tR7, %d",	2, 1 },		/*	0xdf	*/
	
	{ "movx\tA, @DPTR",	1, 0 },		/*	0xe0	*/
	{ "ajmp\t%d",		2, 1 },		/*	0xe1	*/
	{ "movx\tA, @R0",	1, 0 },		/*	0xe2	*/
	{ "movx\tA, @R1", 	1, 0 }, 	/*	0xe3	*/
	{ "clr\tA",		1, 0 },		/*	0xe4	*/
	{ "mov\tA, %d",		2, 1 },		/*	0xe5	*/
	{ "mov\tA, @R0",	1, 0 },		/*	0xe6	*/
	{ "mov\tA, @R1",	1, 0 },		/*	0xe7	*/
	{ "mov\tA, R0",		1, 0 },		/*	0xe8	*/
	{ "mov\tA, R1",		1, 0 },		/*	0xe9	*/
	{ "mov\tA, R2",		1, 0 },		/*	0xea	*/
	{ "mov\tA, R3",		1, 0 },		/*	0xeb	*/
	{ "mov\tA, R4",		1, 0 },		/*	0xec	*/
	{ "mov\tA, R5",		1, 0 },		/*	0xed	*/
	{ "mov\tA, R6",		1, 0 },		/*	0xee	*/
	{ "mov\tA, R7",		1, 0 },		/*	0xef	*/
	
	{ "movx\t@DPTR, A",	1, 0 },		/*	0xf0	*/
	{ "acall\t%d",		2, 1 },		/*	0xf1	*/
	{ "movx\t@R0, A",	1, 0 },		/*	0xf2	*/
	{ "movx\t@R1, A",	1, 0 }, 	/*	0xf3	*/
	{ "cpl\tA",		1, 0 },		/*	0xf4	*/
	{ "mov\t%d, A",		2, 1 },		/*	0xf5	*/
	{ "mov\t@R0, A",	1, 0 },		/*	0xf6	*/
	{ "mov\t@R1, A",	1, 0 },		/*	0xf7	*/
	{ "mov\tR0, A",		1, 0 },		/*	0xf8	*/
	{ "mov\tR1, A",		1, 0 },		/*	0xf9	*/
	{ "mov\tR2, A",		1, 0 },		/*	0xfa	*/
	{ "mov\tR3, A",		1, 0 },		/*	0xfb	*/
	{ "mov\tR4, A",		1, 0 },		/*	0xfc	*/
	{ "mov\tR5, A",		1, 0 },		/*	0xfd	*/
	{ "mov\tR6, A",		1, 0 },		/*	0xfe	*/
	{ "mov\tR7, A",		1, 0 },		/*	0xff	*/
	
	/*	END OF TABLE!!!		*/
};
	



void usage() {
	printf("Usage: prog <file.bin>\n");
}

int main(int argc, char ** argv) {
	FILE * fp;
	long size;
	int opc, op1, op2, addr, paddr;
	
	if(argc != 2) {
		usage();
		exit(-1);
	}
		
	fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("Can't open file %s!\n", argv[1]);
		exit(-1);
	}
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	addr = 0;
	paddr = addr;
	while((opc = getc(fp)) != EOF) {
		//printf("Read %x opcode.", opc);
		switch(table[opc].bytes) {
		case 1:
			addr += 1;
			break;
		case 2:
			addr += 2;
			op1 = getc(fp);
			break;
		case 3:
			addr += 3;
			op1 = getc(fp);
			op2 = getc(fp);
			break;
		}
		
		printf("%04d:\t", paddr);
		paddr = addr;
		
		switch(table[opc].operands) {
		case 0:
			printf("%s\n", table[opc].str);
			break;
		case 1:
			if(table[opc].bytes == 3)
				printf(table[opc].str, (op1 << 8) | (op2));
			else
				printf(table[opc].str, op1);
			printf("\n");
			break;
		case 2:
			printf(table[opc].str, op1, op2);
			printf("\n");
			break;
		default:
			printf("; -- Error condition");
			break;
		}
			
			
	}
		
	
	fclose(fp);
	exit(0);
}


