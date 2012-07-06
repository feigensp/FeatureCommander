#include "stnodecolordistribution.h"

STNodeColorDistribution::STNodeColorDistribution()
{
    list = new QList <Interval*>();
    grey = false;
}

void STNodeColorDistribution::writeToFeatureDistributionList(int index, int start, int offset)
{
    Interval *interval = new Interval(start,offset,grey);
    if (index < list->size())
        list->replace(index,interval);
    else
        list->insert(index,interval);

    if (grey)
        grey = false;
    else
        grey = true;
}

