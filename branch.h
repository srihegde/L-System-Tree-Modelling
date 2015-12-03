#ifndef BRANCH_H
#define BRANCH_H
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
//data structure for one branch
class Branch
{
public:
    vector<Point> polyBranch;
    vector<float> zvalue;
    vector<int> childrenIds; //id's of child branches of this poly branch
    int polyBranchId;
    int polyBranchSize;//number of line segments that make upthis branch
    int parentId;
    int nChildren;
    int consider;//don't consider redundant and terminal branchids for finding l system
    int visited;//if visited =1 then this branch has been paird up wid its similar structure so stop processing it
                //if visited = 0 then keep trying to find the similar structure
    vector<int> similarBranchIds;//similar structure; replace polybranchid with similarbranchid
    Branch();



  //  int getParentId(int branchId);
  //  int getSize(int branchId);
};

#endif // BRANCH_H
