#pragma once
#include <cstdint>
#include "utils.hpp"
#include "tictactoe.hpp"

struct sat_stat;
extern struct sat_stat sat_status;

struct sat_stat{
private:
    constexpr const static uint64_t expected_signature = 0xeddaacdcabbaedda; //Three well-known bands
    uint64_t signature;

    sat_stat(sat_stat&) = delete;
    void operator=(sat_stat&) = delete;

public:
    static const constexpr std::size_t chunk_length = 12;
    static const constexpr std::size_t chunk_length_in_base64 = chunk_length * 4 / 3;

    sat_stat();

    uint8_t bootnum;
    uint8_t unknown_interrupt;

    struct {
        uint8_t frame_error;
        uint8_t noise_error;
        uint8_t overrun_error;
        uint8_t too_long_message;
        uint8_t midpacket_char;
        uint16_t received_char;
        uint16_t idle;
    } uart;

    uint8_t clock;

    struct {
        uint8_t command_without_run;
        uint8_t unknown_command;
        uint8_t mrc_buffer_overflow;
    } communication;

    enum class experiment : uint8_t{
        OFF = 0,
        ADC_NOISE,
        UART_RATES,
        QUOTES,
        TEMP,
        HALL
    } experiment;

    struct {
        uint16_t errors;
    } measure;

    struct {
        uint16_t half_vref;
        uint16_t hall_exp;
        uint16_t temp;
        uint16_t vref;
    } adc;

    std::array<uint16_t,4> timer_capture;

    TicTacToe tictactoe;

    const unsigned char * getchunk(const std::size_t chunk){
        unsigned char* begin_data = reinterpret_cast<unsigned char*>(&sat_status.bootnum);
        return begin_data + (chunk_length*chunk);
    }
};

const constinit std::size_t sat_stat__number_of_chunks =
    utils::round_up(
        (sizeof(sat_stat)-sizeof(uint64_t)),
        sat_stat::chunk_length
    );
