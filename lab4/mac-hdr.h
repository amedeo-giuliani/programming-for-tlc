#ifndef MACHDR
#define MACHDR

#include <cstddef>
#include <cstdint>

struct mac_hdr{
	uint_fast8_t sn = 0;
	uint_fast8_t src = 0;
	uint_fast8_t dest = 0;
	const size_t sn_size = 7;
	const size_t addr_size = 6;
	bool serialize(char* buffer, size_t& offset) const;
	bool deserialize(char* buffer, size_t& offset);
};

#endif
