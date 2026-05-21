#include "pch.h"
#include "CppUnitTest.h"
#include "../shop/shop.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestEmptyCartTotal)
        {
            OrderManager manager;
            Assert::AreEqual(0.0, manager.calculateTotal());
        }

        TEST_METHOD(TestAddToCartTotal)
        {
            OrderManager manager;
            manager.addToCart(1, 2);
            Assert::AreEqual(50000.0, manager.calculateTotal());
        }

        TEST_METHOD(TestUpdateAndRemove)
        {
            OrderManager manager;
            manager.addToCart(2, 1);
            manager.updateQuantity(2, 3);
            Assert::AreEqual(1950.0, manager.calculateTotal());

            manager.removeFromCart(2);
            Assert::AreEqual(0.0, manager.calculateTotal());
        }

        TEST_METHOD(TestPromoCodeDiscount)
        {
            OrderManager manager;
            manager.addToCart(3, 1);
            manager.applyPromoCode("STUDENT");
            Assert::AreEqual(1080.0, manager.calculateTotal());
        }

        TEST_METHOD(TestBirthdayDiscount)
        {
            OrderManager manager;
            manager.addToCart(3, 1);
            manager.applyBirthdayDiscount(5, 5);
            Assert::AreEqual(1020.0, manager.calculateTotal());
        }
    };
}