#ifndef MD5_H
#define MD5_H

typedef unsigned int MD5_u32;

typedef struct {
	MD5_u32 lo, hi;
	MD5_u32 a, b, c, d;
	unsigned char buffer[64];
	MD5_u32 block[16];
} MD5_CTX;
 
extern void MD5_Init(MD5_CTX *ctx);
extern void MD5_Update(MD5_CTX *ctx, const void *data, unsigned long size);
extern void MD5_Final(unsigned char *result, MD5_CTX *ctx);

#endif // end of MD5_H
