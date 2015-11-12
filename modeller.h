#ifndef MODELLER_H
#define MODELLER_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "branch.h"

using namespace std;
using namespace cv;

#define SIZE 500
#define PI 3.14159

class Modeller
{
private:
    Branch *branchList;
    int numBranches;
    vector<float> finalNodes;

protected:
    Point2f rotate(float x, float y, float angle);
    void placeBranches(Branch br, float angle);
    void printFinalNodes();

public:
    Modeller(Branch blist[100]);
    vector<float> getFinalNodes();
};

#endif // MODELLER_H
