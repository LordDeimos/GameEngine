#pragma once

#define PRINTBIN(x) std::bitset<sizeof(x) * 8>(x).to_string().insert(0, "0b").c_str()
#define FOURBYTE(buffer, offset) ((buffer[offset+3] & 0xff) << 24) | ((buffer[offset+2] & 0xff) << 16) | ((buffer[offset+1] & 0xff) << 8) | (buffer[offset] & 0xff)
#define TWOBYTE(buffer, offset) ((buffer[offset+1] & 0xff) << 8) | (buffer[offset] & 0xff)

namespace GameEngine {
	class Image {
	public:
		Image(const std::string& path);
		~Image();
		bool ok = false;
		uint8_t* image = nullptr;
		uint32_t width=0, height=0;
		bool hasAlpha();
	private:
		uint16_t pix_depth,alpha_length=0;
		void loadPng(const std::string& path);
		void loadJpg(const std::string& path);
		void loadTga(const std::string& path);
		void loadBmp(const std::string& path);
	};
}