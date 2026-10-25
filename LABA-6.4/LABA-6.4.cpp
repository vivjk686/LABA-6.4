// LABA-6.4.cpp
// Шах Владислав Ігорьович
// Лабораторна робота № 6.4
// Опрацювання та впорядкування одновимірних динамічних масивів
// Варіант 32 (Рекурсивний спосіб)

#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>

using namespace std;

// Рекурсивне формування динамічного масиву випадковими дійсними числами
void Create(double* a, const int size, const double Low, const double High, int i)
{
    // Округлення до 1 знака після коми для наочності
    double r = Low + (High - Low) * (rand() / (double)RAND_MAX);
    a[i] = round(r * 10.0) / 10.0;
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// Рекурсивне виведення елементів динамічного масиву
void Print(const double* a, const int size, int i)
{
    cout << setw(7) << setprecision(1) << fixed << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// 1.1. Рекурсивний пошук індексу максимального за модулем елементу масиву (0-based)
int MaxAbsIndex(const double* a, const int size, int i, int maxIdx)
{
    if (i >= size)
        return maxIdx;
    if (fabs(a[i]) > fabs(a[maxIdx]))
        maxIdx = i;
    return MaxAbsIndex(a, size, i + 1, maxIdx);
}

// 1.2. Рекурсивний пошук індексу першого додатного елементу
int FirstPositiveIndex(const double* a, const int size, int i)
{
    if (i >= size)
        return -1;
    if (a[i] > 0)
        return i;
    return FirstPositiveIndex(a, size, i + 1);
}

// Рекурсивне обчислення суми елементів масиву, розташованих після першого додатного елементу
double SumAfterFirstPositive(const double* a, const int size, int i)
{
    if (i >= size)
        return 0.0;
    return a[i] + SumAfterFirstPositive(a, size, i + 1);
}

// Загальна функція для обчислення суми після першого додатного елементу
double CalculateSumAfterFirstPositive(const double* a, const int size)
{
    int firstPos = FirstPositiveIndex(a, size, 0);
    if (firstPos == -1 || firstPos == size - 1)
        return 0.0;
    return SumAfterFirstPositive(a, size, firstPos + 1);
}

// Перевірка умови: ціла частина лежить в інтервалі [A, B]
bool InRange(double val, double A, double B)
{
    int intPart = static_cast<int>(val);
    return (intPart >= A && intPart <= B);
}

// Рекурсивне копіювання елементів, що лежать в інтервалі [A, B]
int CopyInRange(const double* a, const int size, double* temp, int i, int k, double A, double B)
{
    if (i >= size)
        return k;
    if (InRange(a[i], A, B))
    {
        temp[k] = a[i];
        return CopyInRange(a, size, temp, i + 1, k + 1, A, B);
    }
    return CopyInRange(a, size, temp, i + 1, k, A, B);
}

// Рекурсивне копіювання елементів, що НЕ лежать в інтервалі [A, B]
int CopyOutOfRange(const double* a, const int size, double* temp, int i, int k, double A, double B)
{
    if (i >= size)
        return k;
    if (!InRange(a[i], A, B))
    {
        temp[k] = a[i];
        return CopyOutOfRange(a, size, temp, i + 1, k + 1, A, B);
    }
    return CopyOutOfRange(a, size, temp, i + 1, k, A, B);
}

// Рекурсивне повернення елементів з тимчасового масиву назад в основний
void CopyBack(double* a, const double* temp, const int size, int i)
{
    if (i >= size)
        return;
    a[i] = temp[i];
    CopyBack(a, temp, size, i + 1);
}

// 2. Рекурсивне перетворення масиву:
// спочатку елементи, ціла частина яких в [A, B], потім всі інші (зі збереженням порядку)
void Transform(double* a, const int size, double A, double B)
{
    if (size <= 1)
        return;
    double* temp = new double[size];
    int k = CopyInRange(a, size, temp, 0, 0, A, B);
    CopyOutOfRange(a, size, temp, 0, k, A, B);
    CopyBack(a, temp, size, 0);
    delete[] temp;
}

#ifndef UNIT_TESTING
int main()
{
    srand((unsigned)time(NULL));

    int n;
    cout << "Enter size of dynamic array n: ";
    if (!(cin >> n) || n <= 0)
    {
        cout << "Invalid size! Using default n = 10" << endl;
        n = 10;
    }

    double a_range, b_range;
    cout << "Enter interval [a, b] for integer part:" << endl;
    cout << "a = "; cin >> a_range;
    cout << "b = "; cin >> b_range;

    double* a = new double[n];
    const double Low = -15.0;
    const double High = 15.0;

    cout << "\nLab 6.4 (Recursive) Variant 32" << endl;
    Create(a, n, Low, High, 0);

    cout << "\nInitial dynamic array:" << endl;
    Print(a, n, 0);

    // 1.1. Номер максимального за модулем елементу
    int maxIdx = MaxAbsIndex(a, n, 1, 0);
    cout << "\n1.1. Max by absolute value element = " << a[maxIdx]
         << " (index = " << maxIdx << ", number = " << (maxIdx + 1) << ")" << endl;

    // 1.2. Сума елементів після першого додатного
    int firstPos = FirstPositiveIndex(a, n, 0);
    double sum = CalculateSumAfterFirstPositive(a, n);
    if (firstPos != -1)
        cout << "1.2. First positive element = " << a[firstPos] << " at number " << (firstPos + 1)
             << ", sum of elements after it = " << sum << endl;
    else
        cout << "1.2. No positive elements found in the array!" << endl;

    // 2. Перетворення масиву
    Transform(a, n, a_range, b_range);
    cout << "\n2. Transformed dynamic array (integer part in [" << a_range << ", " << b_range << "] first):" << endl;
    Print(a, n, 0);

    delete[] a;
    return 0;
}
#endif
