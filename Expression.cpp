#include "Expression.h"

using namespace std;

bool judgeDepth(string expression, int* nowl, int len)
{
    bool flag = false;
    int depth1 = 0;
    int depth2 = 0;
    int numRight1 = 0;
    int numRight2 = 0;
    int insideNowl = *nowl;

    while (insideNowl < len)
    {
        if (expression[insideNowl] == '<')
        {
            depth1++;
            flag = true;
        }
        if (expression[insideNowl] == '[')
        {
            depth2++;
            flag = true;
        }
        if (expression[insideNowl] == ')')
        {
            if (depth1 == 0)break;
            numRight1++;
        }
        if (expression[insideNowl] == ']')
        {
            if (depth2 == 0)break;
            numRight2++;
        }
        if (depth2 == numRight2 && flag && expression[insideNowl + 1] == ']')
        {
            break;
        }
        if (depth1 * 4 == numRight1 && flag && expression[insideNowl + 1] == ')')
        {
            break;
        }
        insideNowl++;
    }
    *nowl = insideNowl;
    return flag;
}

bool recognitionLeftorRight(vector<expressionStructure>& expStr, string expression, int* l, int len, int type)
{
    int insideL = *l;
    string names = "";
    string subexpression = "";
    insideL += 3;
    while (expression[insideL++] != ')')
    {
        names += expression[insideL - 1];
    }
    insideL++;
    int nowl = insideL;
    bool flag = judgeDepth(expression, &nowl, len);//<_(1)( a<_(2)(c) (c)>_(2) )
    if (flag)
    {
        while (insideL <= nowl)
        {
            subexpression += expression[insideL++];
        }
        insideL++;
    }
    else
    {
        while (expression[insideL++] != ')')
        {
            subexpression += expression[insideL - 1];
        }
    }
    expStr.push_back(expressionStructure(type, names, subexpression, flag));
    *l = insideL;
    return flag;
}

bool recognitionSelfRep(vector<expressionStructure>& expStr, string expression, int* l, int len)
{
    int insideL = *l;
    string names = "";
    string subexpression = "";
    insideL++;
    int nowl = insideL;
    bool flag = judgeDepth(expression, &nowl, len);//[ [b][a] ]
    if (flag)
    {
        while (insideL <= nowl)
        {
            subexpression += expression[insideL++];
        }
        insideL++;
    }
    else
    {
        while (expression[insideL++] != ']')
        {
            subexpression += expression[insideL - 1];
        }
    }
    expStr.push_back(expressionStructure(3, "#", subexpression, flag));
    *l = insideL;
    return flag;
}

bool recognition(vector<expressionStructure>& expStr, string expression)
{
    int len = expression.length();
    int l = 0;
    bool haveSub = false;
    bool flag = false;
    while (l < len)
    {
        if (expression[l] == '<')
        {
            haveSub = recognitionLeftorRight(expStr, expression, &l, len, 1);
            if (haveSub) flag = true;
        }
        if (expression[l] == '>')
        {
            haveSub = recognitionLeftorRight(expStr, expression, &l, len, 2);
            if (haveSub) flag = true;
        }
        if (expression[l] == '[')
        {
            haveSub = recognitionSelfRep(expStr, expression, &l, len);
            if (haveSub) flag = true;
        }
        if (('a' <= expression[l] && expression[l] <= 'z') || ('A' <= expression[l] && expression[l] <= 'Z'))
        {
            string sub = "";
            while (('a' <= expression[l] && expression[l] <= 'z') || ('A' <= expression[l] && expression[l] <= 'Z'))
            {
                sub += expression[l++];
            }
            expStr.push_back(expressionStructure(4, "#", sub, false));
        }
    }
    return flag;
}

bool buildSub(vector<expressionStructure>& exp, string expression)
{
    bool flag = recognition(exp, expression);
    if (flag)
    {
        for (int i = 0; i < exp.size(); i++)
        {
            if (exp[i].Sub())
            {
                vector<expressionStructure> subExp = exp[i].getSubexp();
                buildSub(subExp, exp[i].getExptession());
                exp[i].setSubexp(subExp);
                exp[i].setDepth(subExp.size());
                subExp.clear();
            }
        }
        
    }
    return true;
}

void printExp(vector<expressionStructure> exp, string strI)
{ 
    for (int i = 0; i < exp.size(); i++)
    {
        cout << strI << i << endl; exp[i].printStruct();
        if (exp[i].Sub())
        {
            cout << "///////////////////////////////////////////////////////" << endl;
            vector<expressionStructure> subExp = exp[i].getSubexp();
            printExp(subExp, strI + to_string(i) + ".");
            subExp.clear();
            cout << "///////////////////////////////////////////////////////" << endl;
        }
    }
}

NodeStructure getInfNode(int type, string exp, string name)
{
    NodeStructure newNodeStr;
    switch (type)
    {
    case 1: newNodeStr.nodeUpdata(exp, "<" + name); break;
    case 2: newNodeStr.nodeUpdata(exp, ">" + name); break;
    case 3: newNodeStr.nodeUpdata(exp, "[]" + name); break;
    }
    return newNodeStr;
}

Arc getInfArc(NodeStructure node1, NodeStructure node2, int type, string exp, string name)
{
    Arc newArcStr(node1, node2);
    switch (type)
    {
    case 1: newArcStr.arcUpData(exp, "<" + name); break;
    case 2: newArcStr.arcUpData(exp, ">" + name); break;
    case 3: newArcStr.arcUpData(exp, "[]" + name); break;
    }
    return newArcStr;
}

bool toGraphStr(vector<expressionStructure> expStr, vector<NodeStructure>& nodeStr, vector<Arc>& arcStr, string strK)
{    
    int k = 0;
    vector<string> strExpStr;
    for (int i = 0; i < expStr.size(); i++)
    {
        if (1 <= expStr[i].getType() && expStr[i].getType() <= 3)
        {
            strExpStr.push_back("node");
        }
        else
        {
            strExpStr.push_back("arc");

        }
    }
    NodeStructure nowNode;
    for (int i = 0; i < expStr.size(); i++)
    {
        string preExp = "";
        if (i > 0)
        {
            preExp = expStr[i - 1].getExptession();
        }
        string exp = expStr[i].getExptession();
        if (i == 0 && strExpStr[i] == "arc")
        {
            NodeStructure newNodeStr;
            newNodeStr.setNodeName(strK + to_string(k++));
            newNodeStr.setNodeDepth();
            newNodeStr.setIsBegin(true);
            newNodeStr.nodeUpdata(exp, "¦Ø");
            nodeStr.push_back(newNodeStr);
            nowNode = newNodeStr;
        }
        if (strExpStr[i] == "node")
        {
            string name = expStr[i].getNames();
            NodeStructure newNodeStr = getInfNode(expStr[i].getType(), exp, name);
            newNodeStr.setNodeName(strK + to_string(k++));
            newNodeStr.setNodeDepth();
            if (i == 0) newNodeStr.setIsBegin(true);
            if (i == expStr.size() - 1) newNodeStr.setIsEnd(true);
            if (i > 0)
            {
                NodeStructure preNode = nowNode;
                if (strExpStr[i - 1] == "arc")
                {
                    newNodeStr.nodeUpdata(preExp, "¦Ø");
                    Arc nnewArc(preNode, newNodeStr);
                    nnewArc.arcUpData(preExp, "¦Ø");
                    nnewArc.setArcDepth();
                    arcStr.push_back(nnewArc);
                }
                else
                {
                    newNodeStr.nodeUpdata("¦Å", "¦Ø");
                    Arc nnewArc(preNode, newNodeStr);
                    nnewArc.arcUpData("¦Å", "¦Ø");
                    nnewArc.setArcDepth();
                    arcStr.push_back(nnewArc);
                }
            }
            if (i + 1 < expStr.size())
                if (strExpStr[i + 1] == "arc")
                {
                    newNodeStr.nodeUpdata(expStr[i + 1].getExptession(), "¦Ø");
                }
                else
                {
                    newNodeStr.nodeUpdata("¦Å", "¦Ø");
                }
            Arc newArc = getInfArc(newNodeStr, newNodeStr, expStr[i].getType(), exp, name);
            newArc.setArcDepth();
            arcStr.push_back(newArc);
            nodeStr.push_back(newNodeStr);
            nowNode = newNodeStr;
        }
        if (i == expStr.size() - 1 && strExpStr[i] == "arc")
        {
            NodeStructure newNodeStr;      
            newNodeStr.setNodeName(strK + to_string(k++));
            newNodeStr.setNodeDepth();
            newNodeStr.setIsEnd(true);
            newNodeStr.nodeUpdata(exp, "¦Ø");
            NodeStructure preNode = nowNode;
            nodeStr.push_back(newNodeStr);
            Arc nnewArc(preNode, newNodeStr);
            nnewArc.arcUpData(exp, "¦Ø");
            nnewArc.setArcDepth();
            arcStr.push_back(nnewArc);
        }
        if (expStr[i].Sub())
        {
            toGraphStr(expStr[i].getSubexp(), nodeStr, arcStr, strK + to_string(k - 1) + ",");
        }
    }
    return true;
}