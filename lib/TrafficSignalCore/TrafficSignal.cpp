#include <Arduino.h>
#include "TrafficSignal.h"

TrafficSignal::TrafficSignal(int r, int y, int g, bool isPrimary)
{
    PIN_RED = r;
    PIN_YELLOW = y;
    PIN_GREEN = g;

    // default settings
    RED_INT_TIME = 10000;
    YELLOW_INT_TIME = 3000;
    GREEN_INT_TIME = 10000;
    IS_PRIM_SIGNAL = isPrimary;
}

TrafficSignal::TrafficSignal(int r, int y, int g, bool isPrimary, int r_time, int y_time, int g_time) {
    PIN_RED = r;
    PIN_YELLOW = y;
    PIN_GREEN = g;

    // custom settings
    RED_INT_TIME = r_time;
    YELLOW_INT_TIME = y_time;
    GREEN_INT_TIME = g_time;
    IS_PRIM_SIGNAL = isPrimary;
}

void TrafficSignal::Initialize()
{
    pinMode(PIN_RED, OUTPUT); // leds output light
    pinMode(PIN_YELLOW, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);

    if (m_currentPhase >= 0 and m_currentPhase <= 2)
    {                  // if setup properly...no previous garbage data
        m_currentPhase = 0; // reset the current phase before beginning to prevent erratic first cycle
        RedInterval(); // start the program as a red light
        m_redStartedAt = millis();
    }
    else
    {
        m_currentPhase = -1; // force into out-of-bounds to trigger default case each time (also maybe harden against overflow exploit)
        m_flashStartedAt = millis(); // used for fallback. unsigned long int will overflow after ~49 days i think
        m_invalidFallback = true; // raise invalid flag (turns off all lights)
    }
}

void TrafficSignal::Update()
{
    // using millis() requires a mindset change from telling a program to stay put (delay()) to being a security guard waiting for the right time to do something (millis())
    // i.e. state machines

    // signal loop based on US traffic signals
    // switch statement keeps this clean, only worry about one signal at a time
    switch (m_currentPhase) {

        case 0:
            m_invalidFallback = false; // if the system recovers to any valid phase, set the fallback flag to false
            if (millis() - m_redStartedAt >= RED_INT_TIME)
            {
                // it's time to switch to another state, switch to another state and check the time there.
                GreenInterval();
                m_currentPhase = 2;
                m_greenStartedAt = millis();
            }
            // reaches the end = it's not time yet. repeat the loop and stay in current phase.
            break;

        case 1:
            m_invalidFallback = false;
            if (millis() - m_yellowStartedAt >= YELLOW_INT_TIME)
            {
                RedInterval();
                m_currentPhase = 0;
                m_redStartedAt = millis();
            }
            break;

        case 2:
            m_invalidFallback = false;
            if (millis() - m_greenStartedAt >= GREEN_INT_TIME)
            {
                YellowInterval();
                m_currentPhase = 1;
                m_yellowStartedAt = millis();
            }
            break;

        default: // out of bounds exception (fallback to flashing red or yellow depending on signal identifier)

            // if the fallback flag is true (for the first time), turn off all the pins, we'll turn on the necessary ones below
            if (m_invalidFallback)
            {
                digitalWrite(PIN_RED, LOW);    // we need this
                digitalWrite(PIN_YELLOW, LOW); // and this for fallback
                digitalWrite(PIN_GREEN, LOW);
                // digitalWrite(PIN_BUZZER, LOW);
                m_flashStartedAt = millis(); // initialize timer in a clean spot
                m_invalidFallback = false;   // turn the flag off to prevent flashing issues
            }

            // if the signal is a primary signal, flash yellow every second
            // otherwise, the signal is an arterial signal, flash red every second
            if (!IS_PRIM_SIGNAL)
            {

                if (millis() - m_flashStartedAt >= FLASH_INT_TIME)
                { // arterial signal fallback (red)
                    if (digitalRead(PIN_RED))
                    {                               // read the red pin's state (returns binary 1=high, 0=low)
                        digitalWrite(PIN_RED, LOW); // if high, invert to low
                        m_flashStartedAt = millis();
                    }
                    else
                    {
                        digitalWrite(PIN_RED, HIGH); // if low, invert to high
                        m_flashStartedAt = millis();
                    }
                }
                // otherwise, reach the end of the loop and try again, no break because it's default case and looping in loop()
                // and we don't restart the timer because we took no action
            }
            else
            {

                if (millis() - m_flashStartedAt >= FLASH_INT_TIME)
                { // primary signal fallback (yellow)
                    if (digitalRead(PIN_YELLOW))
                    {                                  // read the red pin's state
                        digitalWrite(PIN_YELLOW, LOW); // if high, invert to low
                        m_flashStartedAt = millis();   // restart the timer after every flip
                    }
                    else
                    {
                        digitalWrite(PIN_YELLOW, HIGH); // if low, invert to high
                        m_flashStartedAt = millis();
                    }
                }
            }
    }
}

void TrafficSignal::RedInterval() {
    digitalWrite(PIN_RED, HIGH);   // turn on
    digitalWrite(PIN_YELLOW, LOW); // turn off
    digitalWrite(PIN_GREEN, LOW);  // turn off
  
    // sunsetted delay() in favor of millis(), delay() stops the whole program just to keep the light on which is NOT good!
    // delay(RED_TIME); // keep red light on during a period of time
}

void TrafficSignal::YellowInterval() {
    digitalWrite(PIN_RED, LOW);    // turn off red
    digitalWrite(PIN_YELLOW, HIGH); // turn on yellow
    digitalWrite(PIN_GREEN, LOW); // turn off green
}

void TrafficSignal::GreenInterval() {
    digitalWrite(PIN_RED, LOW);    // turn off red
    digitalWrite(PIN_YELLOW, LOW); // turn off yellow
    digitalWrite(PIN_GREEN, HIGH); // turn on green
}

// [TEMPORARY] for pentesting purposes (intentional lack of bounds checking)
// realistically this would be used for police control
// but requires a lock flag to prevent unauthorized changes
void TrafficSignal::SetCurrentPhase(int phase) {
    m_currentPhase = phase;
}