#include "WeightedLayout.h"



WeightedLayout::WeightedLayout()
{
	weightSum = 0.0f;
	sizeSum = 0;
}


WeightedLayout::~WeightedLayout()
{
}

void WeightedLayout::addLayoutInfo(LayoutInfo* info, ComponentType type) {
	weightSum += ((Info*)info)->weight;
	sizeSum += ((Info*)info)->size;
}

void WeightedLayout::removeLayoutInfo(LayoutInfo* info, ComponentType type) {
	weightSum -= ((Info*)info)->weight;
	sizeSum -= ((Info*)info)->size;
}
