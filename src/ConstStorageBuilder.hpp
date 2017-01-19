#pragma once
#include "ScalarStorageBuilder.hpp"

template<class Type>
using ConstStorageBuilder = ScalarStorageBuilder<Type, class ClassStorageBuilderTag>;

