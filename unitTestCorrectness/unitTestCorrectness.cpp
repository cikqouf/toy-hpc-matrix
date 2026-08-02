#include "pch.h"
#include "CppUnitTest.h"

#include "mat.hpp"
#include <random>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unitTestCorrectness
{
    TEST_CLASS(unitTestCorrectness)
    {
    public:

        void CheckMatMul(int p, int q, int s)
        {
            using T = float;

            std::mt19937 rng(123);
            std::normal_distribution<T> dist(3.0, 1.0);

            mat<T> A(p, q, dist);
            mat<T> B(q, s, dist);

            mat<T> C = A * B;
            mat<T> C2(p, s, 0.0);

            for (int i = 0; i < p; ++i)
                for (int k = 0; k < q; ++k)
                    for (int j = 0; j < s; ++j)
                        C2.pData[i * s + j] +=
                        A.pData[i * q + k] * B.pData[k * s + j];

            // correctness check
            for (int i = 0; i < C.len; ++i)
            {
                float diff = std::abs(C.pData[i] - C2.pData[i]);
                Assert::IsTrue(diff < 1e-2f, L"Matrix multiplication mismatch");
            }
        }

        TEST_METHOD(Test_MatMul_0_to_1000)
        {
            for (int n = 0; n <= 1000; ++n)
            {
                CheckMatMul(n, n, n);
            }
        }
    };
}