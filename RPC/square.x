struct square_in
{
/*input arg*/
long arg1;
};

struct square_out
{
/*op result*/
long res1;
};

program SQUARE_PROG
{
version SQUARE_VERS
{
square_out SQUAREPROC(square_in)=1; /*proc no=1*/
square_out SQRPROC(square_in)=2; /*proc no=2*/
}=1; /*version no*/
}=0x31230000;/*prog no*/