#pragma once

#include <array>
#include <cstdint>
#include "utils.hpp"
#include "command.hpp"
#include "status.hpp"

union meas_mem_type{
    std::array<unsigned char, 1024> raw_content;
    static constexpr const std::size_t chunk_size = 12;
    static constexpr const std::size_t number_of_chunks = utils::round_up(1024, 12);

    class baud_measure_class{
        static const constexpr std::size_t histogram_width = 100;

        using histogram = std::array<uint16_t, histogram_width>;
        std::array<histogram, 5> histograms;
    public:
        void register_measure(command::Destinition dst, int16_t baud){
            const uint8_t dst_id = static_cast<uint8_t>(dst);
            const int16_t baud_error = baud - 1000;
            const uint16_t baud_bin_index = baud_error + (histogram_width/2);

            if(dst_id>=5){
                sat_status.measure.errors++;
                return;
            }

            if(baud_bin_index > histogram_width){
                sat_status.measure.errors++;
                return;
            }

            auto& hist = histograms[dst_id];
            hist[baud_bin_index]++;
        }
    } baud_rate;

    class adc_measure_class{
        static const constexpr std::size_t histogram_width = 127;

        std::array<uint32_t, histogram_width> histogram;
    public:
        uint16_t counter;
        int16_t center;
	//                      ADC prescaler---,        ,-----main worst case shortness
	constexpr static const uint16_t delay = 64 * 4 - 5;
	//                                           ˘--number of channels

        void register_measure(){
            int16_t value = sat_status.adc.half_vref;

            const uint16_t bin_index = (center - value) + (histogram_width/2);

            if(bin_index>=histogram_width){
                sat_status.measure.errors++;
                return;
            }

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
