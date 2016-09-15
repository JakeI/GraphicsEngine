#pragma once

#include "StdAfx.h"
#include "WeightedLayout.h"


class HorizontalLayout : public WeightedLayout
{
public:
	HorizontalLayout();
	~HorizontalLayout();

	void resize(int x, int y, int w, int h) override;
};

