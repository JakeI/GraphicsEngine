#pragma once
#include "WeightedLayout.h"
class VerticalLayout : public WeightedLayout
{
public:
	VerticalLayout();
	~VerticalLayout();

	void resize(int x, int y, int w, int h) override;
};

