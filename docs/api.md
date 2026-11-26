# Use the EEPROM Core

Public entry headers are [eeprom/eeprom.hpp](../include/eeprom/eeprom.hpp).

## Choose an operation

Construct `EEPROM` from a live `Memory&`. Check `size_bytes()` when you need to choose a storage layout. Use `read` and `write` for one bounded operation. Treat the read output as valid only on `Success`. The underlying implementation validates the effective address range.

## Update an existing byte

`update` reads first and skips programming if the value already matches. It returns any read error directly or reports the outcome of a needed write. The positive timeout applies separately to each step, so there can be two operation budgets. Concurrent code must serialize updates to the same location if the whole read/compare/write sequence has to be indivisible.

## Composition and lifetime

Application code calls the EEPROM Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
