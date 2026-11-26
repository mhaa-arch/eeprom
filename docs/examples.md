# Run the EEPROM Core example

The facade borrows one byte of simulated storage. `update(0, 55, 20)` reads offset zero and writes only if necessary, passing 20 ms to each operation it uses. The result and simulated cell are checked together. The behavior test also verifies a direct write and an unchanged value that skips programming.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
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
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/eeprom-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
