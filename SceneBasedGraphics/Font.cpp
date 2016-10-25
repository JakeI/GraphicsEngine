#include "Font.h"

void Font::load(const std::string & path) {
	std::ifstream in(path, std::ios::in);

	if (in.is_open()) {
		
		std::string line;
		FontPart currentPart;
		bool partStarted = false;

		while (getline(in, line)) {
			
			if (line == "" || line[0] == '#') // ignore blank lines / comments
				continue;

			std::stringstream ss(line);
			std::string type, flag;
			std::vector<std::string> flags;
			
			ss >> type;

			while (ss >> flag) {
				flags.push_back(flag);
			}

			if (type == "page") {
				handelPage(flags, path);
				continue;
			}
			
			if (type == "info" && partStarted) {
				currentPart.finalize();
				fonts.push_back(currentPart);
				currentPart.reset();
			}

			currentPart.handel(type, flags);
			partStarted = true;
		}

		if (partStarted) {
			currentPart.finalize();
			fonts.push_back(currentPart);
		}

	}

	in.close();
}

void Font::handelPage(std::vector<std::string> & flags, const std::string & path) {
	if (texture == nullptr) { // TODO: Add support for multiple pages
		std::string key, value;
		for (auto flag : flags) {
			std::stringstream ss(flag);
			getline(ss, key, '=');
			getline(ss, value);
			
			if (key == "file") {
				texturePath = Strings::pathInSameDir(path, Strings::stripQuotes(value));
				texture = new Texture(texturePath);
			}

		}
	}
}

Font::FontPart::FontPart() {
	reset();
}

Font::FontPart::~FontPart() {
}

void Font::FontPart::finalize() {
	info.finalize();
	common.finalize();
}

void Font::FontPart::handelInfo(std::vector<std::string> & flags) {
	std::string key, value;
	for (auto flag : flags) {
		std::stringstream ss(flag);
		getline(ss, key, '=');
		getline(ss, value);
		info.set(key, value);
	}
}

void Font::FontPart::Info::finalize() {
	
}

void Font::FontPart::Info::readPadding(std::string & value) {

	std::vector<int> flags(4);
	std::string flag;
	for (std::string::iterator it = value.begin(); it != value.end(); ++it) {
		if (*it == ',') {
			flags.push_back(std::stoi(flag));
			flag = "";
		} else {
			flag = flag + *it;
		}
	}
	paddingTop = flags[0];
	paddingRight = flags[1];
	paddingBottom = flags[2];
	paddingLeft = flags[3];

	paddingWidth = paddingRight - paddingLeft;
	paddingHeight = paddingBottom - paddingTop;
}

void  Font::FontPart::Info::set(std::string & key, std::string & value) {
	if (key == "face") face = value;
	else if (key == "size") size = std::stoi(value);
	else if (key == "bold") bold = (bool)std::stoi(value);
	else if (key == "italic") italic = (bool)std::stoi(value);
	else if (key == "charset") charset = value;
	else if (key == "unicode") unicode = (bool)std::stoi(value);
	else if (key == "stretchH") stretchH = std::stoi(value);
	else if (key == "smooth") smooth = (bool)std::stoi(value);
	else if (key == "padding") readPadding(value);
	else if (key == "spacing") spacing = value;
}

void Font::FontPart::handelCommon(std::vector<std::string> & flags) {
	std::string key, value;
	for (auto flag : flags) {
		std::stringstream ss(flag);
		getline(ss, key, '=');
		getline(ss, value);
		common.set(key, value);
	}
}

void Font::FontPart::Common::set(std::string & key, std::string & value) {
	if (key == "lineHeight") lineHeight = std::stoi(value);
	else if (key == "base") base = std::stoi(value);
	else if (key == "scaleW") scaleW = std::stoi(value);
	else if (key == "scaleH") scaleH = std::stoi(value);
}

void Font::FontPart::Common::finalize() {
	lineHeightf = (float)lineHeight / (float)scaleH;
	basef = (float)base / (float)scaleH;
}

void Font::FontPart::handelScalar(std::vector<std::string> & flags) {
	std::string key, value;
	for (auto flag : flags) {
		std::stringstream ss(flag);
		getline(ss, key, '=');
		getline(ss, value);
		
		if (key == "r") scalar.r = std::stof(value);
		else if (key == "g") scalar.g = std::stof(value);
		else if (key == "b") scalar.b = std::stof(value);
		else if (key == "a") scalar.a = std::stof(value);
	}
}

void Font::FontPart::handelChars(std::vector<std::string> & flags) {
	std::string key, value;
	for (auto flag : flags) {
		std::stringstream ss(flag);
		getline(ss, key, '=');
		getline(ss, value);
		common.set(key, value);
		
		if (key == "count") charsCount = std::stoi(value);
	}
}

void Font::FontPart::handelChar(std::vector<std::string> & flags) {
	std::string key, value;
	Character character;
	char id = 0;
	for (auto flag : flags) {
		std::stringstream ss(flag);
		getline(ss, key, '=');
		getline(ss, value);

		if (key == "id") id = (char)std::stoi(value);
		else character.set(key, value, common.scaleW, common.scaleH);
	}

	character.finalize();
	chars[id] = character;
}

void Font::FontPart::Character::set(std::string & key, std::string & value, int scaleW, int scaleH) {
	if (key == "x") xf = (float)std::stoi(value) / (float)scaleW;
	else if (key == "y") yf = (float)std::stoi(value) / (float)scaleH;
	else if (key == "width") {
		widthi = (float)std::stoi(value);
		widthf = widthi / (float)scaleW;
	} else if (key == "height") {
		heighti = (float)std::stoi(value);
		heightf = heighti / (float)scaleH;
	}
	else if (key == "xoffset") xoffsetf = (float)std::stoi(value); // / (float)scaleW;
	else if (key == "yoffset") yoffsetf = (float)std::stoi(value); // / (float)scaleH;
	else if (key == "xadvance") xadvancef = (float)std::stoi(value); // / (float)scaleW;
}

void Font::FontPart::Character::finalize() {
	aspectf = widthf / heightf;
}

void Font::FontPart::handelKernings(std::vector<std::string> & flags) {
	// No idea what this is good for
}

void Font::FontPart::handel(std::string & type, std::vector<std::string> & flags) {
	if (type == "char") // most lickly case first
		handelChar(flags);
	else if (type == "info") handelInfo(flags);
	else if (type == "common") handelCommon(flags);
	else if (type == "scalar") handelScalar(flags);
	else if (type == "chars") handelChar(flags);
	else if (type == "kernings") handelKernings(flags);
}

Font::Font(const std::string & path) :
	Resource(path)
{
	
}

void Font::init_resource(const std::string & path) {
	texture = nullptr;
	load(path);
	texture->init(texturePath);
}

Font::~Font() {
	if (texture != nullptr)
		delete texture;
}

Font::FontPart* Font::getFontPart(FONT_TYPE type) {
	try {
		return &fonts.at(type);
	}
	catch (std::out_of_range& r) {
		ilog->printError("getFontPart called with non exitsing FONT_TYPE: '" + type + '\'');
		return nullptr;
	}
}
