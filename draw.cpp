#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "grid.h"
#include "draw.h"
#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

int draw(grid g, string name){
        char arr[900*64];
        for(int i = 0; i<30; i++){
                for(int j = 0; j<30; j++){
                        for(int k = 0; k<8; k++){
                                for(int l = 0; l<8; l++) arr[30*(64*i+8*k)+8*j+l] = (1-g(i,j))*255;
                        }
                }
        }
        return stbi_write_png(name.c_str(), 240, 240, 1, arr, 240);
}
int draw2(grid g, string name){
	char arr[900*64];
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			for(int k = 0; k<8; k++){
				for(int l = 0; l<8; l++){
					if(k % 8 && l % 8 ){
						arr[30*(64*i+8*k)+8*j+l] = (1-g(i,j))*253+1;
					} else if(!((!(k%8)&& i%5) || (!(l%8)&& j%5))){
						arr[30*(64*i+8*k)+8*j+l] = 0;
					} else {
						arr[30*(64*i+8*k)+8*j+l] = 127;
					}
				}
			}
		}
	}
	return stbi_write_png(name.c_str(), 240, 240, 1, arr, 240);
}
