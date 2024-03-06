unsigned long t= 0;                   // Current temp set 0
unsigned long t1= 0;                  // Current temp set 1
unsigned long dt= 0;                  // Temporal difference 0
unsigned long dt1= 0;                 // Temporal difference 1

long T_wave = 1000;                   // Define wave period
long offset_wave = T_wave;            // Define wave offset
long T_index = 2000;                  // Define index period

bool stato1 = false;                  // Flag state for square wave 1
bool stato2 = false;                  // Flag state for square wave 2
bool stato3 = false;                  // Flag state for square wave 3
bool sequence = true;                 // Check flag
bool index_state = false;             // Flag for index call

int counter = 0;                      // Counter for index

void setup() {
  
  pinMode(D5, OUTPUT);                // Setup as an OUTPUT pin
  pinMode(D4, OUTPUT);                // Setup as an OUTPUT pin  
  pinMode(D9, OUTPUT);                // Setup as an OUTPUT pin  
  Serial.begin(9600);
}

void loop() {

  t1 = micros();                      // Update time 1
  
  Wave_generator();
  index_generator();
  Index_timing();
  
  if (counter >= 3000){ index_state = true; }
  
//  debug flag code part
//  if (index_state != 0 ){
//    Serial.print('1');
//    }else{Serial.print('0');} 
//  Serial.print("\t");
//  Serial.println(counter);
    
  }

void Wave_generator() {
  dt = micros() - t;                               // Update time
  
  if ((dt > T_wave) && (sequence == true)){
    stato1 = !stato1;                              // Change state
    digitalWrite(D5, stato1);                      // Update output
    sequence = false;                              // Update flag                
  }
    if (dt > (T_wave + offset_wave)){
     stato2 = !stato2;                             // Change state
     digitalWrite(D4, stato2);                     // Update output
     t = micros();                                 // Update time
     sequence = true;                              // Update flag
     counter++;                                    // Increment counter
   } 
}


void index_generator(){
// this function reset the counter and t1 variable (necessary to manage index duration)
  if (index_state == true){
    t1 = 0;                                        // Reset t1 cariable
    counter = 0;                                   // Reset counter
    index_state = false;}                          // Update index_state flag
 }  

void Index_timing(){
// this function manage the duration of index signal
    if (t1 >= T_index) {                           
        digitalWrite(D9, LOW);                     // This part manage the index signal
        } else {
        digitalWrite(D9, HIGH);}
 }
