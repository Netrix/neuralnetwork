#pragma once
#include "ScalarStorageBuilder.hpp"

template<class Type>
using VariableStorageBuilder = ScalarStorageBuilder<Type, class VariableStorageBuilderTag>;

