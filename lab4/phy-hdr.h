#ifndef PHYHDR
#define PHYHDR

#include <cstddef>
#include <cstdint>

struct phy_hdr{

	uint_fast8_t bitrate = 0;
	uint_fast16_t timestamp = 0;
	
	const size_t bitrate_size = 6;
	const size_t timestamp_size = 10;
	
	bool serialize(char* buffer, size_t& offset) const;
	bool deserialize(char* buffer, size_t& offset);

};

#endif
