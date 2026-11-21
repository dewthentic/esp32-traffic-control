# `Intersection`

`Intersection` is an unfinished placeholder for coordinating multiple traffic
signals and, eventually, related devices. Its declarations are in
[`Intersection.h`](../../lib/Signal_Intersection/Intersection.h), and its
current implementation is in
[`Intersection.cpp`](../../lib/Signal_Intersection/Intersection.cpp).

## Current status

The two-signal constructor accepts two `TrafficSignal` objects but has an empty
body. No signals are stored, no phase timing is managed, and no safety or
fallback behavior is implemented. A no-argument constructor is declared but
has no definition. The private `m_isFallback()` function is also only declared.

The class is not included or used by [`main.cpp`](../../src/main.cpp). As a
result, it currently has no effect on the running program and should not be
treated as an intersection controller.

## Declared interface

| Declaration | Status |
|---|---|
| `Intersection(TrafficSignal signalOne, TrafficSignal signalTwo)` | Defined, but empty |
| `Intersection()` | Declared, not defined |
| `m_isFallback()` | Declared, not defined |

## Design direction in source comments

The implementation comments describe a future design in which an intersection
owns coordination and timing, while individual traffic signals expose
operations to change their lights. That design has not yet been implemented.
The current `TrafficSignal` class still owns its own timing and phase
transitions.

## Before extending this class

- Decide how signals are stored and whether they should be passed by reference
  rather than copied.
- Define the legal phase sequence and prove conflicting approaches cannot
  receive green at the same time.
- Specify initialization, invalid-state handling, timing units, and safe
  behavior after resets or faults.
- Add tests for normal sequencing and failure cases before connecting physical
  loads.

This is a learning prototype, not a road-safety controller. Do not use it to
operate a real intersection.