#include <stdio.h>
#include <stdlib.h>
#include <math.h>
main(i){for(i=0;i<288;i++)printf(i%24-23?abs(i%24-11)*24>i|abs((i%24+i/72*3+3)%6-2)>i/24%3?"  ":"* ":"\n");}

