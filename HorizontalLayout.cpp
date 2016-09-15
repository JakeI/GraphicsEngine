#include "HorizontalLayout.h"
#include "Scene.h"



HorizontalLayout::HorizontalLayout() : WeightedLayout()
{
}


HorizontalLayout::~HorizontalLayout()
{
}


void HorizontalLayout::resize(int x, int y, int w, int h) {

	WeightedLayout::resize(x, y, w, h);

	int X = 0, W = 0;
	//float cumulativWeight = 0.0f;
	int spredWidth = w - sizeSum;
		
	for (std::list<Component>::iterator it = components.begin(); it != components.end(); ++it) {
		
		if (((Info*)it->info)->hasIntSize()) {
			W = (int)((Info*)it->info)->size;
		} else {
			//X = (int)((cumulativWeight / weightSum)*w);
			W = (int)((((Info*)it->info)->weight / weightSum)*w);
		}
		
		//cumulativWeight += ((Info*)it->info)->weight;

		Layout::resize(it->type, it->comp, X, y, W, h);
		X += W;
	}
}
