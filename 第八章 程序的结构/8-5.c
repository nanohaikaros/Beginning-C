// Program 8.5 A function to increase your pay
#include <stdio.h>

long *IncomePlus(long* pPay);

int mian(void)
{
    long your_pay = 30000L;
    long *pold_pay = &your_pay;
    long *pnew_pay = NULL;
    pnew_pay = IncomePlus(pold_pay);
    printf("Old pay = $%ld\n", *pold_pay);
    printf(" New pay = $%ld\n", *pnew_pay);
    return 0;
}

long* IncomePlus(long *pPay)
{
    *pPay += 10000L;
    return pPay;
}