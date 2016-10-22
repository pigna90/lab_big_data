#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>

class Baseline {
private:
	std::map<std::string, std::vector<uint32_t>> m_time_series;
	std::vector<uint16_t> m_dates;

	template <class Archive>
	void TimeSeries::serialize(Archive &archive) {
		archive(m_time_series);
	}
	
public:
	Baseline() {}
	~Baseline() {}
	Baseline(const std::string &dataset_name) {
		/*Il costruttore con un parametro assume le caratteristiche
		 * della funzione populateDataStructure precedentemente
		 * implementata, di conseguenza andrà rimossa dalla classe.*/
		 /*Valutare se inserire in questo posto anche la funzione
		  * parseLine, chiamata da populateDataStructure*/
	}

	void serialize_data(const string &file_name) const {
		std::ofstream os(file_name, std::ios::binary);                    
		cereal::BinaryOutputArchive output(os);
		output(m_time_series);
	}
		
	void load_data(const string &file_name) {
		std::ifstream is(file_name, std::ios::binary);
		cereal::BinaryInputArchive input(is);
		input(m_time_series);
	}

	inline std::vector<uint32_t> range(
		const std::string &page, uint32_t time1, uint32_t time2) const {
		
		const auto lt_idx = std::lower_bound(m_dates.begin(), m_dates.end(), time1);
		const auto rt_idx = std::lower_bound(m_dates.begin(), m_dates.end(), time2);		
		
		std::vector<uint32_t> result(rt_idx - lt_idx);
		
		const auto page = m_time_series.find(page);
		
		for(auto idx = lt_idx - m_dates.begin(); idx <= rt_idx - m_dates.begin(); ++idx)
			result.push_back(page->second[idx]);
			
		return result;
	}

	inline std::vector<std::pair<uint16_t, uint32_t>> rangeTopK(
		const std::string &page, uint32_t time1, uint32_t time2, uint32_t k) const {
		
	}

	uint32_t size() const {
		/*Possibile realizzazione: inserire la mappa all'interno di
		 * un std::vector<tipodellamappa> e successivamente calcolare la dimensione
		 * occupata come:
		 * size_t result = sizeof(tipodellamappa) * vettore.size()*/
		  
		return 0;
	}
};
