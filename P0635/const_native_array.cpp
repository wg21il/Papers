

// compile with g++ -o const_native_array const_native_array.cpp
// expect the result to be: 
// error: assignment of read-only location ‘ar[0]’


int main()
{
    const int ar[2] = { 0, 0 };

    ar[0] = 3;

    return 0;
}

