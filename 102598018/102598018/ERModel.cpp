#include "ERModel.h"

ERModel::ERModel()
{
	componentID = 0;
}

ERModel::~ERModel()
{
	components.clear();
}

void ERModel::addNode( string type, string text )
{
	Component* newComponent = new Component();
	ComponentFactory* componentFactory = new ComponentFactory();

	newComponent = static_cast<Component*>(componentFactory->creatComponent(componentID++, type, text));
  	components.push_back(newComponent);
}

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

string ERModel::checkConnectionState( Component* sourceNode, Component* destinationNode )
{
	if(!connectedItself(sourceNode, destinationNode))				// Node not connected itself.
	{
		if (connectedTypeCheck(sourceNode, destinationNode))		// Node type is connected with the other node.
		{
			if (!connectedAlready(sourceNode, destinationNode))		// Node hasn't the connection with the other node.
				return TEXT_CONNECTION_FINISH;
			else
				return TEXT_ERROR_MESSAGEBEGIN + integerToString(sourceNode->getID()) + TEXT_CONNECTION_ALREADYCONNECTION + integerToString(destinationNode->getID()) + TEXT_CONNECTION_TEXTEND;
		}
		else
			return TEXT_ERROR_MESSAGEBEGIN + integerToString(destinationNode->getID()) + TEXT_CONNECTION_NOTCONNECTION + integerToString(sourceNode->getID()) + TEXT_CONNECTION_TEXTEND;
	}
	else
		return TEXT_ERROR_MESSAGEBEGIN + integerToString(sourceNode->getID()) + TEXT_CONNECTION_ITSELFCONNECTION;
}

bool ERModel::connectedItself( Component* sourceNode, Component* destinationNode )
{
	if (sourceNode->getID() == destinationNode->getID())
		return true;
	else
		return false;
}

bool ERModel::connectedTypeCheck( Component* sourceNode, Component* destinationNode )
{
	if (sourceNode->canConnectTo(destinationNode))
		return true;
	else
		return false;
}

bool ERModel::connectedAlready( Component* sourceNode, Component* destinationNode)
{
	if (sourceNode->searchConnections(destinationNode->getID()))
		return true;
	else
		return false;
}

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

bool ERModel::searchComponentExist( string searchID , string searchType)
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

string ERModel::integerToString( int targetNum )
{
	stringstream intNum;
	string intToStringNum;
	
	// int to string
	intNum << targetNum; // int to stringstream
	intNum >> intToStringNum; // stringstream to string

	return intToStringNum;
}

string ERModel::getComponentsTable(string type)
{
	string componentTableString;

	if (components.size() != 0)
	{
		for (vector<Component*>::iterator contents = components.begin(); contents != components.end(); ++contents) {
			if (((Component*)*contents)->getType() == type || type == PARAMETER_ALL)
			{
				componentTableString += TEXT_TWOSPACE + ((Component*)*contents)->getType() + TEXT_SPACELINE
					+ TEXT_TWOSPACE + integerToString(((Component*)*contents)->getID()) + TEXT_SPACELINE
					+ TEXT_TWOSPACE + ((Component*)*contents)->getText() + TEXT_ENDLINE;
			}
		}
		return componentTableString;
	}
	return PARAMETER_SPACE;
}

string ERModel::getCheckConnectionStateMessage( int sourceNodeID, int destinationNodeID )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* desinationNode = searchComponent(destinationNodeID);

	return checkConnectionState(sourceNode, desinationNode);
}

std::string ERModel::getConnectionTable()
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

bool ERModel::checkSetCardinality( int sourceNodeID, int destinationNodeID )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* desinationNode = searchComponent(destinationNodeID);

	if((sourceNode->getType() == PARAMETER_ENTITY && desinationNode->getType() == PARAMETER_RELATIONSHOP) || (sourceNode->getType() == PARAMETER_RELATIONSHOP && desinationNode->getType() == PARAMETER_ENTITY))
		return true;
	else
		return false;
}

void ERModel::setPrimaryKeyEntity( int entityNodeID )
{

}

void ERModel::setPrimaryKeyAttribute( string attributeNodeID)
{

}
