#include "ERModel.h"

ERModel::ERModel()
{
	_componentID = 0;
}

ERModel::~ERModel()
{
// 	for (int i = 0; i < connections.size(); i++)
// 		delete(connections[i]);
// 	connections.clear();
// 
// 	for (int i = 0; i < components.size(); i++)
// 		delete(components[i]);
// 	components.clear();
}

//////////////////////////////////////////////////////////////////////////
//						Choice 1. AddNode								//
//////////////////////////////////////////////////////////////////////////
void ERModel::addNode( string type, string text )
{
	Component* newComponent = new Component();
	ComponentFactory* componentFactory = new ComponentFactory();

	newComponent = static_cast<Component*>(componentFactory->creatComponent(_componentID++, type, text));
  	_components.push_back(newComponent);

	delete(componentFactory);
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
		newComponent = static_cast<Component*>(componentFactory->creatComponent(_componentID++, PARAMETER_CONNECTOR, text));
		_components.push_back(newComponent);

		newConnection = (Connector*) newComponent;	
		// recovery Connector* from Component*
		newConnection->setConnectedNode(sourceNode, destinationNode);	// set which two node be connected.
		_connections.push_back(newConnection);

		sourceNode->connectTo(destinationNode);

		if (checkSetCardinality(sourceNodeID, destinationNodeID))
			setCardinality(sourceNode, destinationNode, text);
	}
	delete(componentFactory);
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

	if((sourceNode->getType() == PARAMETER_ENTITY && desinationNode->getType() == PARAMETER_RELATIONSHIP) || 
		(sourceNode->getType() == PARAMETER_RELATIONSHIP && desinationNode->getType() == PARAMETER_ENTITY))
		return true;
	else
		return false;
}


void ERModel::setCardinality( Component* sourceNode, Component* destinationNode, string cardinality )
{
	int entityID;

	if (sourceNode->getType() == PARAMETER_ENTITY)
	{
		entityID = sourceNode->getID();
		static_cast<NodeRelationship*>(destinationNode)->setEntityCardinality(make_pair(entityID,cardinality));
	}
	else
	{
		entityID = destinationNode->getID();
		static_cast<NodeRelationship*>(sourceNode)->setEntityCardinality(make_pair(entityID,cardinality));
	}
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

	if (_components.size() != 0)
	{
		componentTableString = getComponentDataList(type, _components);

		return componentTableString;
	}
	return PARAMETER_SPACE;
}
string ERModel::getConnectionTable()
{
	string connectionsTableString;

	if (_connections.size() != 0)
	{
		for (int i = 0; i < _connections.size(); i++) {
			connectionsTableString += TEXT_FIVESPACE + integerToString(_connections[i]->getID()) +  TEXT_TWOSPACE + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(_connections[i]->getSourceNodeID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(_connections[i]->getDestinationNodeID()) + TEXT_SPACELINE + TEXT_ENDLINE;
		}
		return connectionsTableString;
	}

	return PARAMETER_SPACE;
}

//////////////////////////////////////////////////////////////////////////
//						Choice 4. SetPrimaryKey							//
//////////////////////////////////////////////////////////////////////////

void ERModel::setPrimaryKey( vector<int> primaryKeys )
{
	Component* attributeNode;
	for( int i = 0; i < primaryKeys.size(); i++)
	{
		attributeNode = searchComponent(primaryKeys[i]);
		static_cast<NodeAttribute*>(attributeNode)->setIsPrimaryKey(true);
	}
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
//						Choice 5. Show ERDiagram						//
//////////////////////////////////////////////////////////////////////////

string ERModel::getERDiagramTable()
{
	string erDiagramRowString;
	string erDiagramTableString;
	string primaryKeyString;
	string notPrimaryKeyString;
	vector<Component*> entitySet = getSpecificTypeComponentSet(PARAMETER_ENTITY, _components);
	vector<Component*> attributeInEntitySet;

	setForeignKey();

	for(int i = 0; i < entitySet.size(); i++)
	{
		erDiagramRowString = TEXT_ONESPACE + entitySet[i]->getText();

		// To fill up with the space
		while (erDiagramRowString.size() < 10)
			erDiagramRowString += TEXT_ONESPACE;

		erDiagramRowString += TEXT_LINESPACE;
		attributeInEntitySet = getSpecificTypeComponentSet(PARAMETER_ATTRIBUTE, entitySet[i]->getConnections());
		erDiagramRowString += getAttributeContents(attributeInEntitySet);
		
		if (!(static_cast<NodeEntity*>(entitySet[i])->getForeignKey()).empty())
		{
			for(int j = 0; j < static_cast<NodeEntity*>(entitySet[i])->getForeignKey().size(); j++)
				erDiagramRowString += searchForeignKey(static_cast<NodeEntity*>(entitySet[i])->getForeignKey()[j]);
		}
		erDiagramRowString += TEXT_ENDLINE;
		erDiagramTableString += erDiagramRowString;
	}
	return erDiagramTableString;
}

string ERModel::getAttributeContents( vector<Component*> attributeSet)
{
	string isPKString;
	string isNotPKString;

	for(int i = 0; i < attributeSet.size(); i++)
	{
		if (static_cast<NodeAttribute*>(attributeSet[i])->getIsPrimaryKey())
			isPKString += attributeSet[i]->getText() + TEXT_GETERDIAGRAM_SPLITER;
		else
			isNotPKString += attributeSet[i]->getText() + TEXT_GETERDIAGRAM_SPLITER;
	}

	// Delete lastest ", " and set format into string
	if (isPKString != PARAMETER_SPACE)
	{
		isPKString = isPKString.substr(0,isPKString.size()-2);
		isPKString = TEXT_GETERDIAGRAM_PK + isPKString + TEXT_GETERDIAGRAM_ENDKEY;			
	}
	if (isNotPKString != PARAMETER_SPACE)
	{
		isNotPKString = isNotPKString.substr(0,isNotPKString.size()-2);
		isNotPKString = TEXT_GETERDIAGRAM_SPLITER + isNotPKString;
	}

	return isPKString + isNotPKString;
}

void ERModel::setForeignKey()
{
	vector<Component*> relationshipSet = getSpecificTypeComponentSet(PARAMETER_RELATIONSHIP, _components);
	vector<int> oneToOneEntityID;	// It store two entity ID which two entity is one to one relationship.
	NodeEntity* setFKEntityNodeFirst;
	NodeEntity* setFKEntityNodeSecond;

	for(int i = 0; i < relationshipSet.size(); i++)
	{
		oneToOneEntityID = oneToOne(static_cast<NodeRelationship*>(relationshipSet[i]));
		// Two entity set the other one as Foreign Key.
		if (!oneToOneEntityID.empty())
		{
			setFKEntityNodeFirst = static_cast<NodeEntity*>(searchComponent(oneToOneEntityID[0]));
// 			setFKEntityNodeSecond = static_cast<NodeEntity*>(searchComponent(oneToOneEntityID[1]));

			setFKEntityNodeFirst->setForeignKey(oneToOneEntityID[1]);
// 			setFKEntityNodeSecond->setForeignKey(oneToOneEntityID[0]);
		}
	}
}

// Return a vector that storing two entityID which is existing one to one relationship.
vector<int> ERModel::oneToOne( NodeRelationship* relationshipNode )
{
	// The entityCardinalitySet of Relationship is a set of store relationship between two entities.
	// The format is (entity, cardinality).
	vector<pair<int,string>> entityCardinalitySet = relationshipNode->getEntityCardinality();
	vector<int> oneToOneEntities;

	if (entityCardinalitySet.size() < PARAMETER_RELATIONSHIPLOWERBOUND)									// Relationship connected the only one entity.
		return oneToOneEntities;
	else
	{
		if (entityCardinalitySet[0].second == "1" && entityCardinalitySet[1].second == "1")				// One to one
		{
			oneToOneEntities.push_back(entityCardinalitySet[0].first);
			oneToOneEntities.push_back(entityCardinalitySet[1].first);
			return oneToOneEntities;
		}
		else																							// One to N or N to one or N to N
			return oneToOneEntities;
	}
}

bool ERModel::checkOneToOne()
{
	vector<Component*> relationshipNode = getSpecificTypeComponentSet(PARAMETER_RELATIONSHIP, _components);

	// The entityCardinalitySet of Relationship is a set of store relationship between two entities.
	// The format is (entity, cardinality).
	vector<pair<int,string>> entityCardinalitySet;

	for(int i = 0; i < relationshipNode.size(); i++){
		entityCardinalitySet = static_cast<NodeRelationship*>(relationshipNode[i])->getEntityCardinality();
		if (entityCardinalitySet.size() >= PARAMETER_RELATIONSHIPLOWERBOUND)								// Check relationship connected two entity at least.
			if (entityCardinalitySet[0].second == "1" && entityCardinalitySet[1].second == "1")				// One to one
				return true;
	}
	return false;
}

string ERModel::searchForeignKey( int foreignKeyEntityID )
{
	Component* foreignKeyEntity = searchComponent(foreignKeyEntityID);
	vector<Component*> attributeSet = getSpecificTypeComponentSet(PARAMETER_ATTRIBUTE, foreignKeyEntity->getConnections());
	string isFKString;

	for(int i = 0; i < attributeSet.size(); i++)
	{
		if (static_cast<NodeAttribute*>(attributeSet[i])->getIsPrimaryKey())
			isFKString += attributeSet[i]->getText() + TEXT_GETERDIAGRAM_SPLITER;
	}

	// Delete lastest ", " and set format into string
	if (isFKString != PARAMETER_SPACE)
	{
		isFKString = isFKString.substr(0,isFKString.size()-2);
		isFKString = TEXT_GETERDIAGRAM_FK + isFKString + TEXT_GETERDIAGRAM_ENDKEY;
	}

	return isFKString;
}

//////////////////////////////////////////////////////////////////////////
//							General Function							//
//////////////////////////////////////////////////////////////////////////

//	Using nodeID to search node, and return pointer of node
Component* ERModel::searchComponent( int searchNodeID )
{
	for( int i = 0; i < _components.size(); i++)
	{
		// Find!
		if (_components[i]->getID() == searchNodeID)
			return _components[i];
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

	for( int i = 0; i < _components.size(); i++)
	{
		// int to string
		intNum << (_components[i]->getID()); // int to stringstream
		intNum >> intToStringNum; // stringstream to string

		// Find!
		if (intToStringNum == searchID && (_components[i]->getType() == searchType || searchType == PARAMETER_ALL))
			return true;

		intNum.clear();
	}
	// Not find!
	return false;
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

	for (int i = 0; i < targetComponents.size(); i++)
	{
		if (targetComponents[i]->getType() == type || type == PARAMETER_ALL)
		{
			ComponentDataList += TEXT_TWOSPACE + targetComponents[i]->getType() + TEXT_SPACELINE
				+ TEXT_TWOSPACE + integerToString(targetComponents[i]->getID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + targetComponents[i]->getText() + TEXT_ENDLINE;
		}
	}	
	return ComponentDataList;
}


vector<Component*> ERModel::getSpecificTypeComponentSet( string type, vector<Component*> targetComponetSet )
{
	vector<Component*> specificTypeComponentSet;

	for( int i = 0; i < targetComponetSet.size(); i++)
	{
		if (targetComponetSet[i]->getType() == type)
			specificTypeComponentSet.push_back(targetComponetSet[i]);
	}

	return specificTypeComponentSet;
}
