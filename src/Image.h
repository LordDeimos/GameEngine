#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <glbinding/gl/gl.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define PRINTBIN(x) std::bitset<sizeof(x) * 8>(x).to_string().insert(0, "0b").c_str()
#define FOURBYTE(buffer, offset) ((buffer[offset+3] & 0xff) << 24) | ((buffer[offset+2] & 0xff) << 16) | ((buffer[offset+1] & 0xff) << 8) | (buffer[offset] & 0xff)
#define TWOBYTE(buffer, offset) ((buffer[offset+1] & 0xff) << 8) | (buffer[offset] & 0xff)

namespace GameEngine {
	class Image {
	public:
		Image(std::string path);
		virtual ~Image();
		bool ok = false;
		uint8_t* image;
		uint32_t width, height;
	protected:
		uint16_t pix_depth,alpha_length;
	};
	class TgaImage : public Image {
	public:
		TgaImage(std::string path);
		~TgaImage();
	};
	class BmpImage : public Image {
	public:
		BmpImage(std::string path);
		~BmpImage();
	private:
	};
}