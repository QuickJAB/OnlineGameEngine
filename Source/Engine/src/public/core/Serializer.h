#pragma once

#include <string>
#include <vector>

/*
	Example Data
	uint32_t num = 506;
	float float1 = 123.456f;
	float float2 = -987.654f;

	Serialization Example
	BinarySerializer* bs = new BinarySerializer();
	std::string bin = bs->serialize(num);
	bin += bs->serialize(float1);
	bin += bs->serialize(float2);
	Do something with the binary data...

	Deserialization Example
	BinarySerializer* bs = new BinarySerializer();
	std::vector<uint32_t> u = bs->deserialize<uint32_t>(bin, 1);
	std::vector<float> f = bs->deserialize<float>(bin);
	Do something with the vectors
*/

class BinarySerializer
{
public:
	template <typename T>
	std::string serialize(const T& in_data)
	{
		std::string bin;

		// Loop through each byte of the data and cast it to a char
		for (int i = 0; i < sizeof(in_data); ++i)
		{
			bin += reinterpret_cast<const char*>(&in_data)[i];
		}

		return bin;
	}

	template <typename T>
	std::vector<T> deserialize(std::string& in_bin, size_t in_numValues = 0)
	{
		std::vector<T> values;
		T value;

		if (in_numValues == 0)
		{
			in_numValues = in_bin.size() / sizeof(T);
		}

		for (size_t i = 0; i < in_numValues; ++i)
		{
			// Copy the bytes from the chars into a variable of the correct type
			std::memcpy(&value, in_bin.data(), sizeof(T));

			values.push_back(value);

			// Remove the value from the binary
			in_bin.erase(0, sizeof(T));
		}

		return values;
	}
};