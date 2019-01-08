#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{	unsigned char blue;	unsigned char green;	unsigned char red;}pixel;
int header[20];
unsigned alg;
char aleg[100];
pixel padding;
unsigned int  xorshift32(unsigned int  x)
{x^=x<<13;x^=x>>17;x^=x<<5;return x;}
void citireHEADER(FILE *f,int *header)
{fread(&header[0],2,1,f);fread(&header[1],4,1,f);fread(&header[2],2,1,f);fread(&header[3],2,1,f);fread(&header[4],4,1,f);fread(&header[5],4,1,f);fread(&header[6],4,1,f);fread(&header[7],4,1,f);fread(&header[8],2,1,f);fread(&header[9],2,1,f);fread(&header[10],4,1,f);fread(&header[11],4,1,f);fread(&header[12],4,1,f);fread(&header[13],4,1,f);fread(&header[14],4,1,f);fread(&header[15],4,1,f);}
void copiereHEADER(FILE *g,int *header)
{fwrite(&header[0],2,1,g);fwrite(&header[1],4,1,g);fwrite(&header[2],2,1,g);fwrite(&header[3],2,1,g);fwrite(&header[4],4,1,g);fwrite(&header[5],4,1,g);fwrite(&header[6],4,1,g);fwrite(&header[7],4,1,g);fwrite(&header[8],2,1,g);fwrite(&header[9],2,1,g);fwrite(&header[10],4,1,g);fwrite(&header[11],4,1,g);fwrite(&header[12],4,1,g);fwrite(&header[13],4,1,g);fwrite(&header[14],4,1,g);fwrite(&header[15],4,1,g);}
void afisare(FILE *g, pixel *p, int *header)
{	int i,j;
	copiereHEADER(g,header);
	for(i=0;i<header[7];i++)
		{for(j=0;j<header[6];j++)fwrite(&p[i*header[6]+j],3,1,g);
			if(header[6]%4!=0) fwrite(&padding,header[6]%4,1,g);}
	free(p);}
pixel* urcare(FILE *f,int *header)
{
	citireHEADER(f,header);
	pixel *p=(pixel*)malloc(sizeof(pixel)*header[6]*header[7]);
	int i,j;
	for(i=0;i<header[7];i++)
		{for(j=0;j<header[6];j++)	fread(&p[i*header[6]+j],3,1,f);
		if(header[6]%4!=0) fread(&padding,header[6]%4,1,f);}
	return p;}
void partea_de_criptare()
{
	FILE *f,*g;
	if(alg==1)printf("\nCe imagine veti cripta? Introduceti numele:\n");
	if(alg==2)printf("\nCe imagine veti cripta? Introduceti numele:\n");
	if(alg==3)printf("\nCe imagine veti cripta? Introduceti numele:\n");
	if(alg==4)printf("\nCe imagine veti cripta? Introduceti numele:\n");
	if(alg==5)printf("\nCe imagine veti cripta? Introduceti numele:\n");
	char nume1[100],nume2[100];
	while(1)
	{	scanf("%s",nume1);
		f=fopen(nume1,"rb");
		if(f==NULL)
		{if(alg==1)printf("\nNume incorect, reincercati:\n");
		if(alg==2)printf("\nNume incorect, reincercati:\n");
		if(alg==3)printf("\nNume incorect, reincercati:\n");
		if(alg==4)printf("\nNume incorect, reincercati:\n");
		if(alg==5)printf("\nNume incorect, reincercati:\n");}
		else break;}
	if(alg==1)printf("\nNoul nume al imaginii criptate:\n");
	if(alg==2)printf("\nNoul nume al imaginii criptate:\n");
	if(alg==3)printf("\nNoul nume al imaginii criptate:\n");
	if(alg==4)printf("\nNoul nume al imaginii criptate:\n");
	if(alg==5)printf("\nNoul nume al imaginii criptate:\n");
	scanf("%s",nume2);
	g=fopen(nume2,"wb");
	pixel *p=urcare(f,header);
	unsigned int  SV,seed;
	if(alg==1)printf("\nIntroduceti doua chei unice intre 1 si 4294967295:");
	if(alg==2)printf("\nIntroduceti doua chei unice intre 1 si 4294967295:");
	if(alg==3)printf("\nIntroduceti doua chei unice intre 1 si 4294967295:");
	if(alg==4)printf("\nIntroduceti doua chei unice intre 1 si 4294967295:");
	if(alg==5)printf("\nIntroduceti doua chei unice intre 1 si 4294967295:");
		scanf("%u %u",&seed,&SV);
	unsigned k,l;
	unsigned long long i;
	for(k=0;k<header[7]/2;k++)
		for(l=0;l<header[6];l++)
		{pixel aux=p[k*header[6]+l];p[k*header[6]+l]=p[(header[7]-k-1)*header[6]+l];p[(header[7]-k-1)*header[6]+l]=aux;}
	unsigned int *R;
	R=(unsigned int*)malloc(2*header[6]*header[7]*sizeof(unsigned int ));
	R[0]=seed;
	for(i=1;i<2*header[6]*header[7];i++)
		R[i]=xorshift32(R[i-1]);
	unsigned int *PERM;
	PERM=(unsigned int*)malloc((header[6]*header[7])*sizeof(unsigned int));
    for(i=0;i<header[6]*header[7];i++)
     PERM[i]=i;
    for(i=header[6]*header[7]-1;i>=1;i--)
    {	unsigned int K=R[header[6]*header[7]-i]%(i+1);
        unsigned int aux= PERM[i];
        PERM[i]=PERM[K];
        PERM[K]=aux;}
   pixel *X=(pixel*)malloc(header[6]*header[7]*sizeof(pixel));
    for(i=0;i<header[6]*header[7];i++)
		X[PERM[i]]=p[i];
	for(i=0;i<header[6]*header[7];i++)
		p[i]=X[i];
	unsigned int ABC=R[header[6]*header[7]];
	p[0].blue=		(SV&255)^p[0].blue			^(ABC&255);				SV=SV>>8; ABC=ABC>>8;
	p[0].green=		(SV&255)^p[0].green			^(ABC&255);				SV=SV>>8; ABC=ABC>>8;
	p[0].red=			(SV&255)^p[0].red				^(ABC&255);

	for(i=1;i<header[6]*header[7];i++)
	{
	ABC=R[header[6]*header[7]+i];
	p[i].blue=	p[i-1].blue  			^p[i].blue	^(ABC&255);				ABC=ABC>>8;
	p[i].green=	p[i-1].green			^p[i].green	^(ABC&255); 			ABC=ABC>>8;
	p[i].red=		p[i-1].red				^p[i].red		^(ABC&255);
	}
	for(k=0;k<header[7]/2;k++)
		for(l=0;l<header[6];l++)
		{pixel aux=p[k*header[6]+l];p[k*header[6]+l]=p[(header[7]-k-1)*header[6]+l];p[(header[7]-k-1)*header[6]+l]=aux;}
	afisare(g,p,header);free(PERM);free(X);free(R);fclose(f);fclose(g);
}
void partea_de_decriptare()
{
	FILE *f,*g;
	if(alg==1)printf("\nCe imagine veti decripta? Introduceti numele:\n");
	if(alg==2)printf("\nCe imagine veti decripta? Introduceti numele:\n");
	if(alg==3)printf("\nCe imagine veti decripta? Introduceti numele:\n");
	if(alg==4)printf("\nCe imagine veti decripta? Introduceti numele:\n");
	if(alg==5)printf("\nCe imagine veti decripta? Introduceti numele:\n");
	char nume1[100],nume2[100];
	while(1)
	{	scanf("%s",nume1);
		f=fopen(nume1,"rb");
		if(f==NULL)
		{if(alg==1)printf("\nNume incorect, reincercati:\n");
		if(alg==2)printf("\nNume incorect, reincercati:\n");
		if(alg==3)printf("\nNume incorect, reincercati:\n");
		if(alg==4)printf("\nNume incorect, reincercati:\n");
		if(alg==5)printf("\nNume incorect, reincercati:\n");}
		else break;}
	if(alg==1)printf("\nNoul nume al imaginii decriptate:\n");
	if(alg==2)printf("\nNoul nume al imaginii decriptate:\n");
	if(alg==3)printf("\nNoul nume al imaginii decriptate:\n");
	if(alg==4)printf("\nNoul nume al imaginii decriptate:\n");
	if(alg==5)printf("\nNoul nume al imaginii decriptate:\n");
	scanf("%s",nume2);
	g=fopen(nume2,"wb");
	pixel *p=urcare(f,header);
	unsigned int  SV,seed;
	unsigned k,l;
	unsigned long long i;
	if(alg==1)printf("\nIntroduceti doua chei unice intre 0 si 4294967295:");
	if(alg==2)printf("\nIntroduceti doua chei unice intre 0 si 4294967295:");
	if(alg==3)printf("\nIntroduceti doua chei unice intre 0 si 4294967295:");
	if(alg==4)printf("\nIntroduceti doua chei unice intre 0 si 4294967295:");
	if(alg==5)printf("\nIntroduceti doua chei unice intre 0 si 4294967295:");
		scanf("%u %u",&seed,&SV);
	for(k=0;k<header[7]/2;k++)
		for(l=0;l<header[6];l++)
		{pixel aux=p[k*header[6]+l];p[k*header[6]+l]=p[(header[7]-k-1)*header[6]+l];p[(header[7]-k-1)*header[6]+l]=aux;}
	unsigned int *R;
	R=(unsigned int*)malloc(2*header[6]*header[7]*sizeof(unsigned int ));
	R[0]=seed;
	for(i=1;i<2*header[6]*header[7];i++)
		R[i]=xorshift32(R[i-1]);
	unsigned int ABC;
	for(i=header[6]*header[7]-1;i>=1;i--)
	{	ABC=R[header[6]*header[7]+i];
	p[i].blue=	p[i-1].blue  		^p[i].blue 	^(ABC&255);			ABC=ABC>>8;
	p[i].green=	p[i-1].green		^p[i].green	^(ABC&255); 		ABC=ABC>>8;
	p[i].red=		p[i-1].red			^p[i].red		^(ABC&255);}
	ABC=R[header[6]*header[7]];
	p[0].blue=		(SV&255)^p[0].blue			^(ABC&255);				SV=SV>>8; ABC=ABC>>8;
	p[0].green=		(SV&255)^p[0].green			^(ABC&255);				SV=SV>>8; ABC=ABC>>8;
	p[0].red=			(SV&255)^p[0].red				^(ABC&255);
	unsigned int *PERM;
	PERM=(unsigned int*)malloc((header[6]*header[7])*sizeof(unsigned int));
    for(i=0;i<header[6]*header[7];i++)PERM[i]=i;
    for(i=header[6]*header[7]-1;i>=1;i--)
    {	unsigned int K=R[header[6]*header[7]-i]%(i+1);
        unsigned int aux= PERM[i]; PERM[i]=PERM[K];PERM[K]=aux;    }
	pixel *X=(pixel*)malloc(header[6]*header[7]*sizeof(pixel));
    for(i=0;i<header[6]*header[7];i++)		X[i]=p[PERM[i]];
	for(i=0;i<header[6]*header[7];i++)		p[i]=X[i];
	for(k=0;k<header[7]/2;k++)
		for(l=0;l<header[6];l++)
		{pixel aux=p[k*header[6]+l];p[k*header[6]+l]=p[(header[7]-k-1)*header[6]+l];p[(header[7]-k-1)*header[6]+l]=aux;}
	afisare(g,p,header);	free(R);	free(PERM);	free(X);	fclose(f);	fclose(g);}
void alegere()
{

	if(alg==1)
	{	while(1)
		{	printf("\nCe doriti sa faceti? \n	1)criptare imagine \n	2)decriptare imagine\n	3)exit\n");
		unsigned  x;char xx[100];scanf("%s",xx);
	if(strlen(xx)==1){
		x=(unsigned)(xx[0]-'0');
	if(x==1) partea_de_criptare();
	if(x==2) partea_de_decriptare();
	if(x==3) return;}
	if(x>3||x<=0)
	 printf("\n\n\n\n\n Try again! \n\n\n\n\n");}}
	if(alg==2)
	{	while(1)
		{	printf("\nCe doriti sa faceti? \n	1)criptare imagine \n	2)decriptare imagine\n	3)exit\n");
		unsigned  x;char xx[100];scanf("%s",xx);
	if(strlen(xx)==1){
		x=(unsigned)(xx[0]-'0');
	if(x==1) partea_de_criptare();
	if(x==2) partea_de_decriptare();
	if(x==3) return;}
	if(x>3||x<=0)
	 printf("\n\n\n\n\n Try again! \n\n\n\n\n");}}
	if(alg==3)
	{	while(1)
		{			printf("\nCe doriti sa faceti? \n	1)criptare imagine \n	2)decriptare imagine\n	3)exit\n");
		unsigned  x;char xx[100];scanf("%s",xx);
	if(strlen(xx)==1){
		x=(unsigned)(xx[0]-'0');
	if(x==1) partea_de_criptare();
	if(x==2) partea_de_decriptare();
	if(x==3) return;}
	if(x>3||x<=0)
	 printf("\n\n\n\n\n Try again! \n\n\n\n\n");}}
	if(alg==4)
	{	while(1)
		{			printf("\nCe doriti sa faceti? \n	1)criptare imagine \n	2)decriptare imagine\n	3)exit\n");
		unsigned  x;char xx[100];scanf("%s",xx);
	if(strlen(xx)==1){
		x=(unsigned)(xx[0]-'0');
	if(x==1) partea_de_criptare();
	if(x==2) partea_de_decriptare();
	if(x==3) return;}
	if(x>3||x<=0)
	 printf("\n\n\n\n\n Try again! \n\n\n\n\n");}}
	if(alg==5)
	{	while(1)
		{			printf("\nCe doriti sa faceti? \n	1)criptare imagine \n	2)decriptare imagine\n	3)exit\n");
				unsigned  x;char xx[100];scanf("%s",xx);
			if(strlen(xx)==1){
				x=(unsigned)(xx[0]-'0');
			if(x==1) partea_de_criptare();
			if(x==2) partea_de_decriptare();
			if(x==3) return;}
			if(x>3||x<=0)
			 printf("\n\n\n\n\n Try again! \n\n\n\n\n");}}
}
int main()
{
	while(1)
	{		printf("\nSelect your language (pick a number):\n	1)english\n	2)germain\n	3)romanian\n	4)french\n	5)spanish\n\n");
		scanf("%s",aleg);
		if(strlen(aleg)==1)
		{alg=(unsigned)(aleg[0]-'0');
		if(alg>=1&&alg<=5)
		break;}
		printf("\n\n\n\nWrong,try again:\n\n\n\n");}
	alegere();
	return 0;
}
