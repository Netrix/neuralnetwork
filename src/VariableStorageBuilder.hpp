#pragma once
#include "ScalarStorageBuilder.hpp"
#include "VariableStorage.hpp"

template<class Type>
using VariableStorageBuilder = ScalarStorageBuilder<Type, VariableStorageTag>;

