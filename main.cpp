#include "Expression.h"
#include "Node.h"
#include "Arc.h"
#include "L-graph.h"

void inPut(string str, vector<string>& strN)
{
    ifstream in(str);
    string line;
    while (getline(in, line))
    {
        strN.push_back(line);
    }
    in.close();
}

void outPut(string fileOut, string test)
{
    ofstream out(fileOut);
    out << test << endl;
    out.close();
}

int main(int argc, char** argv)
{    
    vector<string> testN;
    vector<string> expressionN;
    inPut("inputTest.txt", testN);
    string test = testN[0];
    inPut("inputExpression.txt", expressionN);
    string expression = expressionN[0];
    cout << "test = " << test << endl;
    cout << "expression = " << expression << endl;
    cout << endl;
    vector<expressionStructure> expStr;
    bool flag1 = buildSub(expStr, expression);
    if (flag1)
    {
        cout << "Expression Structure build success!" << endl;
        printExp(expStr, "InfExp ");
        cout << "///////////////////////////////////////////////////////" << endl;
    }
    else cout << "error" << endl;
    vector<NodeStructure> nodeStr;
    vector<Arc> arcStr;
    toGraphStr(expStr, nodeStr, arcStr, "");
    for (int i = 0; i < nodeStr.size(); i++)
    {
        nodeStr[i].printNode();
    }
    cout << "InfArc:" << endl;
    for (int i = 0; i < arcStr.size(); i++)
    {
        arcStr[i].printArc();
    }
    cout << endl;
    L_Graph graphStr;
    bool flag2 = buildGraph(graphStr, arcStr, nodeStr, 0);
    if (flag2)
    {
        cout << "L-Graph build success!" << endl;
        graphStr.printGraphStr();
        cout << "///////////////////////////////////////////////////////" << endl;
    }
    else cout << "error" << endl;
    bool flag3 = graphStr.Sub();
    if (flag3)
    {
        cout << "error: have Sub_L-graph can`t search." << endl;
        ofstream myfile("outputResults.txt", ios::out | ios::trunc);
        if (myfile.is_open())
        {
            myfile << "Have Sub_L-graph can`t search." << endl;
            myfile.close();
        }
    }
    else
    {
        vector<int> PosN;
        vector<string> StrN;
        vector<string> Route = Search(graphStr, test, PosN, StrN);
        if (Route.empty())
        {
            cout << "Don`t found" << endl;
            ofstream myfile("outputResults.txt", ios::out | ios::trunc);
            if (myfile.is_open()) 
            {
                myfile << "Don`t found" << endl;
                myfile.close();
            }
        }
        else
        {
            cout << "Found" << endl;
            printAns(Route, PosN, StrN);
            outAns(Route, PosN, StrN, "outputResults.txt");
        }
    }
    return 0;
}