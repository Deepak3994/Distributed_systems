#include"rpc/rpc.h"
#include"square.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include <unistd.h>

square_out *squareproc_1_svc(square_in *inp,struct svc_req *rqstp)
{
     static square_out out;
     out.res1= inp->arg1 * inp->arg1;
     sleep(120);
     return(&out);
}

square_out *sqrproc_1_svc(square_in *inp,struct svc_req *rqstp)
{
     static square_out out;
     printf("%ld",out.res1= inp->arg1 * inp->arg1);
     sleep(120);
     return(&out);
}