#include "ERModel.h"

ERModel::ERModel()
{
	_componentID = 0;
}

ERModel::~ERModel()
{
	for(int i = 0; i < _components.size(); i++)
		delete _components[i];
	_components.clear();
	_connections.clear();
}

//////////////////////////////////////////////////////////////////////////
//							AddNode										//
//////////////////////////////////////////////////////////////////////////

//	componentID遞增的情況下使用
int ERModel::addNode( string type, string text )
{
	return addNode(_componentID++, type, text);
}

//	指定componentID的情況使用，eg:undo、redo，並回傳componentID
int ERModel::addNode( int componentID, string type, string text )
{
	ComponentFactory* componentFactory = new ComponentFactory();
	Component* newComponent = static_cast<Component*>(componentFactory->creatComponent(componentID, type, text));

	_components.push_back(newComponent);
	delete componentFactory;

	return newComponent->getID();
}

//////////////////////////////////////////////////////////////////////////
//							AddConnection								//
//////////////////////////////////////////////////////////////////////////

int ERModel::addConnection( int sourceNodeID, int destinationNodeID, string text )
{
	return addConnection(_componentID++, sourceNodeID, destinationNodeID, text);
}

int ERModel::addConnection( int componentID, int sourceNodeID, int destinationNodeID, string text )
{
	Component* sourceNode = searchComponent(sourceNodeID);
	Component* destinationNode = searchComponent(destinationNodeID);

	Component* newConnection;
	ComponentFactory* componentFactory = new ComponentFactory();

	if (checkConnectionState(sourceNode, destinationNode) == TEXT_CONNECTION_CANCONNECT)
	{
		newConnection = static_cast<Component*>(componentFactory->creatComponent(componentID, PARAMETER_CONNECTOR, text));
		_components.push_back(newConnection);

		static_cast<Connector*>(newConnection)->setConnectedNode(sourceNode, destinationNode);
		_connections.push_back(newConnection);

		sourceNode->connectTo(destinationNode);

		if (checkSetCardinality(sourceNodeID, destinationNodeID))
			setCardinality(sourceNode, destinationNode, text);
	}
	delete componentFactory;

	return newConnection->getID();
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

	if (sourceNode->getType() == PARAMETER_ENTITY)			// sourceNode is entity, and destinationNode is relationship
	{
		entityID = sourceNode->getID();
		static_cast<NodeRelationship*>(destinationNode)->setEntityCardinality(make_pair(entityID,cardinality));
	}
	else													// destinationNode is entity, and sourceNode is relationship
	{
		entityID = destinationNode->getID();
		static_cast<NodeRelationship*>(sourceNode)->setEntityCardinality(make_pair(entityID,cardinality));
	}
}


//////////////////////////////////////////////////////////////////////////
//							GetTable									//
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
	return PARAMETER_NULL;
}
string ERModel::getConnectionTable()
{
	string connectionsTableString;

	if (_connections.size() != 0)
	{
		for (int i = 0; i < _connections.size(); i++) {
			connectionsTableString += TEXT_FIVESPACE + Toolkit::integerToString(_connections[i]->getID()) +  TEXT_TWOSPACE + TEXT_SPACELINE
				+ TEXT_TWOSPACE + Toolkit::integerToString(static_cast<Connector*>(_connections[i])->getSourceNodeID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + Toolkit::integerToString(static_cast<Connector*>(_connections[i])->getDestinationNodeID()) + TEXT_SPACELINE + TEXT_ENDLINE;
		}
		return connectionsTableString;
	}

	return PARAMETER_NULL;
}

//////////////////////////////////////////////////////////////////////////
//							SetPrimaryKey								//
//////////////////////////////////////////////////////////////////////////

void ERModel::setPrimaryKey( int entityID, vector<int> primaryKeys )
{
	NodeEntity* entityNode = static_cast<NodeEntity*>(searchComponent(entityID));
	Component* attributeNode;
	for( int i = 0; i < primaryKeys.size(); i++)
	{
		attributeNode = searchComponent(primaryKeys[i]);
		static_cast<NodeAttribute*>(attributeNode)->setIsPrimaryKey(true);
		entityNode->setPrimaryKey(attributeNode->getID());
	}
}

void ERModel::reBuildPrimaryKeyFromAttribute( int attributeID, int entityID )
{
	NodeAttribute* attributeNode = static_cast<NodeAttribute*>(searchComponent(attributeID));
	NodeEntity* entityNode = static_cast<NodeEntity*>(searchComponent(entityID));

	attributeNode->setIsPrimaryKey(true);
	entityNode->setPrimaryKey(attributeID);
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
//							Show ERDiagram								//
//////////////////////////////////////////////////////////////////////////

string ERModel::getERDiagramTable()
{
	string erDiagramRowString;
	string erDiagramTableString;
	string primaryKeyString;
	string notPrimaryKeyString;
	vector<Component*> entitySet = searchSpecificTypeComponentSet(PARAMETER_ENTITY, _components);
	vector<Component*> attributeInEntitySet;

	setForeignKey();

	for(int i = 0; i < entitySet.size(); i++)
	{
		erDiagramRowString = TEXT_ONESPACE + entitySet[i]->getText();

		// To fill up with the space
		while (erDiagramRowString.size() < 10)
			erDiagramRowString += TEXT_ONESPACE;

		erDiagramRowString += TEXT_LINESPACE;
		attributeInEntitySet = searchSpecificTypeComponentSet(PARAMETER_ATTRIBUTE, entitySet[i]->getConnections());
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
			isPKString += attributeSet[i]->getText() + TEXT_COMMASPACE;
		else
			isNotPKString += attributeSet[i]->getText() + TEXT_COMMASPACE;
	}

	// Delete lastest ", " and set format into string
	if (isPKString != PARAMETER_NULL)
	{
		isPKString = isPKString.substr(0,isPKString.size()-2);
		isPKString = TEXT_GETERDIAGRAM_PK + isPKString + TEXT_GETERDIAGRAM_ENDKEY;			
	}
	if (isNotPKString != PARAMETER_NULL)
	{
		isNotPKString = isNotPKString.substr(0,isNotPKString.size()-2);
		isNotPKString = TEXT_COMMASPACE + isNotPKString;
	}

	return isPKString + isNotPKString;
}

void ERModel::setForeignKey()
{
	vector<Component*> relationshipSet = searchSpecificTypeComponentSet(PARAMETER_RELATIONSHIP, _components);
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
	vector<Component*> relationshipNode = searchSpecificTypeComponentSet(PARAMETER_RELATIONSHIP, _components);

	// The entityCardinalitySet is a set of relationship between two entities.
	// The pair format is (entity, cardinality).
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
	vector<Component*> attributeSet = searchSpecificTypeComponentSet(PARAMETER_ATTRIBUTE, foreignKeyEntity->getConnections());
	string isFKString;

	for(int i = 0; i < attributeSet.size(); i++)
	{
		if (static_cast<NodeAttribute*>(attributeSet[i])->getIsPrimaryKey())
			isFKString += attributeSet[i]->getText() + TEXT_COMMASPACE;
	}

	// Delete lastest ", " and set format into string
	if (isFKString != PARAMETER_NULL)
	{
		isFKString = isFKString.substr(0,isFKString.size()-2);
		isFKString = TEXT_GETERDIAGRAM_FK + isFKString + TEXT_GETERDIAGRAM_ENDKEY;
	}

	return isFKString;
}

//////////////////////////////////////////////////////////////////////////
//							Load/Save									//
//////////////////////////////////////////////////////////////////////////

void ERModel::loadERDiagram( string fileName )
{
	ifstream inputERDiagramFile;
	inputERDiagramFile.open(fileName);

	//	Get all text in file.
	string erDiagramText((istreambuf_iterator<char>(inputERDiagramFile)),istreambuf_iterator<char>());
	inputERDiagramFile.close();

	recoveryFile(classifyInputFile(erDiagramText));
	
}

vector<vector<string>> ERModel::classifyInputFile( string fileText )
{
	vector<string> splitFileText;
	vector<string> splitComponentsSet;
	vector<string> splitConnectionsSet;
	vector<string> splitPrimaryKeysSet;
	vector<vector<string>> splitResultSet;

	bool firstSpace = false, secondSpace = false;

	splitFileText = Toolkit::splitFunction(fileText,TEXT_ENDLINE);
	for(int i = 0; splitFileText.size() > i; i++)
	{
		if (splitFileText[i] == PARAMETER_NULL && !firstSpace)
			firstSpace = true;
		else if (splitFileText[i] == PARAMETER_NULL && firstSpace)
			secondSpace = true;

		if (splitFileText[i] != PARAMETER_NULL)
		{
			if (!firstSpace)
				splitComponentsSet.push_back(splitFileText[i]);
			else if(firstSpace && !secondSpace)
				splitConnectionsSet.push_back(splitFileText[i]);
			else if (secondSpace)
				splitPrimaryKeysSet.push_back(splitFileText[i]);
		}
	}
	splitResultSet.push_back(splitComponentsSet);
	splitResultSet.push_back(splitConnectionsSet);
	splitResultSet.push_back(splitPrimaryKeysSet);

	return splitResultSet;
}

//	Rebuild input file setting. FileSet's vector[0] is components set, vector[1] is connections set and vector[2] is primary keys set.
void ERModel::recoveryFile( vector<vector<string>> fileSet )
{
 	recoveryAllComponent(fileSet[0], fileSet[1]);
 	recoveryPrimaryKey(fileSet[2]);
}

void ERModel::recoveryAllComponent( vector<string> componentsSet, vector<string> connectionsSet )
{
	vector<string> componentData;
	
	int connectionSetCount = 0;
	for(int i = 0; i < componentsSet.size(); i++)
	{
		componentData = Toolkit::splitFunction(componentsSet[i], TEXT_COMMASPACE);

		if ( componentData[0] == PARAMETER_CONNECTOR && componentData.size() > 1 )			//	Connection with Cardinality
			connectionSetCount = recoveryConnection(connectionsSet, connectionSetCount, componentData[1]);
		else if ( componentData[0] == PARAMETER_CONNECTOR )									//	Connection with no Cardinality
			connectionSetCount = recoveryConnection(connectionsSet, connectionSetCount, PARAMETER_NULL);
		else																				//	Component of Attribute, Entity and Relationship
 			addNode(componentData[0],componentData[1]);
	}
}

int ERModel::recoveryConnection( vector<string> connectionsSet, int connectionCount, string connectionText)
{
	vector<string> connectionData;

	// splitter.first is componentID (or Entity Node ID)
	connectionData = splitter(connectionsSet[connectionCount]).second;
	addConnection(atoi(connectionData[0].c_str()),atoi(connectionData[1].c_str()),connectionText);
	connectionCount += 1;

	return connectionCount;
}

void ERModel::recoveryPrimaryKey( vector<string> primaryKeysSet )
{
	//	primaryKeysSet is composed by entityNodeID, primarykey set.
	pair<string,vector<string>> splitPrimaryKey;
	vector<int> primaryKeyData;

	for (int i = 0; i < primaryKeysSet.size(); i++)
	{
		primaryKeyData.clear();

		//	splitter.first is Entity Node ID (or componentID in recoveryConnection function)
		//	splitter.second is primaryKey set.
		splitPrimaryKey = splitter(primaryKeysSet[i]);
		for (int j = 0; j < splitPrimaryKey.second.size(); j++)
			primaryKeyData.push_back(atoi(splitPrimaryKey.second[j].c_str()));

		setPrimaryKey(atoi(splitPrimaryKey.first.c_str()), primaryKeyData);
	}
}

pair<string,vector<string>> ERModel::splitter( string splitRowData )
{
	vector<string> splitBySpace;
	vector<string> splitResult;

	splitBySpace = Toolkit::splitFunction(splitRowData, TEXT_ONESPACE);
	splitResult = Toolkit::splitFunction(splitBySpace[1], COMMA);

	return make_pair(splitBySpace[0],splitResult);
}

void ERModel::saveERDiagram( string fileName )
{
	ofstream outputERDiagramFile;
	outputERDiagramFile.open(fileName);

	if (!outputERDiagramFile.is_open())
	{
		creatFilePath(fileName);
		outputERDiagramFile.open(fileName);
	}

	outputERDiagramFile << saveComponentTable();
	outputERDiagramFile << TEXT_ENDLINE;
	outputERDiagramFile << saveConnectionTable();
	outputERDiagramFile << TEXT_ENDLINE;
	outputERDiagramFile << savePrimaryKeyTable();

	outputERDiagramFile.close();
}

void ERModel::creatFilePath( string fileName )
{
	string filePath;
	vector<string> splitterFilePath;

	splitterFilePath = Toolkit::splitFunction(fileName,SPLITTERBYBACKSLASH);

	// Final part of splitterFilePath is file name.
	for (int i = 0; i < (splitterFilePath.size()-1); i++)
	{
		if (splitterFilePath[i] != PARAMETER_NULL)
			filePath += splitterFilePath[i] + SPLITTERBYBACKSLASH;
	}
	_mkdir(filePath.c_str());
}

string ERModel::saveComponentTable() 
{
	string componentTableString;

	for (int i = 0; i < _components.size(); i++)
	{
		if (_components[i]->getText() == PARAMETER_NULL)
			componentTableString += _components[i]->getType() + TEXT_ENDLINE;
		else
			componentTableString += _components[i]->getType() + TEXT_COMMASPACE + _components[i]->getText() + TEXT_ENDLINE;
	}

	return componentTableString;
}

string ERModel::saveConnectionTable() 
{
	string connectionTableString;

	for (int i = 0; i < _connections.size(); i++) 
	{
		connectionTableString += Toolkit::integerToString(_connections[i]->getID()) +  TEXT_ONESPACE 
			+ Toolkit::integerToString(static_cast<Connector*>(_connections[i])->getSourceNodeID()) + COMMA
			+ Toolkit::integerToString(static_cast<Connector*>(_connections[i])->getDestinationNodeID()) + TEXT_ENDLINE;
	}
	return connectionTableString;
}

string ERModel::savePrimaryKeyTable() 
{
	string primaryKeyTableString;
	// To find all components of entity.
	vector<Component*> allEntityNode = searchSpecificTypeComponentSet(PARAMETER_ENTITY, _components);
	vector<int> pkofEntityNode;

	for (int i = 0; i < allEntityNode.size(); i++) 
	{
		pkofEntityNode = static_cast<NodeEntity*>(allEntityNode[i])->getPrimaryKey();
		if (!pkofEntityNode.empty())					// If the PK in entity node is not empty, output them. 
		{
			primaryKeyTableString += Toolkit::integerToString(allEntityNode[i]->getID()) + TEXT_ONESPACE; 
			for (int j = 0; j < pkofEntityNode.size(); j++)
			{
				if ( j == pkofEntityNode.size()-1 )		// Final PK
					primaryKeyTableString += Toolkit::integerToString(pkofEntityNode[j]);
				else
					primaryKeyTableString += Toolkit::integerToString(pkofEntityNode[j]) + COMMA;
			}
		}
		primaryKeyTableString += TEXT_ENDLINE;
	}
	return primaryKeyTableString;
}

//////////////////////////////////////////////////////////////////////////
//							Delete Node									//
//////////////////////////////////////////////////////////////////////////

void ERModel::deleteFunction( int componentID )
{
	Component* delComponent = searchComponent(componentID);

	if (delComponent->getType() != PARAMETER_CONNECTOR)
		deleteComponent(delComponent);
	else
		deleteConnection(delComponent);
}

void ERModel::deleteComponent( Component* delComponent )
{
	//	與要刪除的Component有關連的Component
	vector<Component*> relatedComponents = searchRelatedComponent(delComponent->getID());
	//	與要刪除的Component有關連的Connector ID
	vector<Component*> relatedConnectors = searchConnection(delComponent->getID());
	int relatedConnectionsEndIndex = relatedConnectors.size() - 1;
	int delID;

	//	走訪每個有關連的Component，並刪除其中connection的delComponent
	for (int i = 0; i < relatedComponents.size(); i++)
		relatedComponents[i]->deleteConnectedComponent(delComponent->getID());
	
	//	刪除Components中的Connector
	while(relatedConnectors.size() > 0)
	{
		delID = relatedConnectors[relatedConnectionsEndIndex]->getID();
		deleteTableSet(delID, _components, PARAMETER_COMPONENTSTABLE);
		deleteTableSet(delID, _connections, PARAMETER_CONNECTIONSTABLE);

		relatedConnectors.pop_back();
		relatedConnectionsEndIndex = relatedConnectors.size() - 1;
	}
	deleteTableSet(delComponent->getID(), _components, PARAMETER_COMPONENTSTABLE);
}

void ERModel::deleteConnection( Component* delComponent )
{
	Connector* delConnector = static_cast<Connector*>(delComponent);
	Component* sourceNode = searchComponent(delConnector->getSourceNodeID());
	Component* destinationNode = searchComponent(delConnector->getDestinationNodeID());

	sourceNode->deleteConnectedComponent(delConnector->getDestinationNodeID());
	destinationNode->deleteConnectedComponent(delConnector->getSourceNodeID());

	deleteTableSet(delComponent->getID(), _components, PARAMETER_COMPONENTSTABLE);
	deleteTableSet(delComponent->getID(), _connections, PARAMETER_CONNECTIONSTABLE);
}

void ERModel::deleteTableSet( int delID, vector<Component*> targetTableSet, int tableType )
{
	for(int i = 0; i < targetTableSet.size(); i++)
	{
		if (delID == targetTableSet[i]->getID())
		{
			switch(tableType)
			{
			case PARAMETER_COMPONENTSTABLE:
				_components.erase(_components.begin()+i);
				break;
			case PARAMETER_CONNECTIONSTABLE:
				_connections.erase(_connections.begin()+i);
				break;
			default:
				break;
			}
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//							Command Pattern								//
//////////////////////////////////////////////////////////////////////////

void ERModel::addNodeCmd( string type, string text )
{
	_cmdManager.execute(new AddComponentCmd(this, type, text));
}

void ERModel::addConnectionCmd( int sourceNodeID, int destinationNodeID, string text )
{
	_cmdManager.execute(new ConnectComponentsCmd(this, sourceNodeID, destinationNodeID, text));
}

void ERModel::deleteCmd( int delComponentID )
{
	_cmdManager.execute(new DeleteComponentCmd(this, delComponentID));
}

bool ERModel::undoCmd()
{
	return _cmdManager.undo();
}

bool ERModel::redoCmd()
{
	return _cmdManager.redo();
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

// Search components which is specific type in target component set, and return the specific components in target component set.
vector<Component*> ERModel::searchSpecificTypeComponentSet( string type, vector<Component*> targetComponetSet )
{
	vector<Component*> specificTypeComponentSet;

	for( int i = 0; i < targetComponetSet.size(); i++)
	{
		if (targetComponetSet[i]->getType() == type)
			specificTypeComponentSet.push_back(targetComponetSet[i]);
	}

	return specificTypeComponentSet;
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
				+ TEXT_TWOSPACE + Toolkit::integerToString(targetComponents[i]->getID()) + TEXT_SPACELINE
				+ TEXT_TWOSPACE + targetComponents[i]->getText() + TEXT_ENDLINE;
		}
	}	
	return ComponentDataList;
}

//	尋找與ComponentID有關連的Connection
vector<Component*> ERModel::searchConnection( int searchID )
{
	vector<Component*> resultSet;

	for (int i = 0; i < _connections.size(); i++)
	{
		if (static_cast<Connector*>(_connections[i])->getSourceNodeID() == searchID ||
			static_cast<Connector*>(_connections[i])->getDestinationNodeID() == searchID)
			resultSet.push_back(_connections[i]);
	}

	return resultSet;
}

vector<Component*> ERModel::searchRelatedComponent( int searchID )
{
	vector<Component*> resultSet;

	for (int i = 0; i < _connections.size(); i++)
	{
		if (static_cast<Connector*>(_connections[i])->getSourceNodeID() == searchID)
			resultSet.push_back(searchComponent(static_cast<Connector*>(_connections[i])->getDestinationNodeID()));
		else if(static_cast<Connector*>(_connections[i])->getDestinationNodeID() == searchID)
			resultSet.push_back(searchComponent(static_cast<Connector*>(_connections[i])->getSourceNodeID()));
	}

	return resultSet;
}

int ERModel::getComponentTableSize()
{
	return _components.size();
}

int ERModel::getConnectionTableSize()
{
	return _connections.size();
}

void ERModel::setComponentID( int componentID )
{
	_componentID = componentID;
}

int ERModel::getComponentID()
{
	return _componentID;
}