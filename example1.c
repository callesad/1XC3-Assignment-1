#include <stdio.h>

int main () {
double a = 2.0;
for ( int i = 0; i < 10; i++)
{
a -= 1e-16;
}
printf ("result = %0.15lf\n",a) ;
}
