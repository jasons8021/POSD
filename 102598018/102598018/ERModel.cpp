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

string ERModel::addConnection( int sourceNodeID, int destinationNodeID )
{
	Component* sourceNode = new Component();
	Component* destinationNode = new Component();

	Component* newComponent = new Component();
	Connector* newConnection = new Connector();
	ComponentFactory* componentFactory = new ComponentFactory();

	sourceNode = searchComponent(sourceNodeID);
	destinationNode = searchComponent(destinationNodeID);

	if(!connectedItself(sourceNode, destinationNode))				// Node not connected itself.
	{
		if (connectedTypeCheck(sourceNode, destinationNode))		// Node type is connected with the other node.
		{
			if (!connectedAlready(sourceNode, destinationNode))		// Node hasn't the connection with the other node.
			{
				newComponent = static_cast<Component*>(componentFactory->creatComponent(componentID++, PARAMETER_CONNECTOR, PARAMETER_SPACE));
				components.push_back(newComponent);

				newConnection = (Connector*) newComponent;						// recovery Connector* from Component*
				newConnection->setConnectedNode(sourceNode, destinationNode);	// set which two node be connected.
				connections.push_back(newConnection);

				sourceNode->connectTo(destinationNode);

				return TEXT_CONNECTION_FINISH;
			}
			else
				return TEXT_CONNECTION_TEXTBEGIN + integerToString(sourceNode->getID()) + TEXT_CONNECTION_ALREADYCONNECTION + integerToString(destinationNode->getID()) + TEXT_CONNECTION_TEXTEND;
		}
		else
			return TEXT_CONNECTION_TEXTBEGIN + integerToString(destinationNode->getID()) + TEXT_CONNECTION_NOTCONNECTION + integerToString(sourceNode->getID()) + TEXT_CONNECTION_TEXTEND;
		
	}
	else
		return TEXT_CONNECTION_TEXTBEGIN + integerToString(sourceNode->getID()) + TEXT_CONNECTION_ITSELFCONNECTION;

}

void ERModel::getTable()
{

}

vector<Component*> ERModel::getComponents()
{
	return components;
}

bool ERModel::searchComponentExist( string searchID )
{
	stringstream intNum;
	string intToStringNum;

	for( int i = 0; i < components.size(); i++)
	{
		// int to string
		intNum << (components[i]->getID()); // int to stringstream
		intNum >> intToStringNum; // stringstream to string

		// Find!
		if (intToStringNum == searchID)
			return true;

		intNum.clear();
	}
	// Not find!
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

std::string ERModel::integerToString( int targetNum )
{
	stringstream intNum;
	string intToStringNum;
	
	// int to string
	intNum << targetNum; // int to stringstream
	intNum >> intToStringNum; // stringstream to string

	return intToStringNum;
}

vector<Connector*> ERModel::getConnections()
{
	return connections;
}
