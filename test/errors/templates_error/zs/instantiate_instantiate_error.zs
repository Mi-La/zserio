package instantiate_instantiate_error;

struct Test<T>
{
    T value;
};

instantiate Test<uint32> T32;
instantiate T32 T;
