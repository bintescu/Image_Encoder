#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct xorshift32_state
{
    uint32_t a;
};

uint32_t xorshift32(struct xorshift32_state *state)
{
    uint32_t x =state->a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return state->a=x;

}
int*** intoarcere(int M[3][3][3])
{
    int i,j,k;
    int ***S;
    S=malloc(3*sizeof(int**));
    for(int i=0;i<3;i++)
        {S[i]=malloc(3*sizeof(int*));
          for(int j=0;j<3;j++)
            S[i][j]=malloc(3*sizeof(int));
        }
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            for(k=0;k<2;k++)
                S[i][j][k]=M[i][j][k]+10;
        }
    }
    return S;
}
void Create_Copy(char *name,char *CopyName)
{   FILE *scriere = fopen("Pixelii.out","w");
    strcat(name,".bmp");
    FILE *fin = fopen(name,"rb");
    strcat(name,".bmp");
    printf("\n I have created the %s.bmp",CopyName);
    strcat(CopyName,".bmp");
    FILE *fout=fopen(CopyName,"wb+");
    if(fin==NULL)
    {
        printf("\n We can not find the image !");
        return 0;
    }
    else
    {
        int i;
        fseek(fin,2,SEEK_SET);
        fread(&i,sizeof(unsigned int),1,fin);
        printf("\n Dimension of the image = %d",i);
        int W,H;
        fseek(fin,18,SEEK_SET);
        fread(&W,sizeof(unsigned int),1,fin);
        fread(&H,sizeof(unsigned int),1,fin);
        printf("\n Weidth x Heigh = %d x %d \n",W,H);
        fseek(fin,0,SEEK_SET);
     unsigned char a;
     while(fread(&a,1,1,fin)!=NULL )
     {

         fwrite(&a,1,1,fout);
     }
   // I created a copy of the image.



    unsigned char pRGB[3];
    fseek(fin,54,SEEK_SET);
    fseek(fout,54,SEEK_SET);
    while(fread(pRGB,3,1,fin)!=NULL)
    {

        ///I have changed the colour of every pixel.
       int aux = 0.299*pRGB[2] + 0.587*pRGB[1] + 0.114*pRGB[0];
			pRGB[0] = pRGB[1] = pRGB[2] = aux;
        fwrite(pRGB,3,1,fout);

    }
     fseek(fin,54,SEEK_SET);
  int j=0;
  for(i=0;i<H;i++)
  { for(j=0;j<W;j++)
      {fread(pRGB,3,1,fin);
       fprintf(scriere," ,%d %d %d",pRGB[2],pRGB[1],pRGB[0]);
      }
    fprintf(scriere,"\n");
    }
    fclose(fin);
  fclose(scriere);
    fclose(fout);
}
}
int main()
{
    int M[3][3][3]={{{1,2,3},{4,5,6},{7,8,9}},{{10,11,12},{13,14,15},{16,17,18}},{{19,20,21},{22,23,24},{25,26,27}}};
    int ***S;
    S=intoarcere(M);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            free(S[i][j]);
    }

    for(int i=0;i<3;i++)
        free(S[i]);
    free(S);
  char *name;
    char *CopyName;
    name=malloc(100);
    CopyName=malloc(100);
    printf("Input the name of the image ! : ");
    scanf("%s",name);
    printf("\n Input the name of copy: ");
    scanf("%s",CopyName);
    Create_Copy(name,CopyName);
    free(name);
    free(CopyName);
    return 0;
}
