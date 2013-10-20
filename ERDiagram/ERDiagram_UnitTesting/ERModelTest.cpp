#include "ERModelTest.h"

void ERModelTest::SetUp()
{
	_erModel = new ERModel();
	_erModel->setComponentID(0);
	_erModel->setIsModify(false);

	const int testNum = 10;
	const string testType[testNum] = {"A", "E", "R", "A", "A", "A", "E", "R", "E", "E"};
	const string testText[testNum] = {"A0", "E1", "R2", "A3", "A4", "A5", "E6", "R7", "E8", "E9"};

	// �s�Wcomponent�ivector��
	for (int i = 0; i < testNum; i++)
	{
		if (testType[i] == PARAMETER_ATTRIBUTE)
			_erModel->_components.push_back(new NodeAttribute(i, testText[i]));
		else if (testType[i] == PARAMETER_ENTITY)
			_erModel->_components.push_back(new NodeEntity(i, testText[i]));
		else
			_erModel->_components.push_back(new NodeRelationship(i, testText[i]));
	}
}

void ERModelTest::TearDown()
{
	delete _erModel;
}

TEST_F(ERModelTest, addNode){
	_erModel->_components.clear();
	const int testNum = 7;
	const int testCorrectNum = 4;
	const string testType[testNum] = {"A", "E", "R", "C", "T", " A", "A E"};
	const string testText[testNum] = {"A0", "E1", "R2", "C3", "T4", " A5", "A E6"};
	
	// ���T����Jtype
	for (int i = 0; i < testCorrectNum; i++)
		EXPECT_EQ(i,_erModel->addNode(i,testType[i],testText[i]));

	// ���~����J
	EXPECT_EQ(PARAMETER_ISERROR,_erModel->addNode(5,testType[5],testText[5]));
	EXPECT_EQ(PARAMETER_ISERROR,_erModel->addNode(6,testType[6],testText[6]));
}

TEST_F(ERModelTest, addConnection){

	// Attribute�MEntity�۳s
	EXPECT_EQ(10, _erModel->addConnection(10, 0, 1, "Connection0,1"));
 	EXPECT_EQ(11, _erModel->addConnection(11, 5, 6, "Connection5,6"));
	// Entity �MRelation �۳s�A�]Cardinality
	EXPECT_EQ(12, _erModel->addConnection(12, 1, 2, "1"));
  	EXPECT_EQ(13, _erModel->addConnection(13, 7, 8, "N"));

	// ���~�����A�۳s

	// �d�L��Node
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 100, 5, "Connection100,5"));
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 10, 500, "Connection10,500"));
	// Attribute��Relation�۳s
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 7, 5, "Connection7,5"));
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 5, 7, "Connection5,7"));
	// �ۤv�P�ۤv�۳s
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 0, 0, "Connection0,0"));
	// �w�g�s�L
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 0, 1, "Connection0,1"));
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 1, 0, "Connection1,0"));
	// �w�g�s�L��Attribute�P��LEntity�۳s
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 0, 8, "Connection0,8"));
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 5, 9, "Connection5,9"));
	// �ۦP���A�۳s
	// Entity�sEntity
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 1, 8, "Connection1,8"));
	// Attribute�sAttribute
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 0, 3, "Connection0,3"));
	// Relationship�sRelationship
	EXPECT_EQ(PARAMETER_ISERROR, _erModel->addConnection(14, 2, 7, "Connection2,7"));
}

TEST_F(ERModelTest, checkConnectionState){

	EXPECT_EQ("CANCONNECT", _erModel->checkConnectionState(_erModel->_components[1], _erModel->_components[0]));
	EXPECT_EQ("CANCONNECT", _erModel->checkConnectionState(_erModel->_components[1], _erModel->_components[2]));
	EXPECT_EQ("CANCONNECT", _erModel->checkConnectionState(_erModel->_components[5], _erModel->_components[6]));

	// �w�g�s�L
	_erModel->addConnection(10, 0, 1, "Connection0,1");
	EXPECT_EQ("The node '1' has already been connected to component '0'.", _erModel->checkConnectionState(_erModel->_components[1], _erModel->_components[0]));
	EXPECT_EQ("The node '0' has already been connected to component '1'.", _erModel->checkConnectionState(_erModel->_components[0], _erModel->_components[1]));
	_erModel->addConnection(11, 1, 2, "1");
	EXPECT_EQ("The node '2' has already been connected to component '1'.", _erModel->checkConnectionState(_erModel->_components[2], _erModel->_components[1]));
	EXPECT_EQ("The node '1' has already been connected to component '2'.", _erModel->checkConnectionState(_erModel->_components[1], _erModel->_components[2]));

	// ���A����
	// A-A
	EXPECT_EQ("The node '0' cannot be connected by the node '3'.", _erModel->checkConnectionState(_erModel->_components[3], _erModel->_components[0]));
	// E-E
	EXPECT_EQ("The node '9' cannot be connected by the node '6'.", _erModel->checkConnectionState(_erModel->_components[6], _erModel->_components[9]));
	// R-R
	EXPECT_EQ("The node '7' cannot be connected by the node '2'.", _erModel->checkConnectionState(_erModel->_components[2], _erModel->_components[7]));
	// A-R
	EXPECT_EQ("The node '7' cannot be connected by the node '0'.", _erModel->checkConnectionState(_erModel->_components[0], _erModel->_components[7]));

	// �s��ۤv
	EXPECT_EQ("The node '0' cannot be connected to itself.", _erModel->checkConnectionState(_erModel->_components[0], _erModel->_components[0]));
	EXPECT_EQ("The node '9' cannot be connected to itself.", _erModel->checkConnectionState(_erModel->_components[9], _erModel->_components[9]));
	EXPECT_EQ("The node '7' cannot be connected to itself.", _erModel->checkConnectionState(_erModel->_components[7], _erModel->_components[7]));

	// Attribute�w�g�P��LEntity�s���L
	EXPECT_EQ("The node '6' cannot be connected by the node '0'.", _erModel->checkConnectionState(_erModel->_components[0], _erModel->_components[6]));
	_erModel->addConnection(12, 3, 9, "1");
	EXPECT_EQ("The node '8' cannot be connected by the node '3'.", _erModel->checkConnectionState(_erModel->_components[3], _erModel->_components[8]));
}

TEST_F(ERModelTest, getCheckConnectionStateMessage){
	EXPECT_EQ("CANCONNECT", _erModel->getCheckConnectionStateMessage(1, 0));
	EXPECT_EQ("CANCONNECT", _erModel->getCheckConnectionStateMessage(1, 2));
	EXPECT_EQ("CANCONNECT", _erModel->getCheckConnectionStateMessage(5, 6));

	// �w�g�s�L
	_erModel->addConnection(10, 0, 1, "Connection0,1");
	EXPECT_EQ("The node '1' has already been connected to component '0'.", _erModel->getCheckConnectionStateMessage(1, 0));
	EXPECT_EQ("The node '0' has already been connected to component '1'.", _erModel->getCheckConnectionStateMessage(0, 1));
	_erModel->addConnection(11, 1, 2, "1");
	EXPECT_EQ("The node '2' has already been connected to component '1'.", _erModel->getCheckConnectionStateMessage(2, 1));
	EXPECT_EQ("The node '1' has already been connected to component '2'.", _erModel->getCheckConnectionStateMessage(1, 2));

	// ���A����
	// A-A
	EXPECT_EQ("The node '0' cannot be connected by the node '3'.", _erModel->getCheckConnectionStateMessage(3, 0));
	// E-E
	EXPECT_EQ("The node '9' cannot be connected by the node '6'.", _erModel->getCheckConnectionStateMessage(6, 9));
	// R-R
	EXPECT_EQ("The node '7' cannot be connected by the node '2'.", _erModel->getCheckConnectionStateMessage(2, 7));
	// A-R
	EXPECT_EQ("The node '7' cannot be connected by the node '0'.", _erModel->getCheckConnectionStateMessage(0, 7));

	// �s��ۤv
	EXPECT_EQ("The node '0' cannot be connected to itself.", _erModel->getCheckConnectionStateMessage(0, 0));
	EXPECT_EQ("The node '9' cannot be connected to itself.", _erModel->getCheckConnectionStateMessage(9, 9));
	EXPECT_EQ("The node '7' cannot be connected to itself.", _erModel->getCheckConnectionStateMessage(7, 7));

	// Attribute�w�g�P��LEntity�s���L
	EXPECT_EQ("The node '6' cannot be connected by the node '0'.", _erModel->getCheckConnectionStateMessage(0, 6));
	_erModel->addConnection(12, 3, 9, "1");
	EXPECT_EQ("The node '8' cannot be connected by the node '3'.", _erModel->getCheckConnectionStateMessage(3, 8));
}

TEST_F(ERModelTest, checkSetCardinality){
	// E-R �� R-E
	EXPECT_TRUE(_erModel->checkSetCardinality(1, 2));
	EXPECT_TRUE(_erModel->checkSetCardinality(2, 1));
	EXPECT_TRUE(_erModel->checkSetCardinality(7, 9));
	EXPECT_TRUE(_erModel->checkSetCardinality(9, 7));

	// A-E �� A-R �� A-A
	EXPECT_FALSE(_erModel->checkSetCardinality(0, 1));
	EXPECT_FALSE(_erModel->checkSetCardinality(1, 0));
	EXPECT_FALSE(_erModel->checkSetCardinality(2, 0));
	EXPECT_FALSE(_erModel->checkSetCardinality(0, 2));
	EXPECT_FALSE(_erModel->checkSetCardinality(0, 0));
	EXPECT_FALSE(_erModel->checkSetCardinality(3, 5));
}

TEST_F(ERModelTest, setCardinality){
	// �@�}�l�Ū�
	EXPECT_TRUE(static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().empty());
	//	E-R, �bR���]�wEntityCardinality
	_erModel->setCardinality(_erModel->_components[1], _erModel->_components[2], "1");
	EXPECT_FALSE(static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().empty());
	_erModel->setCardinality(_erModel->_components[6], _erModel->_components[7], "N");
	EXPECT_FALSE(static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().empty());
	_erModel->setCardinality(_erModel->_components[6], _erModel->_components[2], "N");
	EXPECT_EQ(2, static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().size());

	//	R-E, �bR���]�wEntityCardinality
	_erModel->setCardinality(_erModel->_components[2], _erModel->_components[9], "N");
	EXPECT_EQ(3, static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().size());
	_erModel->setCardinality(_erModel->_components[2], _erModel->_components[8], "1");
	EXPECT_EQ(4, static_cast<NodeRelationship*>(_erModel->_components[2])->getEntityCardinality().size());

}

TEST_F(ERModelTest, getComponentsTable){
	string allTypeResult = "  A   |  0   |  A0\n";
	allTypeResult += "  E   |  1   |  E1\n";
	allTypeResult += "  R   |  2   |  R2\n";
	allTypeResult += "  A   |  3   |  A3\n";
	allTypeResult += "  A   |  4   |  A4\n";
	allTypeResult += "  A   |  5   |  A5\n";
	allTypeResult += "  E   |  6   |  E6\n";
	allTypeResult += "  R   |  7   |  R7\n";
	allTypeResult += "  E   |  8   |  E8\n";
	allTypeResult += "  E   |  9   |  E9\n";

	string attributeTypeResult = "  A   |  0   |  A0\n";
	attributeTypeResult += "  A   |  3   |  A3\n";
	attributeTypeResult += "  A   |  4   |  A4\n";
	attributeTypeResult += "  A   |  5   |  A5\n";

	string entityTypeResult = "  E   |  1   |  E1\n";
	entityTypeResult += "  E   |  6   |  E6\n";
	entityTypeResult += "  E   |  8   |  E8\n";
	entityTypeResult += "  E   |  9   |  E9\n";

	string relationshipTypeResult = "  R   |  2   |  R2\n";
	relationshipTypeResult += "  R   |  7   |  R7\n";


	EXPECT_EQ(allTypeResult, _erModel->getComponentsTable(PARAMETER_ALL));
	EXPECT_EQ(attributeTypeResult, _erModel->getComponentsTable(PARAMETER_ATTRIBUTE));
	EXPECT_EQ(entityTypeResult, _erModel->getComponentsTable(PARAMETER_ENTITY));
	EXPECT_EQ(relationshipTypeResult, _erModel->getComponentsTable(PARAMETER_RELATIONSHIP));

	// �]����l�Ƥ��S��Connector�A�ҥH�ΨӴ��շj�M���쵲�G�����p
	EXPECT_EQ(PARAMETER_NULL, _erModel->getComponentsTable(PARAMETER_CONNECTOR));

}

TEST_F(ERModelTest, getConnectionTable){
	// �@�}�lconnections�O�Ū��S�F��A�ΨӧP�_�j�p��0�����p
	EXPECT_EQ(PARAMETER_NULL, _erModel->getConnectionTable());
	
	string resultTwoConnection = "     10     |  0   |  1   |\n";
	resultTwoConnection += "     11     |  5   |  6   |\n";

	string resultFourConnection = resultTwoConnection;
	resultFourConnection += "     12     |  1   |  2   |\n";
	resultFourConnection += "     13     |  7   |  8   |\n";

	// �[�J���Connection��A����ӳs��
	EXPECT_EQ(10, _erModel->addConnection(10, 0, 1, "Connection0,1"));
	EXPECT_EQ(11, _erModel->addConnection(11, 5, 6, "Connection5,6"));
	EXPECT_EQ(resultTwoConnection, _erModel->getConnectionTable());

	// �A�[�J���Connection��A���|�ӳs��
	EXPECT_EQ(12, _erModel->addConnection(12, 1, 2, "1"));
	EXPECT_EQ(13, _erModel->addConnection(13, 7, 8, "N"));
	EXPECT_EQ(resultFourConnection, _erModel->getConnectionTable());
}
//{"A0", "E1", "R2", "A3", "A4", "A5", "E6", "R7", "E8", "E9"}
TEST_F(ERModelTest, setPrimaryKey){
	vector<int> primaryKeys;

	// ����PK�S���]�����p
	_erModel->setPrimaryKey(1, primaryKeys);
	EXPECT_EQ(0, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

	// �[�JPK
	primaryKeys.push_back(0);
	primaryKeys.push_back(3);
	primaryKeys.push_back(4);
	_erModel->setPrimaryKey(1, primaryKeys);
	EXPECT_EQ(3, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

	// ���ե[�J�P�˪�Attribute�O�_�|�W�[PK��
	primaryKeys.pop_back();
	primaryKeys.pop_back();
	primaryKeys.push_back(3);
	_erModel->setPrimaryKey(1, primaryKeys);
	EXPECT_EQ(3, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

	primaryKeys.push_back(4);
	primaryKeys.push_back(5);
	_erModel->setPrimaryKey(6, primaryKeys);
	EXPECT_EQ(4, static_cast<NodeEntity*>(_erModel->_components[6])->getPrimaryKey().size());
}

TEST_F(ERModelTest, reBuildPrimaryKeyFromAttribute){
	// �_�l�L�F��A�ΨӽT�{�[�J��O�_������
	EXPECT_FALSE(static_cast<NodeAttribute*>(_erModel->_components[0])->getIsPrimaryKey());
	EXPECT_FALSE(static_cast<NodeAttribute*>(_erModel->_components[3])->getIsPrimaryKey());
	EXPECT_EQ(0, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

	// �[�J��
	_erModel->reBuildPrimaryKeyFromAttribute(0,1);
	EXPECT_TRUE(static_cast<NodeAttribute*>(_erModel->_components[0])->getIsPrimaryKey());
	EXPECT_EQ(1, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

	// �ĤG��
	_erModel->reBuildPrimaryKeyFromAttribute(3,1);
	EXPECT_TRUE(static_cast<NodeAttribute*>(_erModel->_components[3])->getIsPrimaryKey());
	EXPECT_EQ(2, static_cast<NodeEntity*>(_erModel->_components[1])->getPrimaryKey().size());

}

TEST_F(ERModelTest, searchAttributeOfEntity){
	// �_�l�Ū�
	EXPECT_EQ(PARAMETER_NULL, _erModel->searchAttributeOfEntity(1));

	string result = "  A   |  4   |  A4\n";
	result +=  "  A   |  3   |  A3\n";
	result +=  "  A   |  0   |  A0\n";

	EXPECT_EQ(10, _erModel->addConnection(10, 4, 6, "Connection4,6"));
	EXPECT_EQ(11, _erModel->addConnection(11, 3, 6, "Connection4,6"));
	EXPECT_EQ(12, _erModel->addConnection(12, 0, 6, "Connection4,6"));
	EXPECT_EQ(result, _erModel->searchAttributeOfEntity(6));
}
/*
TEST_F(ERModelTest, searchEntityConnection){

}

TEST_F(ERModelTest, getERDiagramTable){

}

TEST_F(ERModelTest, getAttributeContents){

}

TEST_F(ERModelTest, setForeignKey){

}

TEST_F(ERModelTest, oneToOne){

}

TEST_F(ERModelTest, checkOneToOne){

}

TEST_F(ERModelTest, searchForeignKey){

}

TEST_F(ERModelTest, loadERDiagram){

}

TEST_F(ERModelTest, classifyInputFile){

}

TEST_F(ERModelTest, recoveryFile){

}

TEST_F(ERModelTest, recoveryAllComponent){

}

TEST_F(ERModelTest, recoveryConnection){

}

TEST_F(ERModelTest, recoveryPrimaryKey){

}

TEST_F(ERModelTest, splitter){

}

TEST_F(ERModelTest, saveERDiagram){

}

TEST_F(ERModelTest, creatFilePath){

}

TEST_F(ERModelTest, saveComponentTable){

}

TEST_F(ERModelTest, saveConnectionTable){

}

TEST_F(ERModelTest, savePrimaryKeyTable){

}

TEST_F(ERModelTest, deleteFunction){

}

TEST_F(ERModelTest, deleteComponent){

}

TEST_F(ERModelTest, deleteConnection){

}

TEST_F(ERModelTest, deleteTableSet){

}

TEST_F(ERModelTest, addNodeCmd){

}

TEST_F(ERModelTest, addConnectionCmd){

}

TEST_F(ERModelTest, deleteCmd){

}

TEST_F(ERModelTest, undoCmd){

}

TEST_F(ERModelTest, redoCmd){

}

TEST_F(ERModelTest, searchComponent){

}

TEST_F(ERModelTest, searchComponentConnection){

}

TEST_F(ERModelTest, searchComponentExist){

}

TEST_F(ERModelTest, searchSpecificTypeComponentSet){

}

TEST_F(ERModelTest, getComponentDataList){

}

TEST_F(ERModelTest, searchConnection){

}

TEST_F(ERModelTest, searchRelatedComponent){

}

TEST_F(ERModelTest, getComponentTableSize){

}

TEST_F(ERModelTest, getConnectionTableSize){

}

TEST_F(ERModelTest, resetERModel){

}
*/