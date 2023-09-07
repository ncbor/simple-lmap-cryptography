#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define S 128
#define XMAX 0.8
#define XMIN 0.2
#define E (XMAX-XMIN)/S
#define N 0.7
#define N0 250
#define B 3.8


int main(int argc, char *argv[])
{
  srand(time(NULL));
  FILE *in, *out;
  char c;
  double x0 = 0.4;
  if(argc<2){printf("Faltam argumentos.\n");return 1;}
  else if (!(in = fopen(argv[1],"r"))){printf("Arquivo não existe\n");return 1;}

  out = fopen("cypher.txt","w+");
  gen_key(x0);

  int aux = 0;
  while((c = fgetc(in))!=EOF)
  {
    int char_val;
    if(c=='\n'){fprintf(out,"\n");aux=0;}
    else
    {

      char_val = encrypt(c, &x0);
      if(aux){fprintf(out," %d",char_val);}
      else{fprintf(out,"%d",char_val);}
      aux = 1;
    }
  }
  printf("Documento foi encriptado.\n");
  return 0;
}

int lmap(double *x)
{
  double xi = B*(*x)*(1-(*x));
  (*x)=xi;
  return 0;
}

int encrypt(char c, double *x0)
{
  int char_int = c;
  double min = XMIN+E*char_int, max = XMIN+E*(char_int+1);
  int aux = 0;
  while(aux<10000)
  {
    ++aux;
    lmap(x0);
    if( aux>N0 && min <= (*x0) && (*x0) < max)
    {

      double r = (double)rand()/RAND_MAX;
      if(r>N){return aux;}
    }
  }
  return 1;
}

int gen_key(double x0)
{
  FILE *key = fopen("key.txt","w+");
  fprintf(key, "%.16f %.15f %.16f %.16f",x0,B,XMIN,XMAX);
  return 0;
}

