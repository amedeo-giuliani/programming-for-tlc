#include "phy-hdr.h"
#include <cmath>

bool phy_hdr::serialize(char* buffer, size_t& offset) const{

	for(int i = 0; i < bitrate_size; i++){
		buffer[(int)std::floor(offset/8)] |= (char) ((bitrate >> i & 1U) << offset%8);
		offset++;
	}
	
	for(int i = 0; i < timestamp_size; i++){
		buffer[(int)std::floor(offset/8)] |= (char) ((timestamp >> i & 1U) << offset%8);
		offset++;
	}
	
	return true;

}

bool phy_hdr::deserialize(char* buffer, size_t& offset){

	bitrate = 0; timestamp = 0;
	
	for(int i = 0; i < bitrate_size; i++){
		bitrate |= (buffer[(int)std::floor(offset/8)] >> offset%8 & 1U) << i;
		offset++;
	}
	
	for(int i = 0; i < timestamp_size; i++){
		timestamp |= (buffer[(int)std::floor(offset/8)] >> offset%8 & 1U) << i;
		offset++;
	}
	
	return true;

}
