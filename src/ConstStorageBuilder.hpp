#pragma once
#include "ScalarStorageBuilder.hpp"
#include "ConstStorage.hpp"

template<class Type>
using ConstStorageBuilder = ScalarStorageBuilder<Type, ConstStorageTag>;

