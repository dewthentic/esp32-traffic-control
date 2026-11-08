#include "PED_Buzzer.h"
#include <Arduino.h> // Ensure Arduino core functions like digitalWrite and millis are available

PED_Buzzer::PED_Buzzer() {
    PIN_BUZZER = 25;
}

/*
PED_Buzzer::PED_Buzzer(int buzzerPin) {
    PIN_BUZZER = buzzerPin;
}
*/

void PED_Buzzer::Initialize() {
    pinMode(PIN_BUZZER, OUTPUT); // [BUG FIX] Added pinMode initialization so the pin actually drives current.
    m_isBuzzing = false;
    m_currentState = OFF;        // [BUG FIX] Explicitly initialize state on startup.
}

void PED_Buzzer::Update() {
    // update loops continuously per second
    // use it as a router to track current enum state
    // and trigger the correct function at the correct time
    if (m_currentState == BURST) {
        BurstHandler();
    } else if (m_currentState == COUNTDOWN || m_currentState == IDLE) { 
        // [BUG FIX] Included IDLE here so the router actually processes IDLE state pings.
        PingHandler();
    }
}

// allows external functions to change the state of the buzzer
void PED_Buzzer::ChangeState(int state) {
    // bounds checking on requested state
    // we won't trigger functions here, 
    // update() is responsible for listening
    switch (state) {
        case 0:
            m_currentState = OFF;
            digitalWrite(PIN_BUZZER, LOW); // [OPTIMIZATION] Ensure buzzer turns off immediately on state switch.
            break;
        case 1:
            m_currentState = BURST;
            m_nextEventTime = millis();    // [BUG FIX] Reset timer so the first burst tick fires immediately.
            break;
        case 2:
            m_currentState = COUNTDOWN;
            m_nextEventTime = millis();    // [BUG FIX] Reset timer so the first countdown ping fires immediately.
            break;
        case 3:
            m_currentState = IDLE;
            m_nextEventTime = millis();    // [BUG FIX] Reset timer for immediate IDLE pinging.
            break;
        default:
            // keep the current state
            break;
    }
}

void PED_Buzzer::TriggerPing() {
    // [NOTE ON METHOD]: Since Update() already handles calling PingHandler() continuously 
    // when state is COUNTDOWN or IDLE, manual triggering functions should just 
    // change the state rather than trying to loop or call handlers directly.
    if (m_currentState == COUNTDOWN) { 
        // [BUG FIX] Changed assignment '=' to comparison '=='.
        // [NOTE] Removed the blocking code; let Update() handle execution non-blockingly.
    }
}

void PED_Buzzer::TriggerBurst(int amt) {
    // [NOTE ON METHOD]: Instead of a blocking loop or single-fire call, 
    // delegate state management to ChangeState() and let Update() drive the timing.
    ChangeState(1); 
    
    // [NOTE ON 'amt']: If you want to limit the burst to a specific count ('amt'), 
    // store 'amt' in a private member variable and decrement it inside BurstHandler().
}

// private helper functions
void PED_Buzzer::BurstHandler() {
    unsigned long currentMillis = millis();

    // 1. Time to turn the beep ON
    if (currentMillis >= m_nextEventTime) {
        digitalWrite(PIN_BUZZER, HIGH);
        m_buzzerStartedAt = currentMillis;
        m_pulseOffTime = m_buzzerStartedAt + PULSE_DURATION;
        
        // [BUG FIX / OPTIMIZATION]: Advance the deadline immediately upon firing 
        // using the rolling target method (+=) to prevent timing drift.
        m_nextEventTime += BURST_INTERVAL; 
    }
    
    // 2. Time to turn the beep OFF
    // [BUG FIX]: Added a safeguard (like checking if pulse is active or resetting m_pulseOffTime) 
    // so this block doesn't repeatedly execute across multiple loop cycles and mess up timing.
    if (m_pulseOffTime > 0 && currentMillis >= m_pulseOffTime) {
        digitalWrite(PIN_BUZZER, LOW);
        m_pulseOffTime = 0; // Prevent re-triggering this block until the next pulse starts
    }
}

void PED_Buzzer::PingHandler() {
    unsigned long currentMillis = millis();

    // 1. Time to turn the ping ON
    if (currentMillis >= m_nextEventTime) {
        digitalWrite(PIN_BUZZER, HIGH);
        m_buzzerStartedAt = currentMillis;
        m_pulseOffTime = m_buzzerStartedAt + PULSE_DURATION;
        
        // [BUG FIX]: Use rolling target addition (+=) for 1-second countdown intervals.
        m_nextEventTime += COUNT_INTERVAL; 
    }
    
    // 2. Time to turn the ping OFF
    if (m_pulseOffTime > 0 && currentMillis >= m_pulseOffTime) {
        digitalWrite(PIN_BUZZER, LOW);
        m_pulseOffTime = 0; // Reset off-time tracker until next cycle
    }
}