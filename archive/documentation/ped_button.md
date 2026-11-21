# `PED_Button`

`PED_Button` is an early, standalone button-input class intended for a
pedestrian request. Its declarations are in
[`PED_Button.h`](../../lib/PED_Button/PED_Button.h), with implementation in
[`PED_Button.cpp`](../../lib/PED_Button/PED_Button.cpp).

## Implemented behavior

- The implemented constructor takes one GPIO number.
- `Initialize()` starts the serial port at 9600 baud and configures the GPIO
  as `INPUT_PULLUP`.
- `Update()` reads the input and tracks flickering and steady states.
- A 50 ms debounce interval is used before accepting a stable state change.
- A press is detected as a stable transition from `HIGH` to `LOW`, consistent
  with an active-low switch connected to a pull-up input.

The press and release branches contain no action yet. The code does not notify
`TrafficSignal`, queue a crossing request, or change any light.

## Declared API

| Method | Current behavior |
|---|---|
| `PED_Button(int buttonPin)` | Sets the input GPIO; this constructor is implemented |
| `PED_Button()` | Declared in the header, but has no implementation |
| `Initialize()` | Starts serial and configures `INPUT_PULLUP` |
| `Update()` | Samples input and debounces state; no request action is performed |

## Usage shape

The following shows the intended initialization/update pattern for the
implemented constructor. It does not imply that button presses currently
control a signal.

```cpp
PED_Button crossingButton(23);

void setup() {
    crossingButton.Initialize();
}

void loop() {
    crossingButton.Update();
}
```

Choose a GPIO suitable for the specific ESP32 board. With `INPUT_PULLUP`, wire
the switch between the configured GPIO and ground; the released input reads
`HIGH`, while a pressed switch reads `LOW`.

## Limitations

- There is no callback, return value, or event queue for a detected press.
- The default constructor has no definition and should not be used.
- `m_amtPressed` is present but not used.
- `Serial.begin(9600)` is called by this class's initializer; applications
  should avoid initializing serial elsewhere at an incompatible rate.

The button module is not integrated into the current application entry point.