#pragma once
#include "Layout.h"

class WeightedLayout : public Layout
{
public:

	class Info : public LayoutInfo {
	public:
		float weight;
		int size;
		Info(float weight = 1.0f) { this->weight = weight; size = 0; }
		Info(int size) { this->size = size; this->weight = 0.0f; }

		inline bool hasIntSize() { return size > 0 && weight == 0.0f; }

		LayoutInfo* copy() override { 
			if (hasIntSize())
				return new Info(size);
			else
				return new Info(this->weight); 
		}
		void del() override { delete this; }
	};

protected:

	float weightSum;
	int sizeSum;

public:
	WeightedLayout();
	~WeightedLayout();

	inline void addLayoutInfo(LayoutInfo* info, ComponentType type) override;
	inline void removeLayoutInfo(LayoutInfo* info, ComponentType type) override;
};

