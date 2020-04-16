# include <stdio.h>

int main()
{

    const int maxInput = 5;
    int i;
    double number, average, sum=0.0;

    for(i=1; i<=maxInput; ++i)
    {
        printf("%d. Enter a number: ", i);
        scanf("%lf",&number);
        sum += number;
    }

    return 0;
}
