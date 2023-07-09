#pragma once
#include "stdAfx.h"
#include "Node.h"
#include "Arc.h"

class expressionStructure
{
private:
    int type;
    string names;
    string expression;
    bool haveSub = false;
    int depthSub = 0;
    vector<expressionStructure> subExpStr;
public:
    expressionStructure(int type, string names, string expression, bool haveSub)
    {
        this->type = type;
        this->names = names;
        this->expression = expression;
        this->haveSub = haveSub;
    }
    int getType() { return type; }
    string getNames() { return names; }
    string getExptession() { return expression; }
    bool Sub() { return haveSub; }
    void setDepth(int d) { this->depthSub = d; }
    int getDepth() { return depthSub; }
    void setSubexp(vector<expressionStructure> sub) { this->subExpStr = sub; }
    vector<expressionStructure> getSubexp() { return  subExpStr; }
    void printStruct()
    {
        cout << "type\tname\thave Sub?\texpression\n";
        switch (this->type)
        {
        case 1:cout << "<_"; break;
        case 2:cout << ">_"; break;
        case 3:cout << "[]"; break;
        case 4:cout << "¦Ø"; break;
        }
        cout << "\t" << this->names;
        switch (this->haveSub)
        {
        case 1:cout << "\t" << "yes(" << this->depthSub << ")"; break;
        case 0:cout << "\t" << "no"; break;
        }
        cout << "\t\t" << this->expression << endl;
    }
};

void setNodeDepth(vector<NodeStructure>& nodeStr);

void setArcDepth(vector<Arc>& arcStr);

bool judgeDepth(string expression, int* nowl, int len);

bool recognitionLeftorRight(vector<expressionStructure>& expStr, string expression, int* l, int len, int type);

bool recognitionSelfRep(vector<expressionStructure>& expStr, string expression, int* l, int len);

bool recognition(vector<expressionStructure>& expStr, string expression);

bool buildSub(vector<expressionStructure>& exp, string str);

bool toGraphStr(vector<expressionStructure> expStr, vector<NodeStructure>& nodeStr, vector<Arc>& ArcStr, string k);

void printExp(vector<expressionStructure> exp, string strI);