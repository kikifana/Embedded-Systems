#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 200 /* frame dimension for QCIF format */
#define M 200 /* frame dimension for QCIF format */
#define filename "sunflower_200x200_444.yuv"
#define file_yuv "sunflower_444_yuv_output.yuv"

/* code for armulator*/
#pragma arm section zidata="manual"
int new_y[N][M];
int current_y[N][M];

#pragma arm section zidata="sram"
int buffer1[M];
int buffer2[M];
int buffer3[M];
int i,j,k;

#pragma arm section
int current_u[N][M];
int current_v[N][M];




void read() 
{
  FILE *frame_c;
  if((frame_c=fopen(filename,"rb"))==NULL)
  {
    printf("current frame doesn't exist\n");
    exit(-1);
  }

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      current_y[i][j]=fgetc(frame_c);
    }
  }
  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      current_u[i][j]=fgetc(frame_c);
    }
  }
  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      current_v[i][j]=fgetc(frame_c);
    }
  }
  fclose(frame_c);
}

void write()
{
  FILE *frame_yuv;
  frame_yuv=fopen(file_yuv,"wb");

  for(i=0;i<N;i++)
        {
			for(j=0;j<M;j++)
			{
				fputc(new_y[i][j],frame_yuv);
			}
		}

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      fputc(current_u[i][j],frame_yuv);
    }
  }


  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      fputc(current_v[i][j],frame_yuv);
    }
  }
  fclose(frame_yuv);
}
 void filtering () {
	 
	 for (i=0; i<N; i++)
	 {
		 if(i==0) {
			 for(k=0;k<M;k++) {
				 buffer1[k]=current_y[0][k];
				  buffer2[k]=current_y[1][k];
				   buffer3[k]=current_y[2][k];
			 }
		 }else{
			 for(k=0;k<M;k++){
				 buffer1[k]=buffer2[k];
				 buffer2[k]=buffer3[k];
				 buffer3[k]=current_y[i][j];
			 }
		 }
	 }
 }
	
int main()
{
    int i;
	int j;
	double g;
	double noisyImage_y[N][M];	
	
	int k=3;
	
	
    read();
    filtering();
	
	i = 0;
	j = 0;
	if(i<N){
		if(j<M){
			do{
		
		g = buffer1[j];
		noisyImage_y[i][j] = ((exp(-g))*(g*g*g))/ ((k-2)*(k-1)*(k));
		new_y[i][j] =noisyImage_y[i][j];	
		
		g = buffer1[j+1];
	    noisyImage_y[i+1][j+1] = ((exp(-g))*(g*g*g))/ ((k-2)*(k-1)*(k));
		new_y[i+1][j+1] =noisyImage_y[i+1][j+1];
		
		g = buffer1[j+2];
	    noisyImage_y[i+2][j+2] = ((exp(-g))*(g*g*g))/ ((k-2)*(k-1)*(k));
		new_y[i+2][j+2] =noisyImage_y[i+2][j+2];
		
		g = buffer1[j+3];
	    noisyImage_y[i+3][j+3] = ((exp(-g))*(g*g*g))/ ((k-2)*(k-1)*(k));
		new_y[i+3][j+3] =noisyImage_y[i+3][j+3];
		i=i+4;
		j=j+4; 
		} while( j<M);
          	
		}	while(i<N);
	} 
  
  write();
 
}