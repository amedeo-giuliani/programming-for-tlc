#include "mac-hdr.h"
#include <cmath>

bool mac_hdr::serialize(char* buffer, size_t& offset) const{
	
	for(int i = 0; i < sn_size; i++){
		buffer[(int)std::floor(offset/8)] |= (char) ((sn >> i & 1U) << offset%8);
		offset++;
	}
	
	for(int i = 0; i < addr_size; i++){
		buffer[(int)std::floor(offset/8)] |= (char) ((src >> i & 1U) << offset%8);
		offset++;
	}
	
	for(int i = 0; i < addr_size; i++){
		buffer[(int)std::floor(offset/8)] |= (char) ((dest >> i & 1U) << offset%8);
		offset++;
	}
	
	return true;
}

bool mac_hdr::deserialize(char* buffer, size_t& offset){

	sn = 0; src = 0; dest = 0;
	
	for(int i = 0; i < sn_size; i++){
		sn |= (buffer[(int)std::floor(offset/8)] >> offset%8 & 1U) << i;
		offset++;
	}
	
	for(int i = 0; i < addr_size; i++){
		src |= (buffer[(int)std::floor(offset/8)] >> offset%8 & 1U) << i;
		offset++;
	}
	
	for(int i = 0; i < addr_size; i++){
		dest |= (buffer[(int)std::floor(offset/8)] >> offset%8 & 1U) << i;
		offset++;
	}
	
	return true;
}

