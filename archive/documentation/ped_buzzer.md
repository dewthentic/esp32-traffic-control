# `PED_Buzzer`

`PED_Buzzer` is a non-blocking tone generator intended for pedestrian
indications. The declaration is in
[`PED_Buzzer.h`](../../lib/PED_Buzzer/PED_Buzzer.h), and implementation is in
[`PED_Buzzer.cpp`](../../lib/PED_Buzzer/PED_Buzzer.cpp).

## Hardware and initialization

The only implemented constructor assigns the buzzer to GPIO 18; there is no
configurable-pin constructor. `Initialize()` sets the pin to `OUTPUT` and sets
the state to `OFF`. The code uses Arduino `tone()` and `noTone()` at 800 Hz.
Confirm that the chosen buzzer type and GPIO are appropriate for the board and
drive circuit; do not connect a load that exceeds ESP32 pin limits.

## State selection

`ChangeState(int state)` maps integer values as follows:

| Value | State | Current behavior |
| ---: | --- | --- |
| 0 | `OFF` | Stops the active tone |
| 1 | `BURST` | Starts a sequence of three burst windows |
| 2 | `COUNTDOWN` | Produces a short ping about once per second |
| 3 | `IDLE` | Also produces a short ping about once per second |
| Other | Unchanged | No state change |

`Update()` must be called repeatedly to service the timers. The implementation
does not use a blocking delay.

## Timing configuration

The current constants are:

| Setting | Value |
|---|---:|
| Tone frequency | 800 Hz |
| Short pulse duration | 40 ms |
| Countdown/idle interval | 1,000 ms |
| Burst pulse interval | 111 ms |
| Active burst window | 2,000 ms |
| Pause between windows | 500 ms |
| Number of burst windows | 3 |

`TriggerBurst(int amt)` currently ignores `amt` and simply selects state 1.
`TriggerPing()` contains no active behavior. The repeated ping behavior is
selected through `ChangeState(2)` or `ChangeState(3)` and serviced by
`Update()`.

## Usage shape

```cpp
PED_Buzzer buzzer;

void setup() {
    buzzer.Initialize();
    buzzer.ChangeState(2); // select one-second pings
}

void loop() {
    buzzer.Update();
}
```

Call `ChangeState(0)` to stop the sound. This example describes the standalone
class; the current `TrafficSignal` implementation comments out its buzzer
initialization and update calls, so the buzzer is not active in the main
application.

## Limitations

- Every instance uses GPIO 18, so multiple active instances would share the
  same physical pin.
- The buzzer is not connected to pedestrian button events or intersection
  state.
- `TriggerPing()` and the `amt` argument to `TriggerBurst()` are not
  implemented as their names may suggest.
- Validate the intended sound pattern and hardware separately before use.