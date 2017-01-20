#pragma once
#include "ScalarStorage.hpp"

struct ConstStorageTag{};

template<class Type>
using ConstStorage = ScalarStorage<Type, ConstStorageTag>;

