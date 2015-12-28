/***************************************************************************************************

  L-System Syntax:

  * Instead of '->' assignment '~' symbol should be used.
  * There must be a '#define start <symbol>' statement that highlights the starting production
    or axiom, '<symbol>'.
  * Length is defined by '#define len <num>' to define the length of each 'F' operator as <num>
  * Rest all symbols have their meaning according to the convention.

***************************************************************************************************/


#ifndef LSYSDECODER_H
#define LSYSDECODER_H

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <utility>
#include <stack>

#include <opencv2/opencv.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

class LSysDecoder
{
private:
    map<string, string> prodTable;
    string srule;
    float len;

protected:
    string genString(int depth);

public:
    LSysDecoder(string rules);
    void printProductions();
    vector< vector<float> > grow(cv::Point3f start, int depth, glm::vec3 dir);
};

#endif // LSYSDECODER_H
