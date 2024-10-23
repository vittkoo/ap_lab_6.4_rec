#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int* a, const int size, const int Low, const int High, int i)
{
    if (i < size)
    {
        a[i] = Low + rand() % (High - Low + 1);
        Create(a, size, Low, High, i + 1);
    }
}

void Print(int* a, const int size, int i)
{
    if (i < size)
    {
        cout << "a[" << setw(2) << i << " ] = " << a[i] << setw(7);
        Print(a, size, i + 1);
    }
    else
        cout << endl;
}

int Max(int* a, const int size, int i, int max)
{
    if (i < size)
    {
        if (a[i] > a[max])
            max = i;
        return Max(a, size, i + 1, max);
    }
    else
        return max;
}

int ProductBetweenZeros(int* a, const int size, int i, int firstZero, int secondZero)
{
    if (i < size)
    {
        if (a[i] == 0)
        {
            if (firstZero == -1)
                firstZero = i;
            else
                secondZero = i;
        }

        if (firstZero != -1 && secondZero != -1 && secondZero > firstZero + 1)
        {
            int product = 1;
            for (int j = firstZero + 1; j < secondZero; j++)
                product *= a[j];
            return product;
        }
        return ProductBetweenZeros(a, size, i + 1, firstZero, secondZero);
    }
    return 0; // якщо нема двох нулів або між ними немає елементів
}

void Rearrange(int* a, const int size)
{
    int* temp = new int[size];  // тимчасовий масив для перестановки
    int oddPos = 0;             // для непарних позицій
    int evenPos = (size + 1) / 2; // для парних позицій

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0)
            temp[oddPos++] = a[i];
        else
            temp[evenPos++] = a[i];
    }

    for (int i = 0; i < size; i++) {
        a[i] = temp[i];
    }

    delete[] temp;
}

int main()
{
    srand((unsigned)time(NULL));

    int n = 0;
    cout << "Enter n: "; cin >> n;
    int* a = new int[n];

    int Low = -10;
    int High = 10;

    Create(a, n, Low, High, 0);
    Print(a, n, 0);

    int max = Max(a, n, 1, 0);
    cout << "max = " << max << endl;

    cout << "Product between first and second zero = " << ProductBetweenZeros(a, n, 0, -1, -1) << endl;

    Rearrange(a, n);
    cout << "Array after rearranging: " << endl;
    Print(a, n, 0);

    delete[] a;
    return 0;
}