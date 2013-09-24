#include "ERModel.h"

ERModel::ERModel()
{
	componentID = 0;
}

ERModel::~ERModel()
{
	components.clear();
}

//////////////////////////////////////////////////////////////////////////
//						Choice 1. AddNode								//
//////////////////////////////////////////////////////////////////////////
void ERModel::addNode( string type, string text )
{
	Component* newComponent = new Component();
	ComponentFactory* componentFactory = new ComponentFactory();

	newComponent = static_cast<Component*>(componentFactory->creatComponent(componentID++, type, text));
  	components.push_back(newComponent);
}

//////////////////////////////////////////////////////////////////////////
//						Choice 2. AddConnection							//
//////////////////////////////////////////////////////////////////////////
void ERModel::addConnection( int sourceNodeID, int destinationNodeID, string text )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* destinationNode = searchComponent(destinationNodeID);

	Component* newComponent = new Component();
	Connector* newConnection = new Connector();
	ComponentFactory* componentFactory = new ComponentFactory();

	if (checkConnectionState(sourceNode, destinationNode) == TEXT_CONNECTION_FINISH)
	{
		newComponent = static_cast<Component*>(componentFactory->creatComponent(componentID++, PARAMETER_CONNECTOR, text));
		components.push_back(newComponent);

		newConnection = (Connector*) newComponent;						// recovery Connector* from Component*
		newConnection->setConnectedNode(sourceNode, destinationNode);	// set which two node be connected.
		connections.push_back(newConnection);

		sourceNode->connectTo(destinationNode);
	}
}

//	Check Connection hasn't any error. If it has, return error message.
string ERModel::checkConnectionState( Component* sourceNode, Component* destinationNode )
{
	return sourceNode->canConnectTo(destinationNode);
}

//	The method provides to textUI to get connection error message.
string ERModel::getCheckConnectionStateMessage( int sourceNodeID, int destinationNodeID )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* desinationNode = searchComponent(destinationNodeID);

	return checkConnectionState(sourceNode, desinationNode);
}

//	The method provide to textUI to check whether set cardinality or not.
bool ERModel::checkSetCardinality( int sourceNodeID, int destinationNodeID )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* desinationNode = searchComponent(destinationNodeID);

	if((sourceNode->getType() == PARAMETER_ENTITY && desinationNode->getType() == PARAMETER_RELATIONSHOP) || 
		(sourceNode->getType() == PARAMETER_RELATIONSHOP && desinationNode->getType() == PARAMETER_ENTITY))
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
//						Choice 3. GetTable								//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	The method can search specific tpye or all type , 
//	and return the Component vector's data list (string).
//////////////////////////////////////////////////////////////////////////
string ERModel::getComponentsTable(string type)
{
	string componentTableString;

	if (components.size() != 0)
	{
		componentTableString = getComponentDataList(type, components);

		return componentTableString;
	}
	return PARAMETER_SPACE;
}
string ERModel::getConnectionTable()
{
	string connectionsTableString;

	if (connections.size() != 0)
	{
		for (vector<Connector*>::iterator contents = connections.begin(); contents != connections.end(); ++contents) {
			connectionsTableString += TEXT_FIVESPACE + integerToString(((Connector*)*contents)->getID()) +  TEXT_TWOSPACE + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(((Connector*)*contents)->getSourceNodeID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(((Connector*)*contents)->getDestinationNodeID()) + TEXT_SPACELINE + TEXT_ENDLINE;
		}
		return connectionsTableString;
	}

	return PARAMETER_SPACE;
}

//////////////////////////////////////////////////////////////////////////
//						Choice 4. SetPrimaryKey							//
//////////////////////////////////////////////////////////////////////////

void ERModel::setPrimaryKey( int entityNodeID, vector<int> primaryKeys )
{
	Component* entityNode = searchComponent(entityNodeID);
	static_cast<NodeEntity*>(entityNode);
	for (int i = 0; i < primaryKeys.size(); i++)
		static_cast<NodeEntity*>(entityNode)->setPrimaryKey(primaryKeys[i]);
}

string ERModel::searchAttributeOfEntity( int entityID )
{
	string attributeOfEntityDataList;
	Component* specificEntityNode = searchComponent(entityID);

	return getComponentDataList(PARAMETER_ATTRIBUTE, specificEntityNode->getConnections());
}

bool ERModel::searchEntityConnection( int entityID, int targetNodeID, string targetType)
{
	Component* entityNode = searchComponent(entityID);
	
	return searchComponentConnection(targetNodeID, targetType, entityNode->getConnections());
}


//////////////////////////////////////////////////////////////////////////
//							General Function							//
//////////////////////////////////////////////////////////////////////////

//	Using nodeID to search node, and return pointer of node
Component* ERModel::searchComponent( int searchNodeID )
{
	for( int i = 0; i < components.size(); i++)
	{
		// Find!
		if (components[i]->getID() == searchNodeID)
			return components[i];
	}
	// Not find!
	return NULL;
}

//	The method is searching the nodeID in connections of the target component. 
bool ERModel::searchComponentConnection( int searchNodeID, string searchType,vector<Component*> targetComponent )
{
	for( int i = 0; i < targetComponent.size(); i++)
	{
		// Find!
		if (targetComponent[i]->getID() == searchNodeID && targetComponent[i]->getType() == searchType)
			return true;
	}
	// Not find!
	return NULL;
}

//	The method provides to textUI to check the component is exist.
bool ERModel::searchComponentExist( string searchID, string searchType)
{
	stringstream intNum;
	string intToStringNum;

	for( int i = 0; i < components.size(); i++)
	{
		// int to string
		intNum << (components[i]->getID()); // int to stringstream
		intNum >> intToStringNum; // stringstream to string

		// Find!
		if (intToStringNum == searchID && (components[i]->getType() == searchType || searchType == PARAMETER_ALL))
			return true;

		intNum.clear();
	}
	// Not find!
	return false;
}

bool ERModel::searchComponentExist( int searchID, string searchType )
{
	return searchComponentExist(integerToString(searchID), searchType);
}

//	The method provides that typecast integer to string.
string ERModel::integerToString( int targetNum )
{
	stringstream intNum;
	string intToStringNum;

	// int to string
	intNum << targetNum; // int to stringstream
	intNum >> intToStringNum; // stringstream to string

	return intToStringNum;
}

//////////////////////////////////////////////////////////////////////////
//	The method can search specific type from specific vector of component,
//	and return dataList of the specific vector of component.
//////////////////////////////////////////////////////////////////////////
string ERModel::getComponentDataList( string type, vector<Component*> targetComponents ) 
{
	string ComponentDataList;

	for (vector<Component*>::iterator contents = targetComponents.begin(); contents != targetComponents.end(); ++contents) 
	{
		if (((Component*)*contents)->getType() == type || type == PARAMETER_ALL)
		{
			ComponentDataList += TEXT_TWOSPACE + ((Component*)*contents)->getType() + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(((Component*)*contents)->getID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + ((Component*)*contents)->getText() + TEXT_ENDLINE;
		}
	}	
	return ComponentDataList;
}
