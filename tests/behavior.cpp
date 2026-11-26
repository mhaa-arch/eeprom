#include <eeprom/eeprom.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::eeprom;
using namespace example;

int main()
{
    Fake memory;
    EEPROM settings(memory);
    assert(settings.update(1, 30, 10) == Status::InvalidAddress);
    assert(settings.update(0, 30, 0) == Status::InvalidArgument);
    memory.read_status = Status::Busy;
    assert(settings.update(0, 30, 10) == Status::Busy);
    uint8_t value = 8;
    assert(settings.read(0, value, 10) == Status::Busy && value == 8);
    memory.read_status = Status::Success;
    assert(settings.update(0, 42, 10) == Status::Success && memory.writes == 0);
    memory.write_status = Status::Timeout;
    assert(settings.update(0, 30, 10) == Status::Timeout && memory.writes == 1);
    memory.write_status = Status::Success;
    assert(settings.update(0, 30, 10) == Status::Success && memory.stored == 30);

    assert(settings.size_bytes() == 1);
    assert(settings.write(1, 33, 10) == Status::InvalidAddress);
    assert(settings.write(0, 33, 10) == Status::Success);
    assert(settings.read(0, value, 10) == Status::Success && value == 33);
}
