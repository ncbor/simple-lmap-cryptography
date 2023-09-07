#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define S 128

int main(int argc, char *argv[])
{
  double x0, b, xmin, xmax;
  FILE *in, *out, *key;
  key = fopen("key.txt","r");


  if(argc<2){printf("Faltam argumentos.\n");return 1;}
  else if (!(in = fopen(argv[1],"r"))){printf("Arquivo não existe\n");return 1;}

  fscanf(key,"%lf %lf %lf %lf",&x0,&b,&xmin,&xmax);
  double e = (xmax-xmin)/S;
  out = fopen("result.txt","w+");

  char buf[1000];
  while (fgets(buf, sizeof buf, in))
  {
    char *p = buf, *s = p;
    p = strtok_r(s," ", &s);
    while (p)
    {
      int i = atoi(p);
      char res = decrypt(i, &x0, xmin, e, b);
      fprintf(out, "%c",res);
      p = strtok_r(s ," ", &s);
    }
    fprintf(out,"\n");
  }
  printf("Documento foi descriptografado.\n");
  return 0;
}

int lmap(double *x,double b)
{
  double xi = b*(*x)*(1-(*x));
  (*x)=xi;
  return 0;
}

char decrypt(int i, double *x0, double xmin, double e, double b)
{
  for(int aux = 0; aux<i;++aux)
  {
    lmap(x0,b);
  }
  char c = ((*x0)-xmin)/e;
  return c;
}

