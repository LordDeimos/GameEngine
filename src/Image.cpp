#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <glbinding/gl/gl.h>
#include <turbojpeg.h>
#include <libpng16/png.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Image.h"

using namespace GameEngine;

Image::Image(const std::string& path) {
	std::ifstream file;
	file.open(path, std::ios::binary);
	if (!file.is_open()) {
		file.close();
		return;
	}
	file.close();
	std::string type = path.substr(path.find_last_of('.')+1, 3);
	if (type == "png") {
		loadPng(path);
	}
	else if (type == "jpg") {
		loadJpg(path);
	}
	else if (type == "bmp") {
		loadBmp(path);
	}
	else if (type == "tga") {
		loadTga(path);
	}
}

Image::~Image() {
	if(image!=nullptr)
		delete[] image;
}


void Image::loadPng(const std::string& path) {
	FILE* file = fopen(path.c_str(), "rb");
	std::vector<char> header(8);
	int length = fseek(file, 0, SEEK_END);

	fseek(file, 0, SEEK_SET);

	fread(header.begin()._Ptr, 1, 8, file);

	png_structp png_file = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png_file)
		std::cerr << "Failed to initialise png_file" << std::endl;
	png_infop png_info = png_create_info_struct(png_file);
	if (!png_file)
		std::cerr << "Failed to initialise png_info" << std::endl;
	if (setjmp(png_jmpbuf(png_file)))
		std::cerr << "Failed inital read" << std::endl;
	png_init_io(png_file, file);
	png_set_sig_bytes(png_file, 8);

	png_read_info(png_file, png_info);

	width = png_get_image_width(png_file, png_info);
	height = png_get_image_height(png_file, png_info);
	char color_type = png_get_color_type(png_file, png_info);
	pix_depth = png_get_bit_depth(png_file, png_info);

	if (color_type == PNG_COLOR_TYPE_RGBA) {
		alpha_length = 2;
	}

	if (pix_depth == 16)
		png_set_strip_16(png_file);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_file);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if (color_type == PNG_COLOR_TYPE_GRAY && pix_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_file);

	if (png_get_valid(png_file, png_info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_file);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png_file, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_file);

	//number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_file, png_info);

	/* read file */
	if (setjmp(png_jmpbuf(png_file)))
		std::cerr << "Error during read_image" << std::endl;

	png_bytep* row_pointers = new png_bytep[height];
	int row_bytes = png_get_rowbytes(png_file, png_info);
	for (int i = 0; i < height; i++)
		row_pointers[i] = (png_byte*)malloc(row_bytes);
	png_read_image(png_file, row_pointers);

	int imsize = height * row_bytes;
	image = new uint8_t[imsize];
	for (int i = 0; i < height; i++) {
		memcpy(image + (row_bytes * i), row_pointers[i], row_bytes);
	}
	png_destroy_read_struct(&png_file, &png_info, NULL);
	fclose(file);
	delete[] row_pointers;
}

void Image::loadJpg(const std::string& path) {
	FILE* file;
	uint8_t* buffer;
	int size, inSubsamp, inColorspace;
	uint32_t jpegSize;
	tjhandle tjInstance = tjInitDecompress();

	file = fopen(path.c_str(), "rb");

	if (fseek(file, 0, SEEK_END) < 0 || ((size = ftell(file)) < 0) || fseek(file, 0, SEEK_SET) < 0)
		OutputDebugString("determining input file size\n");

	if (size == 0)
		OutputDebugString("Input file contains no data\n");

	jpegSize = (uint32_t)size;
	buffer = (uint8_t*)tjAlloc(jpegSize);
	fread(buffer, jpegSize, 1, file);
	fclose(file);

	tjDecompressHeader3(tjInstance, buffer, jpegSize, (int*)&width, (int*)&height, &inSubsamp, &inColorspace);
	width = TJPAD(width);
	int imsize = width * height * tjPixelSize[TJPF_RGBX];
	uint8_t* temp_image = (uint8_t*)(tjAlloc(imsize));

	tjDecompress2(tjInstance, buffer, jpegSize, temp_image, width, 0, height, TJPF_RGBX, TJFLAG_ACCURATEDCT);
	alpha_length = 1;
	tjFree(buffer);
	tjDestroy(tjInstance);

	image = new uint8_t[imsize];
	memcpy(image, temp_image, imsize);
	tjFree(temp_image);
}

void Image::loadTga(const std::string& path) {
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();

	file.seekg(0, file.beg);
	char header[18];
	file.read(header, 18);

	width = TWOBYTE(header, 12);// (header[13] << 8) | (header[12] & 0xff);
	height = TWOBYTE(header, 14);// (header[15] << 8) | (header[14] & 0xff);
	pix_depth = header[16];
	alpha_length = header[17];

	int imsize = (pix_depth / 8)*width*height;
	std::vector<uint8_t> temp_image(imsize);
	uint8_t* image_ptr = temp_image.begin()._Ptr;
	if (imsize > length) {
		ok = false;
		return;//Filter out compressed textures
	}
	image = new uint8_t[imsize];
	file.read((char*)image_ptr, imsize);
	file.close();
	int counter = 0;
	for (int i = 0; i < (height) / 2; i++) {
		uint8_t* row = new uint8_t[width * 4];
		memcpy(row, image_ptr + (i*width * 4), width * 4);
		memcpy(image_ptr + (i*width * 4), image_ptr + (((height - 1) - i)*width * 4), width * 4);
		memcpy(image_ptr + (((height - 1) - i)*width * 4), row, width * 4);
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
}

void Image::loadBmp(const std::string& path) {
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
}

bool Image::hasAlpha() {
	return alpha_length > 0;
}