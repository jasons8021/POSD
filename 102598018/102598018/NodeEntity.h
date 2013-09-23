#ifndef NODEENTITY
#define NODEENTITY

#define TEXT_NODENUMBEGIN "The node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_ENDTEXT "'."
#define TEXT_CONNECTION_FINISH "CONNECTOK"

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"

#include <vector>
#include "Node.h"

using namespace std;

class NodeEntity : public Node
{
public:
	NodeEntity();
	NodeEntity(int, string);
	~NodeEntity();
	void setPrimaryKey(int);
	vector<int> getPrimaryKey();
	virtual void connectTo(Component*);
	virtual string canConnectTo(Component*);
private:
	vector<int> primaryKeys;
};

#endif