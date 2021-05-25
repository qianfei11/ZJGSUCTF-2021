#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

char banner[] = "\033[7;35m"
"############################################################\n"
"##                                                        ##\n"
"##   █████╗ ███╗   ██╗████████╗██╗      ███████╗███████╗  ##\n"
"##  ██╔══██╗████╗  ██║╚══██╔══╝██║      ██╔════╝██╔════╝  ##\n"
"##  ███████║██╔██╗ ██║   ██║   ██║█████╗█████╗  ███████╗  ##\n"
"##  ██╔══██║██║╚██╗██║   ██║   ██║╚════╝██╔══╝  ╚════██║  ##\n"
"##  ██║  ██║██║ ╚████║   ██║   ██║      ██║     ███████║  ##\n"
"##  ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝      ╚═╝     ╚══════╝  ##\n"
"##                                                        ##\n"
"##                Shout out to WangXiaoJun                ##\n"
"##                                                        ##\n"
"############################################################\n"
"\033[0m";
char buf[1024*4]={0,};
//old:zjgsctf{Da_si_geD4Zhuan9_&_Es3}
//char *f1a9 = "mpulezy{Uq_lo_utU2Zixqf0_&_Yl1}";

//new:zjgsuctf{fUck!!_b3ale_1s_st1ll_w0rk1ng!!}
//char *f1a9 = "zjgsuctf{fUck!!_b3ale_1s_st1ll_w0rk1ng!!}";
char f1a9[] = {0xff, 0x21, 0xc2, 0xe7, 0x1c, 0x44, 0x69, 0x28, 0x26, 0xd6, 0x78, 0xfb, 0xbb, 0x41, 0xd0, 0xe9, 0xd0, 0xd5, 0x2e, 0x5b, 0x5a, 0x19, 0x43, 0x30, 0x39, 0x28, 0xae, 0xf, 0x2a, 0xb6, 0xe0, 0x93, 0x9b, 0x82, 0x12, 0x21, 0xcd, 0xe, 0xe, 0x47, 0xb0};

void encode() {
	unsigned int i = 0;
	unsigned int len = strlen(buf);
	char atable[] = "qwertyuiopasdfghjklzxcvbnm";
	char Atable[] = "POIUYTREWQLKJHGFDSAMNBVCXZ";
	char Dtable[] = "9631287450";
	for(;i<len;i++){
		if(islower(buf[i]))
			buf[i] = atable[buf[i]-'a'];
		else if(isupper(buf[i]))
			buf[i] = Atable[buf[i]-'A'];
		else if(isdigit(buf[i]))
			buf[i] = Dtable[buf[i]-'0'];
	}
}

#define MAX_LEN 256

unsigned char sb[MAX_LEN];
char *key = "zjgsuctf";

void init() {
	int i = 0, j = 0;
	char t[MAX_LEN];
	int len = strlen(key);

	__asm__ __volatile__(
		"push eax\n\t"
		"xor eax, eax\n\t"
		"jz qff_init\n\t"
		"add esp, 8\n\t"
		"qff_init:\n\t"
		"pop eax"
		: /* (none) */
		: /* (none) */
		: "eax", "esp");

	for (i = 0; i < MAX_LEN; i++) {
		sb[i] = i;
		t[i] = key[i % len];
	}

	for (i = 0; i < MAX_LEN; i++) {
        int x = j + sb[i] + t[i];
		j = x - (x >> 8 << 8);
		unsigned char tmp = sb[i];
		sb[i] = sb[j];
		sb[j] = tmp;
	}

	//for (i = 0; i < MAX_LEN; i++) {
	//	printf("0x%x, ", sb[i]);
	//}
	//printf("\n");
}

void enc0d3() {
	int i = 0, j = 0;
	int k = 0, len = strlen(buf);
	//printf("len => %d\n", len);

	__asm__ __volatile__(
		"push eax\n\t"
		"xor eax, eax\n\t"
		"jz qff_enc0d3\n\t"
		"add esp, 8\n\t"
		"qff_enc0d3:\n\t"
		"pop eax"
		: /* (none) */
		: /* (none) */
		: "eax", "esp");


	for (k = 0; k < len; k++) {
		i = (i + 1) - ((i + 1) >> 8 << 8);
		j = (j + sb[i]) - ((j + sb[i]) >> 8 << 8);
		unsigned char tmp = sb[i];
		sb[i] = sb[j];
		sb[j] = tmp;
		int t = (sb[i] + sb[j]) % MAX_LEN;
		buf[k] ^= sb[t];
		//printf("0x%x, ", buf[k]);
	}
	//printf("\n");
}

int check() {
	int i = 0;
	int len = strlen(f1a9);
	int result = 1;

	for (i = 0; i < len; i++) {
		if (0xff & buf[i] == f1a9[i]) {
			continue;
		} else {
			result = 0;
			break;
		}
	}

	return result;
}

int main() {
	puts(banner);
	puts("现在你可以输入flag，我会告诉你对不对：");
	//scanf("%s", buf);
    read(0, buf, 4000);
	//判断长度
	if(strlen(buf)>4000)
		exit(-1);
	//变换输入
	//encode();
	init();
	enc0d3();
	if (check())
		puts("厉害厉害，佩服佩服！");
	else
		puts("stupid!");
	exit(0);
}

