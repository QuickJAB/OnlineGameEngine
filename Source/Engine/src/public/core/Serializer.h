#pragma once

#include <string>
#include <vector>

/*
	Example Data
	std::vector<uint32_t> entityId;
	entityId.push_back(506);
	std::vector<float> data;
	data.push_back(123.456f);
	data.push_back(-987.654f);

	Serialization Example
	BinarySerializer* bs = new BinarySerializer();
	std::string bin = bs->serialize(entityId);
	bin += bs->serialize(data);
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
	std::string serialize(const std::vector<T>& in_data)
	{
		std::string bin;

		for (const T& t : in_data)
		{
			// Loop through each byte of the data and cast it to a char
			for (int i = 0; i < sizeof(in_data); ++i)
			{
				bin += reinterpret_cast<const char*>(&t)[i];
			}
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