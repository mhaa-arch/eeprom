#ifndef MHAA_EEPROM_HPP
#define MHAA_EEPROM_HPP

#include <stdint.h>
#include <eeprom/memory.hpp>
#include <eeprom/types.hpp>

namespace mhaa
{
    namespace eeprom
    {
        /** @brief Byte operations on one borrowed EEPROM. */
        class EEPROM
        {
        public:
            explicit EEPROM(Memory &memory) : memory_(memory) {}

            Status read(Address address, uint8_t &value, uint32_t timeout_ms)
            {
                return memory_.read(address, value, timeout_ms);
            }

            uint32_t size_bytes() const { return memory_.size_bytes(); }

            Status write(Address address, uint8_t value, uint32_t timeout_ms)
            {
                return memory_.write(address, value, timeout_ms);
            }

            /** @brief Avoids programming unchanged cells. The budget applies to each operation. */
            Status update(Address address, uint8_t value, uint32_t timeout_ms_per_operation)
            {
                uint8_t stored = 0;
                const Status status = read(address, stored, timeout_ms_per_operation);
                if (status != Status::Success || stored == value)
                {
                    return status;
                }
                return write(address, value, timeout_ms_per_operation);
            }

        private:
            Memory &memory_;
        };
    }
}

#endif
