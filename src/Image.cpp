#include "Image.h"

using namespace GameEngine;
namespace fs = std::experimental::filesystem::v1;

Image::Image(std::string path) {
	std::ifstream file;
	file.open(path, std::ios::binary);
	if (!file.is_open()) {
		file.close();
		ok = false;
		return;
	}
	ok = true;
	file.close();
}

Image::~Image() {

}

BmpImage::BmpImage(std::string path) : Image(path) {
	if (!ok) return;

	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();

	file.seekg(0, file.beg);
	char header[14];
	file.read(header, 14);

	uint16_t type = TWOBYTE(header, 0);

	if (type != 0x4d42) {
		file.close();
		ok = false;
		return;
	}

	uint32_t hSize = FOURBYTE(header, 2);
	uint32_t pix_loc = FOURBYTE(header, 10);
	char dibHeader[40];
	file.read(dibHeader, 40);
	width = FOURBYTE(dibHeader, 4);
	height = FOURBYTE(dibHeader, 8);
	pix_depth = TWOBYTE(dibHeader, 14);
	uint32_t compress_method = FOURBYTE(dibHeader, 16);
	uint32_t imsize = FOURBYTE(dibHeader, 20);
	imsize = (imsize == 0) ? 4 * height*ceil((pix_depth*width) / 32) : imsize;
	uint8_t* temp_image = new uint8_t[imsize];
	file.seekg(pix_loc);
	file.read((char*)temp_image, imsize);
	file.close();
	int counter = 0;
	for (int i = 0; i < (height) / 2; i++) {//Flip
		uint8_t* row = new uint8_t[width * 3];
		memcpy(row, temp_image + (i*width * 3), width * 3);
		memcpy(temp_image + (i*width * 3), temp_image + (((height - 1) - i)*width * 3), width * 3);
		memcpy(temp_image + (((height - 1) - i)*width * 3), row, width * 3);
		delete[] row;
	}
	counter = 0;
	image = new uint8_t[imsize];
	while (counter <= imsize) {
		//Convert to RGBA
		image[counter] = temp_image[counter + 2];
		image[counter + 1] = temp_image[counter + 1];
		image[counter + 2] = temp_image[counter + 0];
		counter += 3;
	}
	ok = true;
}

BmpImage::~BmpImage() {
	delete[] image;
}

TgaImage::TgaImage(std::string path) : Image(path) {
	if (!ok) return;
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();

	file.seekg(0, file.beg);
	char header[18];
	file.read(header, 18);

	width = (header[13] << 8) | (header[12] & 0xff);
	height = (header[15] << 8) | (header[14] & 0xff);
	pix_depth = header[16];
	alpha_length = header[17];

	int imsize = (pix_depth / 8)*width*height;
	uint8_t* temp_image = new uint8_t[imsize];
	if (imsize > length) {
		ok = false;
		return;//Filter out compressed textures
	}
	image = new uint8_t[imsize];
	file.read((char*)temp_image, imsize);
	file.close();
	int counter = 0;
	for (int i = 0; i < (height) / 2; i++) {
		uint8_t* row = new uint8_t[width * 4];
		memcpy(row, temp_image + (i*width * 4), width * 4);
		memcpy(temp_image + (i*width * 4), temp_image + (((height - 1) - i)*width * 4), width * 4);
		memcpy(temp_image + (((height - 1) - i)*width * 4), row, width * 4);
		delete[] row;
	}
	counter = 0;
	while (counter <= imsize) {
		//Flip and Convert to RGBA
		image[counter] = temp_image[counter + 2];
		image[counter + 1] = temp_image[counter + 1];
		image[counter + 2] = temp_image[counter + 0];
		image[counter + 3] = temp_image[counter + 3];
		counter += 4;
	}
	ok = true;
}

TgaImage::~TgaImage() {
	delete[] image;
}