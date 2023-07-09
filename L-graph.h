#pragma once
#include "stdAfx.h"
#include "Node.h"			
#include "Arc.h"
#include "Expression.h"
class L_Graph
{
private:
	vector<Arc> arcStr;
	vector<NodeStructure> nodeStr;
	NodeStructure beginNode;
	NodeStructure endNode;
	vector<L_Graph> subGraph;
	bool sub = false;
public:
	L_Graph() {}
	void setSub(bool flag) { this->sub = flag; }
	bool Sub() { return sub; }
	void graphUpData(vector<Arc> arcStr, vector<NodeStructure> nodeStr)
	{
		this->arcStr = arcStr;
		this->nodeStr = nodeStr;
	}
	void setBeg_End(NodeStructure beginNode, NodeStructure endNode)
	{
		this->beginNode = beginNode;
		this->endNode = endNode;
	}
	NodeStructure getBeg() { return beginNode; }
	NodeStructure getEnd() { return endNode; }
	vector<Arc> getArcStr() { return arcStr; }
	vector<NodeStructure> getNodeStr() { return nodeStr; }
	void subGraphUpData(L_Graph subGraph) { this->subGraph.push_back(subGraph); }
	vector<L_Graph> getSubGraph(vector<L_Graph> subGraph) { return subGraph; }
	void printGraphStr()
	{
		cout << "InfNode:" << endl;
		for (int i = 0; i < nodeStr.size(); i++)
		{
			nodeStr[i].printNode();
		}

		cout << "InfArc:" << endl;
		for (int i = 0; i < arcStr.size(); i++)
		{
			arcStr[i].printArc();
		}
		if (this->sub)
		{
			cout << endl;
			cout << "///////////////////////////////////////////////////////" << endl;
			for (int i = 0; i < subGraph.size(); i++)
			{
				subGraph[i].printGraphStr();
			}
			cout << "///////////////////////////////////////////////////////" << endl;
		}
	}
};

NodeStructure findBegin(vector<NodeStructure>& nodeStr, int depth);

NodeStructure findEnd(vector<NodeStructure>& nodeStr, int depth);

bool buildGraph(L_Graph& graphStr, vector<Arc> arcStr, vector<NodeStructure> nodeStr, int depth);

vector<string> Search(L_Graph graphStr, string test, vector<int>& PosN, vector<string>& StrN);

void printAns(vector<string>Route, vector<int> PosN, vector<string> StrN);

void outAns(vector<string>Route, vector<int> PosN, vector<string> StrN, string fileOut);
