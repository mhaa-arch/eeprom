# Using EEPROM across targets

The only project dependency is the matching `eeprom-contract`. Keep its API revision aligned with this Core.

The update policy skips writes for equal values across all conforming Adapters. Physical erase granularity and endurance still belong to the implementation. After an uncertain write, decide whether to verify on a subsequent successful read before retrying. The Core provides no transaction or rollback guarantee.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
