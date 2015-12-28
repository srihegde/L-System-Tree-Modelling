#ifndef MODELLER_H
#define MODELLER_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "branch.h"
#include "lsysdecoder.h"

using namespace std;
using namespace cv;

#define SIZE 500

class Modeller
{
private:
    Branch *branchList;
    int numBranches;
    vector< vector<float> > finalNodes;
    vector<float> girth;
    vector<float> brLen;

protected:
    Point2f rotate(float x, float y, float angle, Point2f axis);
    void placeBranches(Branch br, float angle, Point2f axis);
    void printFinalNodes();
    void modelIn3D();
    float findNearestNode(Branch br, Branch child);
    int findNearestxy(Branch br, Branch child);

public:
    Modeller(Branch blist[100], string rules);
    vector<float> getFinalNodes();
    LSysDecoder *lsys;
};

#endif // MODELLER_H
