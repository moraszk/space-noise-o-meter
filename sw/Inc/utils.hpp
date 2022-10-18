#pragma once
#include <concepts>
#include <array>
#include <cstdint>
#include <iterator>

namespace utils{
    consteval std::size_t round_up(std::size_t whole, std::size_t partlen){
        if(whole % partlen == 0)
            return whole/partlen;
        else
            return whole/partlen +1;
    }

    template<std::integral T>
    constexpr auto hex2int(const char* const in) -> T{
        T ret = 0;

        for(const char* i = in; i<in+(sizeof(T)*2); i++){
            const char c = *i;
            ret<<=4;

                 if(c <= 'F' && c >= 'A') ret += c-('A'-10);
            else if(c <= 'f' && c >= 'a') ret += c-('a'-10);
            else if(c <= '9' && c >= '1') ret += c-'0';
        }

        return ret;
    }

    const std::array<char, 2>& char2hex(const unsigned char in);

    void copyashex(const uint16_t number, char* begin);

    namespace base64{
        std::array<char, 4> encode_triplet(std::uint8_t a, std::uint8_t b, std::uint8_t c);

        template<std::size_t in_long, std::input_iterator InIt>
        void encode(std::array<char, in_long*4/3>& out, InIt in){
            static_assert((in_long%3) == 0, "Only whole char triplets are implemented!");
            for(
                std::size_t i=0, j=0;
                i<16;
                j+=3,i+=4
            ){
                std::array coded = encode_triplet(in[0+j], in[1+j], in[2+j]);
                std::copy(coded.begin(), coded.end(), out.begin()+i);
            }
        }

        //template<std::size_t s, typename T>
        //void encode(std::array<T, s*4/3>&, const std::array<T, s>)  -> void encode<s>; TODO deduction guide

    }


    template<typename T, std::size_t size>
    class ringbuffer{
        static_assert(size!=0, "Ring buffer size must be at least one");

        typename std::array<T, size> data;
        typename std::array<T, size>::iterator read, write;

        typename std::array<T, size>::iterator next_it(typename std::array<T, size>::iterator it){
            it++;
            if ( it == data.end() )
                it=data.begin();
            return it;
        }

    public:
        ringbuffer(): data{}, read{data.begin()}, write{read} {}

        bool empty(){ return read == write; }

        void put_nocheck(T n){
            *write = std::move(n);
             write = next_it(write);
        }

        bool put(T n){
            put_nocheck(std::move(n));

            if(empty()){
                read=next_it(read);
                return true;
            } else
                return false;
        }

        T get(){
            T ret = *read;
            read = next_it(read);
            return ret;
        }
    };

    namespace paramparser{
        /*
		size_t getNumberOfParams() const{
			return std::count(buff.cbegin() + command_offset, buff.cbegin() + this->getSize() - serial_backset, ',');
		}

		char getParamC (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return *(i+1);
						}
					}
			}
			return '\0';
		}

		uint8_t getParam8 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint8_t>(i+1);
						}
					}
			}
			return 0;
		}

		uint16_t getParam16 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint16_t>(i+1);
						}
					}
			}
			return 0;
		}

		uint32_t getParam32 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint32_t>(i+1);
						}
					}
			}
			return 0;
		}*/
    }
}
