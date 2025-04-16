#pragma once
#include <vector>

#ifdef _WIN64
#define ADDRESS_LENGTH 8
#define ADDRESS_FMT "16"

#else
#define ADDRESS_LENGTH 4
#define ADDRESS_FMT "8"

#endif

enum DataType {
	DATATYPE_HEX,
	DATATYPE_SIGNED_INT,
	DATATYPE_UNSIGNED_INT,
	DATATYPE_BIT,
	DATATYPE_BOOL,
	DATATYPE_FLOAT,
	DATATYPE_PTR,
	DATATYPE_STRING,
	DATATYPE_VECTOR,
	DATATYPE_MATRIX,
	DATATYPE_CLASS,
	DATATYPE_VTABLE,
};

struct DataLine
{
	unsigned int offset;
	DataType dataType;
	unsigned int byteLength;
	

	DataLine(): offset(0), dataType(DATATYPE_HEX), byteLength(ADDRESS_LENGTH)
	{}

	DataLine(unsigned int offset, DataType dataType, unsigned int byteLength):
		offset(offset), dataType(dataType), byteLength(byteLength)
	{}

	void renderLine(uintptr_t baseAddress, uint64_t bytes);
};

class MemoryTable
{
public:
	std::vector<DataLine>* dataLines;
	unsigned char* byteBuffer;
	size_t bufferLength = 511;

	MemoryTable();
	MemoryTable(char* buffer, size_t size);

	~MemoryTable();

	void renderLines(uintptr_t baseAddress);
	void constructLines();
	void constructLeftOverLine(unsigned int offset);
};
