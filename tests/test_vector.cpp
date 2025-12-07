

#include <gtest/gtest.h>
#include <string>
#include "customvec.hpp"

// Helper for value generation
template <typename T>
struct test_value
{
    static T get(int i);
};

template <>
struct test_value<int>
{
    static int get(int i) { return i * 10; }
};

template <>
struct test_value<std::string>
{
    static std::string get(int i) { return "str" + std::to_string(i); }
};

// Templated test fixture
template <typename T>
class VectorTypedTest : public ::testing::Test
{
};

using TestTypes = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(VectorTypedTest, TestTypes);

TYPED_TEST(VectorTypedTest, PushBackAndSize)
{
    customvec::Vector<TypeParam> v;
    EXPECT_EQ(v.size(), 0);
    v.push_back(test_value<TypeParam>::get(1));
    v.push_back(test_value<TypeParam>::get(2));
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], test_value<TypeParam>::get(1));
    EXPECT_EQ(v[1], test_value<TypeParam>::get(2));
}

TYPED_TEST(VectorTypedTest, CopyConstructor)
{
    customvec::Vector<TypeParam> v;
    v.push_back(test_value<TypeParam>::get(42));
    customvec::Vector<TypeParam> w = v;
    EXPECT_EQ(w.size(), 1);
    EXPECT_EQ(w[0], test_value<TypeParam>::get(42));
    w[0] = test_value<TypeParam>::get(99);
    EXPECT_EQ(v[0], test_value<TypeParam>::get(42)); // original should not change
}

TYPED_TEST(VectorTypedTest, CopyAssignment)
{
    customvec::Vector<TypeParam> v;
    v.push_back(test_value<TypeParam>::get(10));
    v.push_back(test_value<TypeParam>::get(20));
    customvec::Vector<TypeParam> w;
    w = v;
    EXPECT_EQ(w.size(), 2);
    EXPECT_EQ(w[0], test_value<TypeParam>::get(10));
    EXPECT_EQ(w[1], test_value<TypeParam>::get(20));
    w[0] = test_value<TypeParam>::get(99);
    EXPECT_EQ(v[0], test_value<TypeParam>::get(10)); // original should not change
}

TYPED_TEST(VectorTypedTest, Clear)
{
    customvec::Vector<TypeParam> v;
    v.push_back(test_value<TypeParam>::get(1));
    v.push_back(test_value<TypeParam>::get(2));
    v.clear();
    EXPECT_EQ(v.size(), 0);
    v.push_back(test_value<TypeParam>::get(3));
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], test_value<TypeParam>::get(3));
}

TYPED_TEST(VectorTypedTest, CopyConstructorIndependence)
{
    customvec::Vector<TypeParam> a;
    for (int i = 0; i < 5; ++i)
        a.push_back(test_value<TypeParam>::get(i));
    customvec::Vector<TypeParam> b = a;
    EXPECT_EQ(b.size(), a.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        EXPECT_EQ(b[i], a[i]);
    a[0] = test_value<TypeParam>::get(42);
    EXPECT_EQ(a[0], test_value<TypeParam>::get(42));
    EXPECT_EQ(b[0], test_value<TypeParam>::get(0)); // b should stay unchanged
}

TYPED_TEST(VectorTypedTest, CopyAssignmentIndependence)
{
    customvec::Vector<TypeParam> a;
    for (int i = 0; i < 5; ++i)
        a.push_back(test_value<TypeParam>::get(i));
    customvec::Vector<TypeParam> c;
    c.push_back(test_value<TypeParam>::get(100));
    c.push_back(test_value<TypeParam>::get(200));
    c = a;
    EXPECT_EQ(c.size(), a.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        EXPECT_EQ(c[i], a[i]);
    a[0] = test_value<TypeParam>::get(99);
    EXPECT_EQ(a[0], test_value<TypeParam>::get(99));
    EXPECT_EQ(c[0], test_value<TypeParam>::get(0)); // c should stay unchanged
}

TYPED_TEST(VectorTypedTest, MoveConstructor)
{
    customvec::Vector<TypeParam> a;
    for (int i = 0; i < 5; ++i)
        a.push_back(test_value<TypeParam>::get(i));
    customvec::Vector<TypeParam> b = std::move(a);
    EXPECT_EQ(b.size(), 5);
    for (std::size_t i = 0; i < b.size(); ++i)
        EXPECT_EQ(b[i], test_value<TypeParam>::get(i));
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
}

TYPED_TEST(VectorTypedTest, MoveAssignment)
{
    customvec::Vector<TypeParam> a;
    for (int i = 0; i < 3; ++i)
        a.push_back(test_value<TypeParam>::get(i));
    customvec::Vector<TypeParam> b;
    b.push_back(test_value<TypeParam>::get(1));
    b.push_back(test_value<TypeParam>::get(2));
    b = std::move(a);
    EXPECT_EQ(b.size(), 3);
    for (std::size_t i = 0; i < b.size(); ++i)
        EXPECT_EQ(b[i], test_value<TypeParam>::get(i));
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
}

template <typename T>
customvec::Vector<T> make_vector_for_test()
{
    customvec::Vector<T> tmp;
    for (int i = 0; i < 5; ++i)
        tmp.push_back(test_value<T>::get(i));
    return tmp;
}

TYPED_TEST(VectorTypedTest, ReturnByValueMoveOrRVO)
{
    customvec::Vector<TypeParam> d = make_vector_for_test<TypeParam>();
    EXPECT_EQ(d.size(), 5);
    for (std::size_t i = 0; i < d.size(); ++i)
        EXPECT_EQ(d[i], test_value<TypeParam>::get(i));
}
