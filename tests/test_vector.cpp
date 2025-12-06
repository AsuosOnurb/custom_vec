#include <gtest/gtest.h>
#include "customvec.hpp"

// Test that push_back correctly adds elements and size is updated.
// Also checks that operator[] returns the correct values.
TEST(VectorTest, PushBackAndSize)
{
    customvec::Vector v;
    EXPECT_EQ(v.size(), 0); // Should start empty
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2); // Size should reflect number of elements
    EXPECT_EQ(v[0], 1);     // First element
    EXPECT_EQ(v[1], 2);     // Second element
}

// Test that the copy constructor creates an independent copy.
// Modifying the copy should not affect the original.
TEST(VectorTest, CopyConstructor)
{
    customvec::Vector v;
    v.push_back(42);
    customvec::Vector w = v;
    EXPECT_EQ(w.size(), 1);
    EXPECT_EQ(w[0], 42);
    w[0] = 99;
    EXPECT_EQ(v[0], 42); // Original should not change
}

// Test that the copy assignment operator creates an independent copy.
// Modifying the assigned-to vector should not affect the source.
TEST(VectorTest, CopyAssignment)
{
    customvec::Vector v;
    v.push_back(10);
    v.push_back(20);
    customvec::Vector w;
    w = v;
    EXPECT_EQ(w.size(), 2);
    EXPECT_EQ(w[0], 10);
    EXPECT_EQ(w[1], 20);
    w[0] = 99;
    EXPECT_EQ(v[0], 10); // Original should not change
}

// Test that clear() empties the vector but does not deallocate memory.
// After clear, the vector should accept new elements.
TEST(VectorTest, Clear)
{
    customvec::Vector v;
    v.push_back(1);
    v.push_back(2);
    v.clear();
    EXPECT_EQ(v.size(), 0); // Should be empty
    v.push_back(3);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 3);
}

// Test that a copied vector is fully independent (deep copy).
// Changing the original after copying does not affect the copy.
TEST(VectorTest, CopyConstructorIndependence)
{
    customvec::Vector a;
    for (int i = 0; i < 5; ++i)
        a.push_back(i + 1); // 1 2 3 4 5

    customvec::Vector b = a; // Copy
    EXPECT_EQ(b.size(), a.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        EXPECT_EQ(b[i], a[i]);

    a[0] = 42;
    EXPECT_EQ(a[0], 42);
    EXPECT_EQ(b[0], 1); // b should stay unchanged
}

// Test that a vector assigned from another is fully independent (deep copy).
// Changing the source after assignment does not affect the assigned-to vector.
TEST(VectorTest, CopyAssignmentIndependence)
{
    customvec::Vector a;
    for (int i = 0; i < 5; ++i)
        a.push_back(i + 1); // 1 2 3 4 5

    customvec::Vector c;
    c.push_back(100);
    c.push_back(200);
    c = a; // Assignment
    EXPECT_EQ(c.size(), a.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        EXPECT_EQ(c[i], a[i]);

    a[0] = 99;
    EXPECT_EQ(a[0], 99);
    EXPECT_EQ(c[0], 1); // c should stay unchanged
}

// Test that the move constructor transfers ownership and leaves the source empty.
// The moved-to vector should have all the original data, and the moved-from vector should be empty.
TEST(VectorTest, MoveConstructor)
{
    customvec::Vector a;
    for (int i = 0; i < 5; ++i)
        a.push_back(i + 10); // 10 11 12 13 14

    customvec::Vector b = std::move(a); // Move constructor
    EXPECT_EQ(b.size(), 5);
    for (std::size_t i = 0; i < b.size(); ++i)
        EXPECT_EQ(b[i], 10 + static_cast<int>(i));
    // a should be empty after move
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
}

// Test that the move assignment operator transfers ownership and leaves the source empty.
// The assigned-to vector should have all the original data, and the moved-from vector should be empty.
TEST(VectorTest, MoveAssignment)
{
    customvec::Vector a;
    for (int i = 0; i < 3; ++i)
        a.push_back(100 + i); // 100 101 102
    customvec::Vector b;
    b.push_back(1);
    b.push_back(2);
    b = std::move(a); // Move assignment
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 100);
    EXPECT_EQ(b[1], 101);
    EXPECT_EQ(b[2], 102);
    // a should be empty after move
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
}

// Helper function to test return-by-value (move or NRVO).
// Returns a vector with 5 elements (1..5).
customvec::Vector make_vector_for_test()
{
    customvec::Vector tmp;
    for (int i = 0; i < 5; ++i)
        tmp.push_back(i + 1);
    return tmp; // Will use move or NRVO
}

// Test that returning a vector by value works (move or NRVO).
// The returned vector should have the correct contents.
TEST(VectorTest, ReturnByValueMoveOrRVO)
{
    customvec::Vector d = make_vector_for_test();
    EXPECT_EQ(d.size(), 5);
    for (std::size_t i = 0; i < d.size(); ++i)
        EXPECT_EQ(d[i], static_cast<int>(i + 1));
}
