unsigned long t = 0;                   // Current temp set 0
unsigned long t1 = 0;                  // Current temp set 1
unsigned long dt = 0;                  // Temporal difference 0
unsigned long dt1 = 0;                 // Temporal difference 1

long T_wave = 1000;                   // Define wave period
long offset_wave = T_wave;            // Define wave offset
long T_index = 2000;                  // Define index period

bool stato1 = true;                  // Flag state for square wave 1
bool stato2 = true;                  // Flag state for square wave 2
bool stato3 = false;                  // Flag state for square wave 3
bool sequence = true;                 // Check flag
bool index_state = false;             // Flag for index call

int counter = 0;                      // Counter for index

//////////////////////// SETUP /////////////////////////////////

void setup() {

    pinMode(D5, OUTPUT);                // Setup as an OUTPUT pin
    pinMode(D4, OUTPUT);                // Setup as an OUTPUT pin  
    pinMode(D9, OUTPUT);                // Setup as an OUTPUT pin  
    Serial.begin(9600);
}

//////////////////////// LOOP /////////////////////////////////

void loop() {

    Wave_generator();
    index_generator();

    if (counter >= 3000)
    {
        index_state = true;
        counter = 0;
        t1 = micros();
    }
}

//////////////////////////////////////////////////////////////

void Wave_generator() {
    dt = micros() - t;                               // Update time

    if ((dt > T_wave) && (sequence == true))
    {
        stato1 = !stato1;                              // Change state
        digitalWrite(D5, stato1);                      // Update output
        sequence = false;                              // Update flag           
    }
    if (dt > (T_wave + offset_wave))
    {
        stato2 = !stato2;                              // Change state
        digitalWrite(D4, stato2);                      // Update output
        t = micros();                                  // Update time
        sequence = true;                               // Update flag 
        counter++;                                     // Increment counter
    }
}

void index_generator() {
    if (index_state == true)
    {
        digitalWrite(D9, HIGH);                        // Set index pin status true
        Index_timing();                                // Call timing function for index signal
    }
}

void Index_timing() {
    dt1 = micros() - t1;                            // Check the time difference, if dt1 is more then definition of T_index change output status 
    if (dt1 >= T_index)
    {
        digitalWrite(D9, LOW);                        // Set index pin status false
        index_state = false;                          // Update index flag 
    }
}
