project(neural-networks)

add_definitions(-std=c++14)

set(FILES
    NotNull.hpp
    BuilderStorage.cpp
    BuilderStorage.hpp
    BinaryNodeBuilder.cpp
    BinaryNodeBuilder.hpp
    NodeBuilder.hpp
    NodeTags.hpp
    NetworkBuilder.cpp
    NetworkBuilder.hpp
    main.cpp
)
add_executable(${PROJECT_NAME} ${FILES})
