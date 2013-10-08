#ifndef NODEENTITY_H_
#define NODEENTITY_H_

#define TEXT_NODENUMBEGIN "The node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_ENDTEXT "'."
#define TEXT_CONNECTION_CANCONNECT "CANCONNECT"

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHIP "R"

#include <vector>
#include "Node.h"

using namespace std;

class NodeEntity : public Node
{
public:
	NodeEntity();
	NodeEntity(int, string);
	virtual ~NodeEntity();
	void setForeignKey(int);
	vector<int> getForeignKey();
	void setPrimaryKey(int);
	vector<int> getPrimaryKey();
	void deleteKeys(int);
	virtual void deleteConnectedComponent(int);
	virtual void connectTo(Component*);
	virtual string canConnectTo(Component*);
private:
	vector<int> _primaryKeySet;
	vector<int> _foreignKeySet;
};

#endif