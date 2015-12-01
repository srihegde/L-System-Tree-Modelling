#include "modeller.h"
#include <cstdlib>
#include <cmath>

Modeller::Modeller(Branch blist[])
{
    branchList = blist;
    numBranches = blist[0].childrenIds.size();

    float angle = 0.0f;
    vector<float> arr;

    arr.push_back(blist[0].polyBranch[0].x);
    arr.push_back(blist[0].polyBranch[0].y);
    arr.push_back(0.0f);
    blist[0].zvalue.push_back(0.0f);

    for (int i = 1; i < blist[0].polyBranch.size()-1; ++i) {
        arr.push_back(blist[0].polyBranch[i].x);
        arr.push_back(blist[0].polyBranch[i].y);
        arr.push_back(0.0f);
        blist[0].zvalue.push_back(0.0f);

        arr.push_back(blist[0].polyBranch[i].x);
        arr.push_back(blist[0].polyBranch[i].y);
        arr.push_back(0.0f);
    }
    arr.push_back(blist[0].polyBranch[blist[0].polyBranch.size()-1].x);
    arr.push_back(blist[0].polyBranch[blist[0].polyBranch.size()-1].y);
    arr.push_back(0.0f);
    blist[0].zvalue.push_back(0.0f);

    finalNodes.push_back(arr);

    int delta;
    for (int i = 0; i < numBranches; ++i) {
        branchList[ branchList[0].childrenIds[i] ].zvalue.push_back(findNearestNode(branchList[branchList[0].childrenIds[i]], branchList[branchList[0].childrenIds[i]].polyBranch[0].x, branchList[branchList[0].childrenIds[i]].polyBranch[0].y));
        placeBranches(branchList[ branchList[0].childrenIds[i] ], angle);
        delta = M_PI/(rand()%10 + 10);     // Random perturbations.
        angle += (((2*M_PI) / numBranches) + delta);

    }

    // For debugging purposes
    printFinalNodes();
}

vector<float> Modeller::getFinalNodes()
{
//    return finalNodes;
}

Point2f Modeller::rotate(float x, float y, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    Point2f p(x*c - y*s, x*s + y*c);
//    printf("******* %f %f %f\n",c,s,angle);
    return p;
}

void Modeller::placeBranches(Branch br, float angle)
{
    // Print coordinates here in DFS approach.
    Point2f tmp;
    vector<float> arr;

    arr.push_back(br.polyBranch[0].x);
    arr.push_back(br.polyBranch[0].y);
    arr.push_back(br.zvalue[0]);

    for (int i = 1; i < br.polyBranch.size()-1; ++i)
    {
        tmp = rotate(br.polyBranch[i].x, 0.0, angle);
        br.zvalue.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);

        arr.push_back(br.polyBranch[i].x);
        arr.push_back(br.polyBranch[i].y);
        arr.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);

        arr.push_back(br.polyBranch[i].x);
        arr.push_back(br.polyBranch[i].y);
        arr.push_back(tmp.y * ((float)i/(float)(br.polyBranch.size())) + br.zvalue[0]);
    }

    tmp = rotate(br.polyBranch[br.polyBranch.size()-1].x, 0.0, angle);
    br.zvalue.push_back(tmp.y + br.zvalue[0]);

    arr.push_back(br.polyBranch[br.polyBranch.size()-1].x);
    arr.push_back(br.polyBranch[br.polyBranch.size()-1].y);
    arr.push_back(tmp.y + br.zvalue[0]);

    finalNodes.push_back(arr);

    if(!br.childrenIds.empty())
    {
        for (int i = 0; i < br.childrenIds.size(); ++i)
        {
            branchList[ br.childrenIds[i] ].zvalue.push_back(findNearestNode(branchList[br.childrenIds[i]], branchList[br.childrenIds[i]].polyBranch[0].x, branchList[br.childrenIds[i]].polyBranch[0].y));
            placeBranches(branchList[ br.childrenIds[i] ], angle);
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
        fprintf(f,"%d\n",finalNodes[i].size()/3);
        for (int j = 0; j < finalNodes[i].size(); j+=3) {
            fprintf(f,"%f %f %f\n", finalNodes[i][j], finalNodes[i][j+1], finalNodes[i][j+2]);
        }
    }
    printf("Printed nodes to file successfully\n");
    fclose(f);
}

float Modeller::findNearestNode(Branch br, float x, float y)
{
    Branch par = branchList[br.parentId];

    for (int i = 0; i < par.polyBranch.size(); ++i) {
       if(fabs(par.polyBranch[i].x - x) < 40 && fabs(par.polyBranch[i].y - y) < 40)
       {
//           printf("Found !!!\n");
           return par.zvalue[i];
       }
    }

    printf("%d: %d\n", br.parentId, par.zvalue.size());
    return par.zvalue[par.zvalue.size()/2];
}


