// Program 8.6 A function to increase your pay that doesn't
#include <stdio.h>

long *IncomePlus(long* pPay);

int main(void)
{
    long your_pay = 30000L;
    long *pold_pay = &your_pay;
    long *pnew_pay = NULL;
    pnew_pay = IncomePlus(pold_pay);
    printf("Old pay = $%ld\n", *pold_pay);
    printf(" New pay = $%ld\n", *pnew_pay);
    return 0;
}

long *IncomePlus(long *pPay)
{
    long pay = 0;

    pay = *pPay + 10000;
    return &pay;
}