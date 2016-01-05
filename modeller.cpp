/***************************************************************************************************

3D Modelling Problems (and Status)

 * Radius Adjustment: Preventing overshooting of branches
 * Surface conversion
 * Enabling shading     // Done (Simple Lambertian shading)
 * Tapering as a function of length     // Done
 * Inserting Randomness in L-System productions     // Done
 * Realistic L-system grown branches - girth and orientation    // Orientation done
 * Computationally heavy (frequent crashes) when enabled L-system growth

***************************************************************************************************/

#include "modeller.h"
#include <cstdlib>
#include <cmath>

float len;
int flag = 1;       // Set flag = 1 for viewing intricate branches.

Modeller::Modeller(Branch blist[], string rules)
{
    branchList = blist;
    numBranches = blist[0].childrenIds.size();

    lsys = new LSysDecoder(rules);

    float angle = 0.0f;
    vector<float> arr;

    arr.push_back(blist[0].polyBranch[0].x);
    arr.push_back(blist[0].polyBranch[0].y);
    arr.push_back(0.0f);
    blist[0].zvalue.push_back(0.0f);
    blist[0].radius.push_back(1.0f);
    girth.push_back(0.9f);
    len = 0.0f;

    for (int i = 1; i < blist[0].polyBranch.size()-1; ++i)
    {
        arr.push_back(blist[0].polyBranch[i].x);
        arr.push_back(blist[0].polyBranch[i].y);
        arr.push_back(0.0f);
        blist[0].zvalue.push_back(0.0f);
        blist[0].radius.push_back(blist[0].radius[blist[0].radius.size()-1] - 0.1f);
        len += (sqrt(pow(arr[arr.size()-6] - arr[arr.size()-3],2) + pow(arr[arr.size()-5] - arr[arr.size()-2],2) + pow(arr[arr.size()-4] - arr[arr.size()-1],2)));

        arr.push_back(blist[0].polyBranch[i].x);
        arr.push_back(blist[0].polyBranch[i].y);
        arr.push_back(0.0f);
    }
    arr.push_back(blist[0].polyBranch[blist[0].polyBranch.size()-1].x);
    arr.push_back(blist[0].polyBranch[blist[0].polyBranch.size()-1].y);
    arr.push_back(0.0f);
    blist[0].zvalue.push_back(0.0f);
    blist[0].radius.push_back(blist[0].radius[blist[0].radius.size()-1] - 0.1f);

    len += (sqrt(pow(arr[arr.size()-6] - arr[arr.size()-3],2) + pow(arr[arr.size()-5] - arr[arr.size()-2],2) + pow(arr[arr.size()-4] - arr[arr.size()-1],2)));
    brLen.push_back(len);
    finalNodes.push_back(arr);

    // Drawing intricate branches for main trunk
    if(flag)
    {
        int depth = random()%4 + 3;
        Point3f start(arr[arr.size()-3], arr[arr.size()-2], arr[arr.size()-1]);
        Point3f tmpo(blist[0].polyBranch[blist[0].polyBranch.size()-1] - blist[0].polyBranch[blist[0].polyBranch.size()-2]);
        glm::vec3 dir(tmpo.x, tmpo.y, tmpo.z);
        vector< vector<float> > tarr;

        tarr = lsys->grow(start, depth, dir);

        for (int i = 0; i < tarr.size(); ++i)
        {
            finalNodes.push_back(tarr[i]);
            girth.push_back(0.03f);
//            girth.push_back(blist[0].radius[blist[0].radius.size()-1]-0.4);
        }
    }

    int mini= 10000.0f, maxi = -10000.0f;
    for (int i = 0; i < blist[0].polyBranch.size(); ++i) {
        if(mini > blist[0].polyBranch[i].x)
            mini = blist[0].polyBranch[i].x;
        if(maxi <= blist[0].polyBranch[i].x)
            maxi = blist[0].polyBranch[i].x;
    }

    int delta,turn=0;
    Point2f axis((maxi + mini)/2.0f, 0.0f);
    for (int i = 0; i < numBranches; ++i, turn = (turn+1)%2) {
//        angle += M_PI/3;    // Hard Coded distribution
//        angle += (((2*M_PI) / numBranches)); //Normal distribution

        // alternate 90 degree placement
        if(turn)
            angle += (((2*M_PI) / numBranches)); //Normal distribution
        else
            angle += (((2*M_PI) / numBranches) + (M_PI/2)); //Normal distribution

        delta = M_PI/(rand()%10 + 10);     // Random perturbations.
//        angle += (((2*M_PI) / numBranches) + delta); //Random distribution

        branchList[ branchList[0].childrenIds[i] ].zvalue.push_back(findNearestNode(branchList[0], branchList[branchList[0].childrenIds[i]]));
        int index = findNearestxy(branchList[0], branchList[branchList[0].childrenIds[i]]);
        index++;
        branchList[ branchList[0].childrenIds[i] ].radius.push_back(branchList[0].radius[index] - 0.01);
        girth.push_back(branchList[0].radius[index] - 0.01);

        placeBranches(branchList[ branchList[0].childrenIds[i] ], angle, axis);
    }

    // For debugging purposes
    printFinalNodes();
}



vector<float> Modeller::getFinalNodes()
{
//    return finalNodes;
}



Point2f Modeller::rotate(float x, float y, float angle, Point2f axis)
{
    float s = sinf(angle);
    float c = cosf(angle);

    Point2f p((x-axis.x)*c - (y-axis.y)*s + axis.x, (x-axis.x)*s + (y-axis.y)*c + axis.y);
//    printf("******* %f %f \n",p.x, p.y);
    return p;
}



void Modeller::placeBranches(Branch br, float angle,  Point2f axis)
{
    // Print coordinates here in DFS approach.
    Point2f tmp;
    vector<float> arr;

    if(br.radius[0] > branchList[br.parentId].radius[0])
        br.radius[0] = branchList[br.parentId].radius[0]-0.01;
    arr.push_back(br.polyBranch[0].x);
    arr.push_back(br.polyBranch[0].y);
    arr.push_back(br.zvalue[0]);
    len = 0.0f;

    for (int i = 1; i < br.polyBranch.size()-1; ++i)
    {
        tmp = rotate(br.polyBranch[i].x, 0.0, angle, axis);
        br.zvalue.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);
        br.radius.push_back(br.radius[br.radius.size()-1] - 0.1f);

        arr.push_back(br.polyBranch[i].x);    // Scaling enabled
//        arr.push_back(tmp.x);      // Scaling disabled
        arr.push_back(br.polyBranch[i].y);
        arr.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);

        len += (sqrt(pow(arr[arr.size()-6] - arr[arr.size()-3],2) + pow(arr[arr.size()-5] - arr[arr.size()-2],2) + pow(arr[arr.size()-4] - arr[arr.size()-1],2)));

        arr.push_back(br.polyBranch[i].x);
//        arr.push_back(tmp.x);      // Scaling disabled
        arr.push_back(br.polyBranch[i].y);
        arr.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);
    }

    tmp = rotate(br.polyBranch[br.polyBranch.size()-1].x, 0.0, angle, axis);
    br.zvalue.push_back(tmp.y + br.zvalue[0]);

    arr.push_back(br.polyBranch[br.polyBranch.size()-1].x);
//    arr.push_back(tmp.x);      // Scaling disabled
    arr.push_back(br.polyBranch[br.polyBranch.size()-1].y);
    arr.push_back(tmp.y + br.zvalue[0]);

    len += (sqrt(pow(arr[arr.size()-6] - arr[arr.size()-3],2) + pow(arr[arr.size()-5] - arr[arr.size()-2],2) + pow(arr[arr.size()-4] - arr[arr.size()-1],2)));
    brLen.push_back(len);
    finalNodes.push_back(arr);


    // Drawing intricate branches
    if(flag)
    {
        int depth = random()%4 + 3;
        Point3f start(arr[arr.size()-3], arr[arr.size()-2], arr[arr.size()-1]);
        Point3f tmpo(br.polyBranch[br.polyBranch.size()-1] - br.polyBranch[br.polyBranch.size()-2]);
        glm::vec3 dir(tmpo.x, tmpo.y, tmpo.z);
        vector< vector<float> > tarr;

        tarr = lsys->grow(start, depth, dir);

        for (int i = 0; i < tarr.size(); ++i)
        {
            finalNodes.push_back(tarr[i]);
            girth.push_back(0.03f);
//            girth.push_back(br.radius[br.radius.size()-1]-0.1);
        }
    }

    if(!br.childrenIds.empty())
    {
        int index;
        for (int i = 0; i < br.childrenIds.size(); ++i)
        {
            branchList[ br.childrenIds[i] ].zvalue.push_back(findNearestNode(br, branchList[br.childrenIds[i]]));
            index = findNearestxy(br,branchList[br.childrenIds[i]]);
            index+=4;
            if(index > br.radius.size()) index = br.radius.size()-1;
//            branchList[ br.childrenIds[i] ].polyBranch[0] = br.polyBranch[index];
            branchList[ br.childrenIds[i] ].radius.push_back(br.radius[index] - 0.01);
            girth.push_back(br.radius[index] - 0.1);
            placeBranches(branchList[ br.childrenIds[i] ], angle, axis);
        }
    }

}



void Modeller::printFinalNodes()
{
    FILE *f = fopen("./output.txt", "w");

    printf("Printing Nodes\n");
    fprintf(f,"%d\n",finalNodes.size());
    for (int i = 0; i < finalNodes.size(); i++)
    {
        fprintf(f,"%d %f %f\n",finalNodes[i].size()/3, girth[i], brLen[i]);
        printf("%f ",girth[i]);
        for (int j = 0; j < finalNodes[i].size(); j+=3) {
            fprintf(f,"%f %f %f\n", finalNodes[i][j], finalNodes[i][j+1], finalNodes[i][j+2]);
        }
    }
    printf("\nPrinted nodes to file successfully\n");
    fclose(f);
}



float Modeller::findNearestNode(Branch br, Branch child)
{
    float x = child.polyBranch[0].x, y = child.polyBranch[0].y;
    int index=0;
    float min = 10000.0f, cur;

    for (int i = br.polyBranch.size()-1; i >= 0 ; --i) {
        cur = pow(fabs(br.polyBranch[i].x - x),2) + pow(fabs(br.polyBranch[i].y - y),2);
       if(cur<min)
       {
           min = cur;
           index = i;
       }
    }

    return br.zvalue[index];
}



int Modeller::findNearestxy(Branch br, Branch child)
{
    float x = child.polyBranch[0].x, y = child.polyBranch[0].y;
    int index=0;
    float min = 1000.0f, cur;

    for (int i = br.polyBranch.size()-1; i >= 0 ; --i) {
       cur = pow(fabs(br.polyBranch[i].x - x),2) + pow(fabs(br.polyBranch[i].y - y),2);
       if( cur < min)
       {
           min = cur;
           index = i;
       }
    }
    return index;
}


