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

    friend bool operator==(NotNull<Type> lhs, Type* rhs)
    {
        return lhs.m_pointer == rhs;
    }

    friend bool operator==(Type* lhs, NotNull<Type> rhs)
    {
        return lhs == rhs.m_pointer;
    }

private:
    Type* m_pointer;
};

