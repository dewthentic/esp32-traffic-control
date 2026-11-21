# Application Entry Point (`src/main.cpp`)

The Arduino application entry point is
[`main.cpp`](../../src/main.cpp). It creates two `TrafficSignal` objects,
configures their initial phases during `setup()`, and calls each object's
non-blocking `Update()` method repeatedly from `loop()`.

## Current configuration

| Signal object | Red GPIO | Yellow GPIO | Green GPIO | Primary? | Red interval | Yellow interval | Green interval | Initial phase request |
|---|---:|---:|---:|---|---:|---:|---:|---:|
| `signalOne` | 14 | 27 | 26 | Yes | 15,000 ms | 5,000 ms | 30,000 ms | 4 |
| `signalTwo` | 15 | 4 | 5 | No | 15,000 ms | 5,000 ms | 30,000 ms | 1 |

The configured intervals are passed to the seven-argument constructor in the
order red, yellow, green. The constructor's timing arguments are in
milliseconds.

## Startup and loop behavior

1. Global object construction assigns GPIOs, timings, and primary/secondary
   roles.
2. `setup()` requests phase 4 for `signalOne` and phase 1 for `signalTwo`.
3. `Initialize()` configures each light pin as an output.
4. A requested phase from 0 through 2 is reset to red (phase 0) during
   initialization. Thus `signalTwo` starts red despite its phase-1 request.
5. Any other requested phase enters the invalid-phase fallback. Thus
   `signalOne` starts flashing yellow because it is primary.
6. `loop()` calls `Update()` for each object continuously. The state machine
   uses `millis()` rather than blocking `delay()` calls.

The source comment on the phase request says that values `<= 0` or `>= 2`
trigger fallback, but the implementation accepts **0, 1, and 2** as valid and
falls back for values outside that range. The actual configured value 4 is
therefore invalid.

## Important limitations

- These two signals run independent state machines; there is no coordination
  or mutual exclusion between them.
- The initial phase is not an instruction to start at that normal phase:
  initialization resets any valid phase to red.
- The pedestrian button and intersection manager are not connected to this
  entry point.
- `TrafficSignal` contains a buzzer member, but its buzzer initialization and
  update calls are commented out.

This configuration is for a development prototype only. It is not safe or
certified for controlling real traffic.

## Build and upload

The PlatformIO environment is named `esp32dev` and uses the `espressif32`
platform with the Arduino framework, as configured in
[`platformio.ini`](../../platformio.ini). From the repository root, a typical
PlatformIO CLI workflow is:

```sh
pio run
pio run -t upload
pio device monitor
```

Upload port selection and hardware wiring depend on the local setup. Confirm
the connected board and GPIO wiring before uploading or powering a circuit.