#pragma once
#include "stdAfx.h"
#include "Node.h"
class Arc
{
private:
    NodeStructure fristNode;      
    NodeStructure secondNode;     
    int depth = 0;
    int edgNum = 0;                
    vector<string> exps;          
    vector<string> bracketNames;   
    bool connect = false;
public:
    Arc(NodeStructure Node1, NodeStructure Node2)
    {
        this->fristNode = Node1;
        this->secondNode = Node2;
        this->edgNum = 0;
        this->connect = true;
    }
    ~Arc() { };
    void arcUpData(string exps, string bracketNames)
    {
        this->edgNum++;
        this->exps.push_back(exps);
        this->bracketNames.push_back(bracketNames);
    }
    vector<string> getExp() { return exps; }
    vector<string> getType() { return bracketNames; }
    bool getConnect() { return connect; }
    NodeStructure getFristNode() { return fristNode; }
    NodeStructure getSecondNode() { return secondNode; }
    void setArcDepth()
    {
        depth = fristNode.getNodeDepht();
     }
    int getArcDepht() { return depth; }
    void printArc()
    {
        
        cout << "Node\"" << fristNode.getNodeName() << "\" to \"" << secondNode.getNodeName() << "\"(d=" << depth << "):" << endl;
        cout << "Type\texpression" << endl;
        for (int i = 0; i < edgNum; i++)
        {
            cout << bracketNames[i] << "\t" << exps[i] << endl;
        }
        cout << endl;
    }
};