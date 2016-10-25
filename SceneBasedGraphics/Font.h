#pragma once

#include "StdAfx.h"
#include "Texture.h"
#include "Strings.h"

typedef int FONT_TYPE;
#define FONT_STD				0
#define FONT_BOLD				1
#define FONT_ITALIC				2
#define FONT_BOLD_ITALIC		3
#define FONT_COMPONENT_COUNT	4

class Font : public Resource
{
private:
	
	void load(const std::string & path);

	void handelPage(std::vector<std::string> & flags, const std::string & path);

public:

	class FontPart
	{
	private:

		void handelInfo(std::vector<std::string> & flags);
		void handelCommon(std::vector<std::string> & flags);
		void handelScalar(std::vector<std::string> & flags);
		void handelChars(std::vector<std::string> & flags);
		void handelChar(std::vector<std::string> & flags);
		void handelKernings(std::vector<std::string> & flags);

	public:

		struct Info {
			std::string face;
			int size;
			bool bold;
			bool italic;
			std::string charset;
			bool unicode;
			int stretchH;
			bool smooth;
			bool aa;
			int paddingTop;
			int paddingRight;
			int paddingBottom;
			int paddingLeft;
			std::string spacing; // same thing as with padding

			int paddingWidth;
			int paddingHeight;

			void finalize();
			void set(std::string & key, std::string & value);
			void readPadding(std::string & value);
		};

		struct Common {
			int lineHeight;
			int base;
			int scaleW;
			int scaleH;
			// ignore pages and packed for know

			float lineHeightf; // respective to the texture height
			float basef;

			void finalize();
			void set(std::string & key, std::string & value);
		};

		struct Character {
			float xf;
			float yf;
			float widthf;
			float widthi;
			float heightf;
			float heighti;
			float xoffsetf;
			float yoffsetf;
			float xadvancef;
			// ignore page and chnl for know

			// calculated to save later calc power
			float aspectf;

			void set(std::string & key, std::string & value, int scaleW, int scaleH);
			void finalize();
		};
		
		Info info;
		Common common;
		glm::vec4 scalar;
		int charsCount;
		std::map<char, Character> chars;

		FontPart();
		~FontPart();

		void handel(std::string & type, std::vector<std::string> & flags);
		void reset(){} // implement later: reset all variables to something reasonable (in case the font file is broken those defaults will be used)
		void finalize();
	};

	std::vector<FontPart> fonts;
	Texture* texture;
	std::string texturePath;

	FontPart* getFontPart(FONT_TYPE type);

	Font(const std::string & path); // used by the Resource Manager expectes a call of init(path)
	~Font();

	// Resouce Features
	static Resource* alloc(const std::string & path) { return new Font(path); }
	void init_resource(const std::string & path) override;
};

