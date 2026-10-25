#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TESTING
#include "../LABA-6.4/LABA-6.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest64
{
    TEST_CLASS(UnitTest64)
    {
    public:
        TEST_METHOD(TestMaxAbsIndex)
        {
            // Max absolute value is |-25.5| = 25.5 at index 3 (number 4)
            double arr[] = { 3.2, -10.4, 18.0, -25.5, 7.1 };
            int idx = MaxAbsIndex(arr, 5, 1, 0);
            Assert::AreEqual(3, idx);
        }

        TEST_METHOD(TestFirstPositiveIndex)
        {
            double arr1[] = { -5.0, -2.1, 4.3, 10.0 };
            Assert::AreEqual(2, FirstPositiveIndex(arr1, 4, 0));

            double arr2[] = { -1.0, -2.0, -3.0 };
            Assert::AreEqual(-1, FirstPositiveIndex(arr2, 3, 0));
        }

        TEST_METHOD(TestSumAfterFirstPositive)
        {
            // first positive is 4.0 at index 2. Elements after it: -2.0, 5.0, 1.0 -> sum = 4.0
            double arr[] = { -10.0, -5.0, 4.0, -2.0, 5.0, 1.0 };
            double sum = CalculateSumAfterFirstPositive(arr, 6);
            Assert::AreEqual(4.0, sum, 1e-9);
        }

        TEST_METHOD(TestSumAfterFirstPositive_LastElement)
        {
            // first positive is the last element -> sum is 0
            double arr[] = { -3.0, -2.0, 5.0 };
            double sum = CalculateSumAfterFirstPositive(arr, 3);
            Assert::AreEqual(0.0, sum, 1e-9);
        }

        TEST_METHOD(TestSumAfterFirstPositive_NoPositive)
        {
            double arr[] = { -3.0, -2.0, -5.0 };
            double sum = CalculateSumAfterFirstPositive(arr, 3);
            Assert::AreEqual(0.0, sum, 1e-9);
        }

        TEST_METHOD(TestInRange)
        {
            // [2, 5]
            Assert::IsTrue(InRange(2.4, 2, 5));
            Assert::IsTrue(InRange(5.9, 2, 5));
            Assert::IsTrue(InRange(3.0, 2, 5));
            Assert::IsFalse(InRange(1.9, 2, 5));
            Assert::IsFalse(InRange(6.1, 2, 5));
            Assert::IsFalse(InRange(-2.0, 2, 5));
        }

        TEST_METHOD(TestTransform_StablePartition)
        {
            // Interval [2, 5]
            // In range: 2.5 (idx 1), 4.1 (idx 3), 3.0 (idx 5)
            // Out of range: -1.2 (idx 0), 8.3 (idx 2), 0.5 (idx 4)
            // Expected transformed order:
            // 2.5, 4.1, 3.0, -1.2, 8.3, 0.5
            double arr[] = { -1.2, 2.5, 8.3, 4.1, 0.5, 3.0 };
            Transform(arr, 6, 2, 5);

            Assert::AreEqual(2.5, arr[0], 1e-9);
            Assert::AreEqual(4.1, arr[1], 1e-9);
            Assert::AreEqual(3.0, arr[2], 1e-9);
            Assert::AreEqual(-1.2, arr[3], 1e-9);
            Assert::AreEqual(8.3, arr[4], 1e-9);
            Assert::AreEqual(0.5, arr[5], 1e-9);
        }
    };
}
