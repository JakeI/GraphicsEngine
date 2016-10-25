#include "ConstantLayout.h"

ConstantLayout::Info::Info(PlacementMode mode, int w, int h) {
	placementMode = mode;
	iw = w;
	ih = h;
	fw = INVALID_FLOAT;
	fh = INVALID_FLOAT;
	resizeMode = KEEP_SIZE;
}

ConstantLayout::Info::Info(PlacementMode mode, float w, float h) {
	placementMode = mode;
	iw = INVALID_INT;
	ih = INVALID_INT;
	fw = w;
	fh = h;
	resizeMode = KEEP_PROPORTION;
}

Layout::LayoutInfo* ConstantLayout::Info::copy() {
	switch (this->resizeMode) {
	case KEEP_PROPORTION:
		return new Info(placementMode, fw, fh);
		break;
	case KEEP_SIZE:
		return new Info(placementMode, iw, ih);
		break;
	}
}

void ConstantLayout::Info::del() {
	delete this;
}

void ConstantLayout::setPadding(float padding) {
	this->fPadding = padding; 
	this->iPadding = INVALID_PADDING_INT; 
}

void ConstantLayout::setPadding(int padding) {
	this->iPadding = padding;
	this->fPadding = INVALID_PADDING_FLOAT;
}

bool ConstantLayout::usesIntPadding() {
	return this->fPadding == INVALID_PADDING_FLOAT;
}

ConstantLayout::ConstantLayout()
{
	this->iPadding = 0;
	this->fPadding = INVALID_PADDING_FLOAT;
}


ConstantLayout::~ConstantLayout()
{
}

void ConstantLayout::resize(int x, int y, int w, int h) {
	Layout::resize(x, y, w, h);

	for (std::list<Component>::iterator it = components.begin(); it != components.end(); ++it) {
		
		Info* info = (Info*)it->info;
		Info::PlacementMode p = info->placementMode;

		int cx = 0, cy = 0, cw = 0, ch = 0;

		getChildSize(info, w, h, &cw, &ch);

		getChildCoards(p, x, y, w, h, &cx, &cy, cw, ch);

		Layout::resize(it->type, it->comp, cx, cy, cw, ch);
	}
}

void ConstantLayout::getChildSize(const Info* info, const int w, const int h, int* cw, int* ch) {
	switch (info->resizeMode) {
	case Info::KEEP_PROPORTION:
		*cw = (int)(info->fw * w);
		*ch = (int)(info->fh * h);
		break;
	case Info::KEEP_SIZE:
		*cw = info->iw;
		*ch = info->ih;
		break;
	}
}

void ConstantLayout::getChildCoards(const Info::PlacementMode mode, 
		const int x, const int y, const int w, const int h, 
		int* cx, int* cy, const int cw, const int ch) {
	
	switch (mode) {
	case Info::TOP_LEFT: case Info::LEFT: case Info::BOTTOM_LEFT:
		first(cx, w, cw);
		break;
	case Info::TOP: case Info::CENTER: case Info::BOTTOM:
		middel(cx, w, cw);
		break;
	case Info::TOP_RIGHT: case Info::RIGHT: case Info::BOTTOM_RIGHT:
		last(cx, w, cw);
		break;
	}

	switch (mode) {
	case Info::BOTTOM_LEFT: case Info::BOTTOM: case Info::BOTTOM_RIGHT:
		first(cy, h, ch);
		break;
	case Info::LEFT: case Info::CENTER: case Info::RIGHT:
		middel(cy, h, ch);
		break;
	case Info::TOP_LEFT: case Info::TOP: case Info::TOP_RIGHT:
		last(cy, h, ch);
		break;
	}

	*cx += x;
	*cy += y;
}