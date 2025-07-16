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
	std::string serialize(const std::vector<T>& i_rvData)
	{
		std::string sBin;

		for (const T& rT : i_rvData)
		{
			for (int i = 0; i < sizeof(i_rvData); ++i)
			{
				sBin += reinterpret_cast<const char*>(&rT)[i];
			}
		}

		return sBin;
	}

	template <typename T>
	std::vector<T> deserialize(std::string& i_rsBin, size_t i_uNumValues = 0)
	{
		std::vector<T> vValues;
		T value;

		if (i_uNumValues == 0)
		{
			i_uNumValues = i_rsBin.size() / sizeof(T);
		}

		for (size_t i = 0; i < i_uNumValues; ++i)
		{
			std::memcpy(&value, i_rsBin.data(), sizeof(T));

			vValues.push_back(value);

			i_rsBin.erase(0, sizeof(T));
		}

		return vValues;
	}

protected:
private:
};