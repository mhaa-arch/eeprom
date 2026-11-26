# EEPROM Core guide

The address type describes a portable byte offset. Each memory instance has a smaller or equal effective capacity reported at runtime.

Start with range and timeout checks, then follow the write and update examples.

- [Use the facade](api.md) for construction, results and optional capabilities.
- [Run the example](examples.md) to see the same API with a simulated resource.
- [Check portability](compatibility.md) for assumptions that belong to the target.
