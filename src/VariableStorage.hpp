#pragma once
#include "ScalarStorage.hpp"

class VariableStorageTag{};
class VariableDeltaStorageTag{};

template<class Type>
using VariableStorage = ScalarStorage<Type, VariableStorageTag>;
template<class Type>
using VariableDeltaStorage = ScalarStorage<Type, VariableDeltaStorageTag>;
