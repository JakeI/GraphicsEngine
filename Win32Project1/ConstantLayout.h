#pragma once
#include "Layout.h"

#define INVALID_PADDING_FLOAT	NAN
#define INVALID_PADDING_INT		INT_MAX

#define INVALID_FLOAT			NAN
#define INVALID_INT				INT_MAX

class ConstantLayout : public Layout
{
public:

	class Info : public LayoutInfo {
	public:

		enum PlacementMode {
			TOP_LEFT,
			TOP,
			TOP_RIGHT,
			LEFT,
			CENTER,
			RIGHT,
			BOTTOM_LEFT,
			BOTTOM,
			BOTTOM_RIGHT
		};

		enum ResizeMode {
			KEEP_PROPORTION,
			KEEP_SIZE
		};

		PlacementMode placementMode;
		ResizeMode resizeMode;

		int iw, ih;
		float fw, fh;

		Info(PlacementMode mode, int w, int h);
		Info(PlacementMode mode, float w, float h);

		LayoutInfo* copy() override;
		void del() override;
	};

private:

	void getChildSize(const Info* info, const int w, const int h, int* cw, int* ch);
	void getChildCoards(const Info::PlacementMode mode, const int x, const int y, 
		const int w, const int h, int* cx, int* cy, const int cw, const int ch);

	inline void first(int* coard, const int parent, const int child) { *coard = 0; }
	inline void middel(int* coard, const int parent, const int child) { *coard = (parent - child) / 2; }
	inline void last(int* coard, const int parent, const int child) { *coard = parent - child; }

	float fPadding;
	int iPadding;
	inline bool usesIntPadding();

public:

	inline void setPadding(float padding);
	inline void setPadding(int padding);

	ConstantLayout();
	~ConstantLayout();

	void resize(int x, int y, int w, int h) override;
};

