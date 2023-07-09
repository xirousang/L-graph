#include "L-graph.h"

NodeStructure findBegin(vector<NodeStructure>& nodeStr, int depth)
{
	for (int i = 0; i < nodeStr.size(); i++)
	{
		if (nodeStr[i].getNodeDepht() == depth && nodeStr[i].getIsBegin()) return nodeStr[i];
	}
}

NodeStructure findEnd(vector<NodeStructure>& nodeStr, int depth)
{
	for (int i = 0; i < nodeStr.size(); i++)
	{
		if (nodeStr[i].getNodeDepht() == depth && nodeStr[i].getIsEnd()) return nodeStr[i];
	}
}

bool buildGraph(L_Graph& graphStr, vector<Arc> arcStr, vector<NodeStructure> nodeStr, int depth)
{	
	vector<NodeStructure> graphNodeStr;
	NodeStructure beginNode = findBegin(nodeStr, depth);
	NodeStructure endNode = findEnd(nodeStr, depth);
	graphStr.setBeg_End(beginNode, endNode);
	for (int i = 0; i < nodeStr.size(); i++)
	{
		if (nodeStr[i].getNodeDepht() == depth)
		{
			graphNodeStr.push_back(nodeStr[i]);
			nodeStr.erase(nodeStr.begin() + i);
			i--;
		}
	}
	vector<Arc> graphArcStr;
	for (int i = 0; i < arcStr.size(); i++)
	{
		if (arcStr[i].getArcDepht() == depth)
		{
			graphArcStr.push_back(arcStr[i]);
			arcStr.erase(arcStr.begin() + i);
			i--;
		}
	}
	graphStr.graphUpData(graphArcStr, graphNodeStr);
	if (!arcStr.empty() || !nodeStr.empty())
	{
		graphStr.setSub(true);
		L_Graph subGraph;
		buildGraph(subGraph, arcStr, nodeStr, ++depth);
		graphStr.subGraphUpData(subGraph);
	}
	return true;
}

bool Match(int& L, int tLength, string exp, string test)
{
	int l = 0;
	int preL = L;
	while (l < exp.length() && L < tLength)
	{
		if (test[L] == exp[l])
		{
			L++;
			l++;
		}
		else
		{
			L = preL;
			return false;
		}

	}
	if (l == exp.length()) return true;
	else return false;
}

bool isAllEqual(stack<string> st, string target) 
{
	while (!st.empty()) 
	{
		string top = st.top();
		st.pop();
		if (top != target) 	return false;
	}
	return true;
}

vector<string> Search(L_Graph graphStr, string test, vector<int>& PosN, vector<string>& StrN)
{
	vector<string> RouteN;
	int Pos = 0;
outer_loop:
	string Route = "";
	string Str = "";
	stack<string> Stack;
	string nowStr;
	int tLength = test.length();
	NodeStructure begNode = graphStr.getBeg();
	NodeStructure nowNode = begNode;
	Route += nowNode.getNodeName();
	vector<Arc> arcStr = graphStr.getArcStr();
	int L = 0;
	bool finish = false;
	while (L < tLength)
	{
		int i = 0; 
		while(i < arcStr.size())
		{
			if (arcStr[i].getFristNode().getNodeName() == nowNode.getNodeName())
			{
				string typeStr = arcStr[i].getType()[0];
				string exp = arcStr[i].getExp()[0];
				//int preL = L;
				bool flag = Match(L, tLength, exp, test);
				//cout << flag << endl;				
				if (flag)
				{
					int type = 0;
					if (typeStr == "¦Ø") type = 0;
					if (typeStr == "[]#") type = 1;
					if (typeStr[0] == '<') type = 2;
					if (typeStr[0] == '>') type = 3;
					switch (type)
					{
					case 0:
					{
						nowNode = arcStr[i].getSecondNode();
						Route += "->" + nowNode.getNodeName();
						break;
					}
					case 1:
					{
						nowNode = arcStr[i].getSecondNode();
						Route += "->" + nowNode.getNodeName();
						break;
					}
					case 2:
					{
						Stack.push(typeStr);
						nowNode = arcStr[i].getSecondNode();
						Route += "->" + nowNode.getNodeName();
						break;
					}
					case 3:
					{
						if (!Stack.empty())
						{
							if (Stack.top().substr(1) == typeStr.substr(1))
							{
								Stack.pop();								
								nowNode = arcStr[i].getSecondNode();
								Route += "->" + nowNode.getNodeName();
							}
							else//<(1) <(2) >(2) >(1)
							{
								test = test.substr(1);
								Pos++;
								goto outer_loop;
							}
						}
						else
						{
							if (nowNode.getIsEnd())
							{
								Pos += L - 1 - Str.length();
								PosN.push_back(Pos);
								StrN.push_back(Str);
								RouteN.push_back(Route);
								test = test.substr(L - 1);								
								Pos += Str.length();
							}
							else
							{
								test = test.substr(1);
								Pos++;
							}
							goto outer_loop;
						}
						break;
					}
					}					
					Str += exp;
				}
				else
				{
					i++;
				}				
			}
			else
			{
				i++;
			}
		}		
		if (nowNode.getIsEnd())
		{
			if (nowNode.getIsBegin())
			{
				if (Route.length() > 1)
				{					
					Pos += L - Str.length();
					PosN.push_back(Pos);
					StrN.push_back(Str);
					RouteN.push_back(Route);
					test = test.substr(L);
					Pos += Str.length();
					goto outer_loop;
				}
			}
			else
			{
				if (Stack.empty())
				{
					Pos += L - Str.length();
					PosN.push_back(Pos);
					StrN.push_back(Str);
					RouteN.push_back(Route);
					test = test.substr(L);
					Pos += Str.length();
					goto outer_loop;
				}
				else
				{
					vector<string> type_namesBeg = begNode.getBracketNames();
					bool leftBeg = false;
					string leftName = "";
					for (int ii = 0; ii < type_namesBeg.size(); ii++)
					{
						if (type_namesBeg[ii][0] == '<')
						{
							leftBeg = true;
							leftName = type_namesBeg[ii];
						}
					}
					if (isAllEqual(Stack, leftName))
					{
						int  delLength = Stack.size();
						while (!Stack.empty())
						{
							Stack.pop();
						}
						Route = Route.substr(delLength * 3);	
						Str = Str.substr(delLength * (leftName.length() - 1));
						StrN.push_back(Str);
						Pos += L - Str.length();
						PosN.push_back(Pos);
						RouteN.push_back(Route);
						test = test.substr(L);
						Pos += Str.length();						
					}
					else
					{
						test = test.substr(1);
						Pos++;
					}
					goto outer_loop;
				}
			}
		}
		L++;
	}
	return RouteN;
}

void printAns(vector<string>Route,vector<int> PosN, vector<string> StrN)
{
	if (Route.empty())
	{
		cout << "don`t found" << endl;
	}
	else
	{
		cout << "Search results:" << endl;
	}
	for (int i = 0; i < Route.size(); i++)
	{
		cout << "Route " << i << " : " << Route[i] << endl;
		cout << "Pos: " << PosN[i] << endl;
		cout << "Str: " << StrN[i] << endl;
		cout << endl;
	}
}

void outAns(vector<string>Route, vector<int> PosN, vector<string> StrN, string fileOut)
{
	ofstream out(fileOut);
	out << "Search results:" << endl;

	for (int i = 0; i < Route.size(); i++)
	{
		out << "Route " << i << " : " << Route[i] << endl;
		out << "Pos: " << PosN[i] << endl;
		out << "Str: " << StrN[i] << endl;
		out << endl;
	}
	out.close();
}
