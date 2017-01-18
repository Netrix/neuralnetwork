#pragma once

#include <memory>
#include <cassert>

template<class Type>
struct NotNull
{
    NotNull(Type* pointer)
        : m_pointer(pointer)
    {
        assert(pointer != nullptr);
    }

    NotNull(std::nullptr_t) = delete;

    Type* operator->()
    {
        return m_pointer;
    }

    Type const* operator->() const
    {
        return m_pointer;
    }

    Type& operator*()
    {
        return *m_pointer;
    }

    Type const& operator*() const
    {
        return *m_pointer;
    }

    Type** operator&()
    {
        return *m_pointer;
    }

    Type* const* operator&() const
    {
        return *m_pointer;
    }

    operator Type const*() const
    {
        return m_pointer;
    }

    operator Type*()
    {
        return m_pointer;
    }

private:
    Type* m_pointer;
};
