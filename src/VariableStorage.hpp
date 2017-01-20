#pragma once
#include "ScalarStorage.hpp"

class VariableStorageTag{};

template<class Type>
using VariableStorage = ScalarStorage<Type, VariableStorageTag>;

