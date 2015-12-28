#include "lsysdecoder.h"
#include <cctype>
#include <cstring>
#include <cstdlib>


string LSysDecoder::genString(int depth)
{
    string rule, tmp, t;
    rule.assign(srule);
    t.assign(" ");
    int ran;

    for (int i = 0; i < depth; ++i)
    {
        for (int j = 0; j < rule.size(); ++j)
        {
            ran = random() % 2;
            if(ran || rule[j] == '[' || rule[j] == ']' || rule[j] == '+' || rule[j] == '-')
            {
                t+=rule[j];

                if(prodTable.find(t) != prodTable.end())
                {
                    tmp.clear();
                    tmp.append(rule, 0, j);
                    tmp.append(prodTable.find(t)->second);
                    tmp.append(rule, j+1, rule.size() - (j+1));
                    rule.assign(tmp);
                    j += prodTable.find(t)->second.size();
                }
                t.assign(" ");
            }
        }
    }

    cout<<rule<<endl;

    return rule;
}


LSysDecoder::LSysDecoder(string rules)
{
    stringstream ss(rules);
    string token;
    vector<string> productions;
    size_t delim = rules.find_first_of("~;");

    while(getline(ss, token, rules[delim])) {
      productions.push_back(token);
      delim = rules.find_first_of("~;", (delim + 1));
    }

    for (int i = 0; i < productions.size(); ) {
        if(productions[i].find("#define") == -1)
        {
            prodTable.insert(pair<string, string>(productions[i], productions[i+1]));
            i+=2;
        }
        else
        {
            delim = productions[i].find_last_of(" ");
            token.clear();
            for (int j = delim+1; j < productions[i].length() && !isspace(productions[i][j]); ++j) {
                token += productions[i][j];
            }
            if(productions[i].find("#define start") != -1)
                srule.assign(token);
            else if(productions[i].find("#define len") != -1)
            {
                len = atof(token.c_str());
                len /= 8;
            }

            prodTable.insert(pair<string, string>(productions[i], token));
            i++;
        }
    }
    printProductions();
}



void LSysDecoder::printProductions()
{
    cout<<"Productions:\n";

    for (map<string, string>::iterator i = prodTable.begin(); i != prodTable.end(); ++i)
        if(i->second.compare("") == 0)
            cout<< i->first <<endl;
        else
            cout<< i->first << "->" << i->second<<endl;
//    cout<<"Axiom: "<<srule<<endl;
    cout<<endl;
}



vector< vector<float> > LSysDecoder::grow(cv::Point3f start, int depth, glm::vec3 dir)
{
    vector< vector<float> > finalNodes;
    vector<float> arr;
    string rule = genString(depth);

    arr.push_back(start.x);
    arr.push_back(start.y);
    arr.push_back(start.z);

    int cnt = 0;
    float theta = 25.0f;

    stack<cv::Point3f> st;
    stack<int> aux;

    for (int i = 0; i < rule.size(); ++i)
    {
        if(rule[i] != ']')
        {
            if(rule[i] == '[')
            {
                st.push(cv::Point3f(arr[arr.size()-3], arr[arr.size()-2], arr[arr.size()-1]));
                aux.push(cnt);
            }

            else if(rule[i] == 'F')
            {
//                start.x -= (cnt*(random()%10 + 1));
//                start.y -= len;
//                start.z -= (cnt*(random()%10 + 1));
                int del = (random()%10);

                start.x += len*dir.x;
                start.y += len*dir.y;
                start.z += (len*dir.z - del);

                arr.push_back(start.x);
                arr.push_back(start.y);
                arr.push_back(start.z);

                arr.push_back(start.x);
                arr.push_back(start.y);
                arr.push_back(start.z);
            }

            else if(rule[i] == '+')
            {
                glm::vec3 tvec = glm::normalize(glm::cross(dir, glm::vec3(dir.x-1, 0.0f, 0.0f)));
                glm::mat4 rot = glm::rotate(glm::mat4(1.0f),glm::radians(theta),tvec);
                dir = glm::mat3(rot) * dir;
            }
//                cnt ++;
            else if(rule[i] == '-')
            {
                glm::vec3 tvec = glm::normalize(glm::cross(dir, glm::vec3(dir.x-1, 0.0f, 0.0f)));
                glm::mat4 rot = glm::rotate(glm::mat4(1.0f),glm::radians(-theta),tvec);
                dir = glm::mat3(rot) * dir;
            }
//                cnt --;
        }
        else
        {
            start = st.top();
            cnt = aux.top();

            arr.push_back(arr[arr.size()-3]);
            arr.push_back(arr[arr.size()-3]+1);
            arr.push_back(arr[arr.size()-3]);
            finalNodes.push_back(arr);
            arr.clear();

            arr.push_back(start.x);
            arr.push_back(start.y);
            arr.push_back(start.z);

            st.pop();
            aux.pop();
        }
    }

    return finalNodes;
}
