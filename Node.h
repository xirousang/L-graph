#pragma once
#include "stdAfx.h"
class NodeStructure
{
private:
    string nodeName = "";          
    int type = 0;                 
    int edgNum = 0;               
    int depth = 0;
    vector<string> exps;          
    vector<string> bracketNames;   
    bool isBegin = false;          
    bool isEnd = false;           
public:
    NodeStructure() { }
    ~NodeStructure() { };
    void setNodeName(string nodeName) { this->nodeName = nodeName; }
    string getNodeName() { return nodeName; }
    void setIsBegin(bool flag) { this->isBegin = flag; }
    void setIsEnd(bool flag) { this->isEnd = flag; }
    bool getIsBegin() { return isBegin; }
    bool getIsEnd() { return isEnd; }
    int getEdgNum() { return edgNum; }
    vector<string> getBracketNames() { return bracketNames; }
    void nodeUpdata(string exps, string bkNames)
    {
        this->edgNum++;
        this->exps.push_back(exps);
        this->bracketNames.push_back(bkNames);
    }
    void setNodeDepth()
    {
        int num = 0;
        int l = 0;
        string name = nodeName;
        while (l < name.length())
        {
            if (name[l] == ',') num++;
            l++;
        }
        depth = num;
    }
    int getNodeDepht() { return depth; }
    void printNode()
    {        
        if (isBegin)cout << "BEGIN";
        if (isEnd)cout << "END";
        if (isBegin && isEnd) cout << "\ttype\texpression" << endl;
        else cout << "\t\ttype\texpression" << endl;
        cout << "Node\"" << nodeName <<"\"(d=" << depth << "):";
        for (int i = 0; i < edgNum; i++)
        {
            if(i != 0)cout << "\t";
            cout << "\t" << bracketNames[i] << "\t" << exps[i] << endl;
        }
        cout << endl;
    }
};
