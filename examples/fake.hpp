#ifndef MHAA_EEPROM_EXAMPLE_FAKE_HPP
#define MHAA_EEPROM_EXAMPLE_FAKE_HPP

#include <eeprom/memory.hpp>

namespace example
{
    using namespace mhaa::eeprom;

    class Fake final : public Memory
    {
    public:
        uint32_t size_bytes() const override { return 1; }
        Status read(Address address, uint8_t &value, uint32_t timeout_ms) override
        {
            if (!timeout_ms)
            {
                return Status::InvalidArgument;
            }
            if (address >= size_bytes())
            {
                return Status::InvalidAddress;
            }
            if (read_status != Status::Success)
            {
                return read_status;
            }
            value = stored;
            return Status::Success;
        }
        Status write(Address address, uint8_t value, uint32_t timeout_ms) override
        {
            if (!timeout_ms)
            {
                return Status::InvalidArgument;
            }
            if (address >= size_bytes())
            {
                return Status::InvalidAddress;
            }
            ++writes;
            if (write_status == Status::Success)
            {
                stored = value;
            }
            return write_status;
        }

        unsigned writes = 0;
        uint8_t stored = 42;
        Status read_status = Status::Success;
        Status write_status = Status::Success;
    };
}

#endif
