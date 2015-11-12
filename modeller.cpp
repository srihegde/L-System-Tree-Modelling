#include "modeller.h"

Modeller::Modeller(Branch blist[])
{
    branchList = blist;
    numBranches = blist[0].childrenIds.size();

    float angle = 0.0f;
    for (int i = 0; i < numBranches; ++i) {
        placeBranches(branchList[ branchList[0].childrenIds[i] ], angle);
        angle += ((2*PI) / numBranches);

    }

    // For debugging purposes
    printFinalNodes();
}

vector<float> Modeller::getFinalNodes()
{
    return finalNodes;
}

Point2f Modeller::rotate(float x, float y, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    Point2f p(x*c - y*s, x*s + y*c);
    // p.x = x*c - y*s, p.y = x*s + y*c;
    // printf("%f %f\n",x*c - y*s, x*s + y*c);
//    printf("******* %f %f %f\n",c,s,angle);
    return p;
}

void Modeller::placeBranches(Branch br, float angle)
{
    // Print coordinates here.
    Point2f tmp;

    finalNodes.push_back(br.polyBranch[0].x);
    finalNodes.push_back(br.polyBranch[0].y);
    finalNodes.push_back(0.0f);

//    for (int i = 1; i < br.polyBranch.size(); ++i)
//    {
//        tmp = rotate(br.polyBranch[i].x, 0.0, angle);
//        finalNodes.push_back(br.polyBranch[i].x);
//        finalNodes.push_back(br.polyBranch[i].y);
//        finalNodes.push_back(tmp.y);
//    }
//    finalNodes.push_back(finalNodes);

    tmp = rotate(br.polyBranch[0].x, 0.0, angle);
    finalNodes.push_back(tmp.x);
    finalNodes.push_back(br.polyBranch[0].y);
    finalNodes.push_back(tmp.y);

    tmp = rotate(br.polyBranch[br.polyBranch.size() - 1].x, 0.0, angle);
    finalNodes.push_back(tmp.x);
    finalNodes.push_back(br.polyBranch[br.polyBranch.size() - 1].y);
    finalNodes.push_back(tmp.y);

    if(!br.childrenIds.empty())
    {
        for (int i = 0; i < br.childrenIds.size(); ++i)
            placeBranches(branchList[ br.childrenIds[i] ], angle);
    }
}

void Modeller::printFinalNodes()
{
    FILE *f = fopen("./output.txt", "w");

    printf("Printing Nodes\n");
    fprintf(f,"%d\n",finalNodes.size()/3);
    for (int i = 0; i < finalNodes.size(); i+=3)
    {
        fprintf(f,"%f %f %f\n", finalNodes[i], finalNodes[i+1], finalNodes[i+2]);
    }
    printf("Printed nodes to file successfully\n");
}


