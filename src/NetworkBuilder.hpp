#pragma once

#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "BuilderStorage.hpp"
#include <map>

using BNN_TYPE = float;

struct BinaryNodeBuilder;

template<class Type>
struct ConstNode
{
    ConstNode(Type & value)
        : m_value(value)
    {}

private:
    Type & m_value;
};

template<class Type>
struct ConstStorage
{
    ConstStorage(std::size_t numConsts)
        : m_storage(numConsts)
    {}

    Type & getSingleValueRef()
    {
        return m_storage;
    }

private:
    std::vector<Type> m_storage;
};

struct BackPropagatioNode
{

};

struct BackPropagationNetwork
{
private:
    std::vector<BackPropagatioNode*> m_nodes;
};

struct ForwardNetwork{};

struct NetworkBuilder
{
    NotNull<BinaryNodeBuilder> setRootNode(BinaryNode, std::string const& operation);

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork() const;   // should verify entire tree and return ready to work tree

    std::unique_ptr<ForwardNetwork> buildForwardNetwork();

private:
    std::vector<BinaryNodeBuilder*> getOperationNodesInTopologicalOrder() const;
    std::map<ConstNodeBuilder*, ConstNode<BNN_TYPE>> getConstNodeMap(ConstStorage<BNN_TYPE> & constStorage) const;

    BuilderStorage m_storage;
    BinaryNodeBuilder* m_root; // should be generic operation later // should be able to get topology from here to get forward list to do operations
};
