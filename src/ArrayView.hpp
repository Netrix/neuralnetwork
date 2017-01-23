#pragma once
#include <cassert>
#include <iterator>
#include <vector>
#include <array>
#include <type_traits>

template<class Type>
class ArrayView
{
public:
    using value_type = Type;

    ArrayView(std::nullptr_t) = delete;

    ArrayView(Type & p_value)
        : m_pointerToArray(std::addressof(p_value))
        , m_arraySize(1)
    {}

    ArrayView(Type* dynamicArray, std::size_t arraySize)
        : m_pointerToArray(dynamicArray)
        , m_arraySize(arraySize)
    {
        assert(dynamicArray);
        assert(arraySize > 0);
    }

    ArrayView(ArrayView<Type> const& av)
        : ArrayView(av.m_pointerToArray, av.m_arraySize)
    {
    }

    template<class InnerType,
             typename = std::enable_if<!std::is_const<InnerType>::value>,
             typename = std::enable_if<std::is_const<Type>::value>>
    ArrayView(ArrayView<InnerType> const& av)
        : ArrayView(av.m_pointerToArray, av.m_arraySize)
    {
    }

    // TODO test this constructor
    template<class VectorType, class Allocator, typename = std::enable_if<std::is_const<Type>::value>>
    ArrayView(std::vector<VectorType, Allocator> const& vector)
        : m_pointerToArray(vector.data())
        , m_arraySize(vector.size())
    {
    }

    // TODO test this constructor
    template<class VectorType, class Allocator, typename = std::enable_if<!std::is_const<Type>::value>>
    ArrayView(std::vector<VectorType, Allocator> & vector)
        : m_pointerToArray(vector.data())
        , m_arraySize(vector.size())
    {
    }

    // TODO test this constructor
    template<class VectorType, std::size_t N, typename = std::enable_if<std::is_const<Type>::value>>
    ArrayView(std::array<VectorType, N> const& vector)
        : m_pointerToArray(vector.data())
        , m_arraySize(vector.size())
    {
    }

    // TODO test this constructor
    template<class VectorType, std::size_t N, typename = std::enable_if<!std::is_const<Type>::value>>
    ArrayView(std::array<VectorType, N> & vector)
        : m_pointerToArray(vector.data())
        , m_arraySize(vector.size())
    {
    }

    Type& operator[](std::size_t index)
    {
        assert(index < m_arraySize);
        return m_pointerToArray[index];
    }

    Type const& operator[](std::size_t index) const
    {
        assert(index < m_arraySize);
        return m_pointerToArray[index];
    }

    Type const* data() const
    {
        return m_pointerToArray;
    }

    std::size_t size() const
    {
        return m_arraySize;
    }

    // TODO Test iterator
    // TODO extract reference implementation for random_access_iterator
    // Implementation base on http://zotu.blogspot.com/2010/01/creating-random-access-iterator.html

    // TODO try to replace it with std::vector<Type>::iterator!!
    template<class TypeForIterator>
    class ArrayViewIterator : public std::iterator<std::random_access_iterator_tag, TypeForIterator>
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename std::iterator<std::random_access_iterator_tag, TypeForIterator>::value_type;
        using difference_type = typename std::iterator<std::random_access_iterator_tag, TypeForIterator>::difference_type;
        using reference = typename std::iterator<std::random_access_iterator_tag, TypeForIterator>::reference;
        using pointer = typename std::iterator<std::random_access_iterator_tag, TypeForIterator>::pointer;

        ArrayViewIterator()
            : m_data(nullptr)
        {}

        template<class T2>
        ArrayViewIterator(ArrayViewIterator<T2> const& r)
            : m_data(r.m_data)
        {}

        ArrayViewIterator(pointer data)
            : m_data(data)
        {}

        template<typename T2>
        ArrayViewIterator& operator=(const ArrayViewIterator<T2>& r)
        {
            m_data = &(*r);
            return *this;
        }

        ArrayViewIterator& operator++()  // PREFIX
        {
            ++m_data;
            return *this;
        }

        ArrayViewIterator& operator--()  // PREFIX
        {
            --m_data;
            return *this;
        }

        ArrayViewIterator operator++(int)  // POSTFIX
        {
            return iterator(m_data++);
        }

        ArrayViewIterator operator--(int)  // POSTFIX
        {
            return iterator(m_data--);
        }

        ArrayViewIterator operator+(const difference_type& n) const
        {
            return iterator(m_data + n);
        }

        ArrayViewIterator& operator+=(const difference_type& n)
        {
            m_data += n;
            return *this;
        }

        ArrayViewIterator operator-(const difference_type& n) const
        {
            return iterator(pointer(m_data - n));
        }

        ArrayViewIterator& operator-=(const difference_type& n)
        {
            m_data -= n; return *this;
        }

        reference operator*() const
        {
            return *m_data;
        }

        pointer operator->() const
        {
            return m_data;
        }

        reference operator[](const difference_type& n) const
        {
            return m_data[n];
        }

        template<typename T>
        bool operator==(const ArrayViewIterator<T>& r2)
        {
            return m_data == r2.m_data;
        }

        template<typename T>
        bool operator!=(const ArrayViewIterator<T>& r2)
        {
            return m_data != r2.m_data;
        }

        template<typename T>
        bool operator<(const ArrayViewIterator<T>& r2)
        {
            return m_data < r2.m_data;
        }

        template<typename T>
        bool operator>(const ArrayViewIterator<T>& r2)
        {
            return m_data > r2.m_data;
        }

        template<typename T>
        bool operator<=(const ArrayViewIterator<T>& r2)
        {
            return m_data <= r2.m_data;
        }

        template<typename T>
        bool operator>=(const ArrayViewIterator<T>& r2)
        {
            return m_data >= r2.m_data;
        }

        template<typename T>
        typename ArrayViewIterator<T>::difference_type operator+(const ArrayViewIterator<T>& r2)
        {
            return ArrayViewIterator<T>(m_data + r2.m_data);
        }

        template<typename T>
        typename ArrayViewIterator<T>::difference_type operator-(const ArrayViewIterator<T>& r2)
        {
            return m_data - r2.m_data;
        }

    private:
        TypeForIterator* m_data;
    };

    using const_iterator = ArrayViewIterator<Type const>;
    using iterator = ArrayViewIterator<Type>;

    const_iterator cbegin() const
    {
        return const_iterator(m_pointerToArray);
    }

    const_iterator cend() const
    {
        return const_iterator(m_pointerToArray + m_arraySize);
    }


    const_iterator begin() const
    {
        return const_iterator(m_pointerToArray);
    }

    const_iterator end() const
    {
        return const_iterator(m_pointerToArray + m_arraySize);
    }

    iterator begin()
    {
        return iterator(m_pointerToArray);
    }

    iterator end()
    {
        return iterator(m_pointerToArray + m_arraySize);
    }

    //TODO add reverse iterator!

    template<class InnerType>
    ArrayView<Type> & operator=(ArrayView<InnerType> & src)
    {
        m_arraySize = src.m_arraySize;
        m_pointerToArray = src.m_pointerToArray;
        return *this;
    }

    template<class InnerType>
    ArrayView<Type> & operator=(ArrayView<InnerType> && src)
    {
        m_arraySize = src.m_arraySize;
        m_pointerToArray = src.m_pointerToArray;
        return *this;
    }

    auto operator()(int first, int second)
    {
        size_t begin = first >= 0 ? first : m_arraySize + first;
        size_t end = second >= 0 ? second : m_arraySize + second;
        assert(begin < m_arraySize);
        assert(end <= m_arraySize);
        assert(begin < end);

        return ArrayView<Type>(m_pointerToArray + begin, end - begin);
    }

    friend class ArrayView<Type const>;

private:
    Type* m_pointerToArray;
    std::size_t m_arraySize;
};

template<class Type>
auto begin(ArrayView<Type> && av)
{
    return av.begin();
}
