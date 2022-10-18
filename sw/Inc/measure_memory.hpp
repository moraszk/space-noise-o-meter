#pragma once

#include <array>
#include <cstdint>
#include <utils.hpp>

	enum class Destinition : uint8_t {
		DE = 1,
		GY = 2,
		SZ = 3,
		OBU = 4,
		OBC = 0,
		UNKNOWN =5,
		SU = 6,
	};

union meas_mem_type{
    std::array<unsigned char, 1024> raw_content;
    static constexpr const std::size_t chunk_size = 12;
    static constexpr const std::size_t number_of_chunks = utils::round_up(1024, 12);
    
    class baud_measure_class{
        static const constexpr std::size_t histogram_width = 100;
        
        using histogram = std::array<uint16_t, histogram_width>;
        std::array<histogram, 5> histograms; //TODO change 5 to number of other modules on the bus;
    public:
        void register_measure(Destinition dst, int16_t baud_error){            
            const uint8_t dst_id = static_cast<uint8_t>(dst);
            const uint16_t baud_bin_index = baud_error + (histogram_width/2);
            
            if(dst_id>=5)
                return; //TODO status metric?
            
            if(baud_bin_index > histogram_width)
                return; //TODO status metric?
            
            auto& hist = histograms[dst_id];
            hist[baud_bin_index]++;
        }
    } baud_rate;
    
    class adc_measure_class{
        static const constexpr std::size_t histogram_width = 512;
        
        std::array<uint16_t, histogram_width> histogram;
    public:
        void register_measure(int16_t error_value){            
            const uint16_t bin_index = error_value + (histogram_width/2);
            
            if(bin_index>=histogram_width)
                return; //TODO status metric?
            
            histogram[bin_index]++;
        }
    } adc_noise;
    
    void zero(){
        __builtin_bzero(this, sizeof(decltype(*this)));
    }
    
    const unsigned char* get_chunk_begin(std::size_t chunk){
        return &raw_content[chunk*chunk_size];
    }
};

extern meas_mem_type measure_memory;

static_assert(sizeof(measure_memory) == 1024, "There are only 1024 bytes for measures");
