project(neural-networks)

add_definitions(-std=c++14)

set(FILES
    ArrayView.hpp
    NotNull.hpp
    BuilderStorage.cpp
    BuilderStorage.hpp
    BuilderToNodeMaps.hpp
    BinaryNodeBuilder.cpp
    BinaryNodeBuilder.hpp
    BinaryOperationNode.hpp
    BackPropagationNetwork.hpp
    OperationNode.hpp
    ComputationNode.hpp
    BinaryOperationsFactory.hpp
    ConstNode.hpp
    ConstStorageBuilder.hpp
    NodeBuilder.hpp
    NodeTags.hpp
    NetworkBuilder.cpp
    NetworkBuilder.hpp
    VariableNode.hpp
    main.cpp
)
add_executable(${PROJECT_NAME} ${FILES})
