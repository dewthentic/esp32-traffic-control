# `TrafficSignal`

`TrafficSignal` represents one three-color light and its local phase-timing
state machine. Its API is declared in
[`TrafficSignal.h`](../../lib/TrafficSignalCore/TrafficSignal.h), and its
implementation is in
[`TrafficSignal.cpp`](../../lib/TrafficSignalCore/TrafficSignal.cpp).

## Construction

Two constructors are implemented:

```cpp
TrafficSignal(int redPin, int yellowPin, int greenPin, bool isPrimary);
TrafficSignal(
    int redPin, int yellowPin, int greenPin, bool isPrimary,
    int redTimeMs, int yellowTimeMs, int greenTimeMs
);
```

The four-argument overload uses defaults of 10,000 ms red, 3,000 ms yellow,
and 10,000 ms green. The seven-argument overload accepts custom intervals.
`isPrimary` selects the fallback color: primary signals flash yellow and
non-primary signals flash red. Provide positive timing values; the
implementation does not validate them.

## Public methods

| Method | Purpose |
|---|---|
| `Initialize()` | Configures the light pins as outputs and starts in red or fallback |
| `Update()` | Advances the state machine; call repeatedly from `loop()` |
| `SetCurrentPhase(int phase)` | Sets the internal phase value |
| `RedInterval()` | Sets red on and yellow/green off |
| `YellowInterval()` | Sets yellow on and red/green off |
| `GreenInterval()` | Sets green on and red/yellow off |

The phase values used by `Update()` are **0 = red**, **1 = yellow**, and
**2 = green**. The normal sequence is:

```text
red -> green -> yellow -> red
```

`Update()` checks elapsed time using `millis()`, so it does not block the rest
of the Arduino loop while waiting for a phase interval.

## Initialization and fallback

Set the phase before calling `Initialize()`. If the phase is 0, 1, or 2,
initialization resets it to 0 and turns red on. Any other value selects an
invalid-phase fallback: the signal clears all three lights, then toggles the
role-specific fallback color every 500 ms. For example:

```cpp
TrafficSignal signal(14, 27, 26, true, 15000, 5000, 30000);

void setup() {
    signal.SetCurrentPhase(0);
    signal.Initialize();
}

void loop() {
    signal.Update();
}
```

The source contains no setter/getter methods for the GPIO pins. It also does
not validate that pins are distinct or that the selected GPIOs are appropriate
for a particular ESP32 board.

## Current integration and limitations

- Each `TrafficSignal` controls only its own pins and timing. Multiple instances
  are not coordinated, so this class alone does not ensure a safe intersection
  phase plan.
- `SetCurrentPhase()` changes the internal phase only. Use it before
  `Initialize()` for the documented startup behavior; changing it at runtime
  does not itself configure phase timestamps or immediately set the outputs.
- The source calls a valid startup phase any value from 0 through 2, then
  unconditionally starts at red.
- A `PED_Buzzer` member exists, but its initialization and update calls are
  commented out. The pedestrian button member is also commented out.
- The internal phase is not initialized by the constructors. Call
  `SetCurrentPhase()` before `Initialize()`; otherwise startup behavior is not
  reliable.
- Negative timing arguments are not rejected before being stored in unsigned
  interval fields.

Use this class only for controlled development/testing. This implementation
has not been certified for real traffic or safety-critical control.