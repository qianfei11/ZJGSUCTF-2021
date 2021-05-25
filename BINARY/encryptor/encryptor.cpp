#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>  
#include <unistd.h>

char banner[0x400] = "\033[7;35m"
"+---------------------------------------------------+\n"
"|                                                   |\n"
"|  ▄▄▄ . ▐ ▄  ▄▄· ▄▄▄   ▄· ▄▌ ▄▄▄·▄▄▄▄▄      ▄▄▄    |\n"
"|  ▀▄.▀·•█▌▐█▐█ ▌▪▀▄ █·▐█▪██▌▐█ ▄█•██  ▪     ▀▄ █·  |\n"
"|  ▐▀▀▪▄▐█▐▐▌██ ▄▄▐▀▀▄ ▐█▌▐█▪ ██▀· ▐█.▪ ▄█▀▄ ▐▀▀▄   |\n"
"|  ▐█▄▄▌██▐█▌▐███▌▐█•█▌ ▐█▀·.▐█▪·• ▐█▌·▐█▌.▐▌▐█•█▌  |\n"
"|   ▀▀▀ ▀▀ █▪·▀▀▀ .▀  ▀  ▀ • .▀    ▀▀▀  ▀█▄▀▪.▀  ▀  |\n"
"|                                                   |\n"
"|   Copyright © 2021, B3ale, All rights reserved.   |\n"
"|                                                   |\n"
"+---------------------------------------------------+\n"
"\033[0m";
  
void encrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */  
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */  
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */  
    for (i=0; i < 32; i++) {                       /* basic cycle start */  
        sum += delta;  
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);  
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    }                                              /* end cycle */  
    v[0]=v0; v[1]=v1;  
}  

void decrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */  
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */  
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */  
    for (i=0; i<32; i++) {                         /* basic cycle start */  
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);  
        sum -= delta;  
    }                                              /* end cycle */  
    v[0]=v0; v[1]=v1;  
}

void tea_test() {
    uint32_t v[2]={1,2},k[4]={2,2,3,4};  
    encrypt(v, k);  
    decrypt(v, k);  
}

void encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {  
    unsigned int i;  
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;  
    for (i=0; i < num_rounds; i++) {  
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);  
        sum += delta;  
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);  
    }  
    v[0]=v0; v[1]=v1;  
}  
  
void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {  
    unsigned int i;  
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*num_rounds;  
    for (i=0; i < num_rounds; i++) {  
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);  
        sum -= delta;  
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);  
    }  
    v[0]=v0; v[1]=v1;  
}

void xtea_test() {
    uint32_t v[2]={1,2};  
    uint32_t const k[4]={2,2,3,4};  
    unsigned int r=32;//num_rounds建议取值为32  
    // v为要加密的数据是两个32位无符号整数  
    // k为加密解密密钥，为4个32位无符号整数，即密钥长度为128位  
    encipher(r, v, k);  
    decipher(r, v, k);  
}

#define DELTA 0x9e3779b9  
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))  
  
void btea(uint32_t *v, int n, uint32_t const key[4])  
{  
    uint32_t y, z, sum;  
    unsigned p, rounds, e;  
    if (n > 1)            /* Coding Part */  
    {  
        rounds = 6 + 52/n;  
        sum = 0;  
        z = v[n-1];  
        do  
        {  
            sum += DELTA;  
            e = (sum >> 2) & 3;  
            for (p=0; p<n-1; p++)  
            {  
                y = v[p+1];  
                z = v[p] += MX;  
            }  
            y = v[0];  
            z = v[n-1] += MX;  
        }  
        while (--rounds);  
    }  
    else if (n < -1)      /* Decoding Part */  
    {  
        n = -n;  
        rounds = 6 + 52/n;  
        sum = rounds*DELTA;  
        y = v[0];  
        do  
        {  
            e = (sum >> 2) & 3;  
            for (p=n-1; p>0; p--)  
            {  
                z = v[p-1];  
                y = v[p] -= MX;  
            }  
            z = v[n-1];  
            y = v[0] -= MX;  
            sum -= DELTA;  
        }  
        while (--rounds);  
    }  
}

void xxtea_test() {
    uint32_t v[2]= {1,2};  
    uint32_t const k[4]= {2,2,3,4};  
    int n= 2; //n的绝对值表示v的长度，取正表示加密，取负表示解密  
    // v为要加密的数据是两个32位无符号整数  
    // k为加密解密密钥，为4个32位无符号整数，即密钥长度为128位  
    btea(v, n, k);  
    btea(v, -n, k);  
}

char f1ag[40] = "flag{i_am_no_flag}";

char *a() {
    // zjgsuctf{yuz3_1s_4_l4zy_pI9}
    char flag[40] = {0x1c, 0x6, 0x6, 0x14, 0xe, 0xa, 0x2b, 0x7, 0x16, 0x26, 0x1b, 0x15, 0x6c, 0x39, 0x5d, 0x12, 0x39, 0x58, 0x3e, 0xb, 0x4f, 0x13, 0x26, 0x3e, 0x1d, 0x16, 0x57, 0x12};
    char *result = (char *) malloc(40);
    int i = 0;

    for (i = 0; i < strlen(flag); i++) {
        *(result + i) = flag[i] ^ f1ag[i % 16];
    }
    *(result + i) = '\0';

    //for (i = 0; i < strlen(flag); i++) {
    //    printf("0x%x, ", *(result + i));
    //}
    //printf("\n");

    return result;
}

int main() {
    char buf[50] = {0}; // zjgsuctf{yuz3_1s_4_l4zy_pI9}
    char welcome[40] = "Plz input your flag: ";

	puts(banner);
	tea_test();
	xtea_test();
	xxtea_test();

    write(1, welcome, strlen(welcome));
    read(0, buf, 28);
    //for (int i = 0; i < strlen(buf); i++) {
    //    printf("0x%x, ", buf[i]);
    //}
    //printf("\n");

    if (strcmp(buf, a()) == 0) {
        puts("this is ez 4 u~");
    } else {
        puts("how stupid r u...");
    }

    exit(0);
}
