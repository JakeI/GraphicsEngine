#include "VerticalLayout.h"
#include "Scene.h"



VerticalLayout::VerticalLayout() : WeightedLayout()
{
}


VerticalLayout::~VerticalLayout()
{
}

void VerticalLayout::resize(int x, int y, int w, int h) {
	
	WeightedLayout::resize(x, y, w, h);
	
	int Y = 0, H = 0;
	//float cumulativWeight = 0.0f;
	int spreadHight = h - sizeSum;

	for (std::list<Component>::iterator it = components.begin(); it != components.end(); ++it) {

		if (((Info*)it->info)->hasIntSize()) {
			H = (int)((Info*)it->info)->size;
		} else {
			//Y = (int)((cumulativWeight / weightSum)*spreadHight);
			H = (int)((((Info*)it->info)->weight / weightSum)*spreadHight);
		}
		
		//cumulativWeight += ((Info*)it->info)->weight;

		Layout::resize(it->type, it->comp, x, Y, w, H);
		Y += H;
	}
}
