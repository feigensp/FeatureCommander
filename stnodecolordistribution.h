#ifndef STNODECOLORDISTRIBUTION_H
#define STNODECOLORDISTRIBUTION_H

#include <QList>
struct Interval{

    int start;
    int offset;
    bool greyTone;

    Interval(int s, int o, bool g){
        start = s;
        offset = o;
        greyTone = g;
        //Feature kommt nicht vor, wenn s = -1
    }

};

class STNodeColorDistribution
{
public:
    void writeToFeatureDistributionList(int index, int start, int offset);
    STNodeColorDistribution();
    QList <Interval*> *list;
    bool grey;

private:



};

#endif // STNODECOLORDISTRIBUTION_H
