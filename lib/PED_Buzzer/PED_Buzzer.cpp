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
    switch (state) {
        case 0:
            m_currentState = OFF;
            noTone(PIN_BUZZER); // [FIX] Instantly stop any active tone when turning off
            break;
        case 1:
            m_currentState = BURST;
            noTone(PIN_BUZZER); // [FIX] Clear any residual tone before starting burst
            m_nextEventTime = millis();    
            m_burstStartedAt = millis(); 
            m_burstCycleCt = 0; 
            m_isBurstActive = true; 
            break;
        case 2:
            m_currentState = COUNTDOWN;
            noTone(PIN_BUZZER); // [FIX] Clear residual tone before starting countdown pings
            m_nextEventTime = millis();    
            break;
        case 3:
            m_currentState = IDLE;
            noTone(PIN_BUZZER); // [FIX] Clear residual tone for IDLE state
            m_nextEventTime = millis();    
            break;
        default:
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

    if (m_burstCycleCt >= MAX_BURSTS) {
        noTone(PIN_BUZZER); // Stop sound completely
        ChangeState(2);
        return;
    }

    if (m_isBurstActive) {
        if (currentMillis - m_burstTimer >= BURST_ACTIVE_INT) {
            noTone(PIN_BUZZER); 
            m_isBurstActive = false; 
            m_burstTimer = currentMillis; 
            return;
        }

        // Fire 800 Hz tone tick
        if (currentMillis >= m_nextEventTime) {
            tone(PIN_BUZZER, 800); // Generate 800 Hz square wave
            m_buzzerStartedAt = currentMillis;
            m_pulseOffTime = m_buzzerStartedAt + PULSE_DURATION;
            m_nextEventTime += BURST_INTERVAL;
        }

        // Stop the short beep after PULSE_DURATION (e.g., 40ms)
        if (m_pulseOffTime > 0 && currentMillis >= m_pulseOffTime) {
            noTone(PIN_BUZZER);
            m_pulseOffTime = 0;
        }
    } else {
        noTone(PIN_BUZZER);
        
        if (currentMillis - m_burstTimer >= BURST_PAUSE_INT) {
            m_burstCycleCt++;          
            m_isBurstActive = true;       
            m_burstTimer = currentMillis; 
            m_nextEventTime = currentMillis; 
        }
    }
}

    /*
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
    */

void PED_Buzzer::PingHandler() {
    unsigned long currentMillis = millis();

    if (currentMillis >= m_nextEventTime) {
        tone(PIN_BUZZER, 800); // 800 Hz single beep
        m_buzzerStartedAt = currentMillis;
        m_pulseOffTime = m_buzzerStartedAt + PULSE_DURATION;
        m_nextEventTime += COUNT_INTERVAL; 
    }
    
    if (m_pulseOffTime > 0 && currentMillis >= m_pulseOffTime) {
        noTone(PIN_BUZZER);
        m_pulseOffTime = 0; 
    }
}