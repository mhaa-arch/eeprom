#include <eeprom/eeprom.hpp>
#include "fake.hpp"

using namespace mhaa::eeprom;
using namespace example;

int main()
{
    Fake memory;
    EEPROM settings(memory);
    return settings.update(0, 55, 20) == Status::Success && memory.stored == 55 ? 0 : 1;
}
