#include <allocation.hpp>

void* c_alloc(size_t size)
{
    if (size < MAX_ALLOC)
    {
        return malloc(size);
    }
    else
    {
        return nullptr;
    }
}
