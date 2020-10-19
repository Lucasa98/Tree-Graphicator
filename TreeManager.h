#pragma once

#include <vector>
#include "tree.hpp"
#include "Node.h"

using namespace std;
using namespace aed;

template<typename Q>
class TreeManager{
public:
	bool LoadTree(tree<Q>);
	static vector<Node> GenerateNodes(tree<Q>);
};
