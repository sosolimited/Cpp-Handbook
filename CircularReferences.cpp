
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

class GraphNode : public std::enable_shared_from_this<GraphNode>
{
public:
	void append( const std::shared_ptr<GraphNode> &node );
	void remove( GraphNode *node );

private:
	// Weak pointer to parent, since having children shouldn't prevent it from
	// falling out of scope.
	std::weak_ptr<GraphNode>								parent;
	// Strong pointers to children, since they must exist as long as the parent.
	std::vector<std::shared_ptr<GraphNode>> children;

	void setParent( const std::weak_ptr<GraphNode> &node );
};

using namespace std;

//
//
//
void GraphNode::append( const shared_ptr<GraphNode> &node )
{
	children.push_back( node );
	node->setParent( shared_from_this() );
}

void GraphNode::setParent( const weak_ptr<GraphNode> &node )
{
	auto previous_parent = parent.lock();
	if( previous_parent )
	{
		previous_parent->remove( this );
	}
	parent = node;
}

void GraphNode::remove( GraphNode *node )
{
	if( node->parent.lock() == shared_from_this() )
	{
		node->parent.reset();
		// remove child from children collection
		// remove_if pushes things that match the predicate to the end of the vector.
		// We then erase from the start of those things to the end of the vector.
		children.erase( std::remove_if( children.begin(), children.end(), [node] ( const shared_ptr<GraphNode> &child ) {
			return child.get() == node;
		} ), children.end() );
	}
}

int main(int argc, char const *argv[])
{

	return 0;
}
