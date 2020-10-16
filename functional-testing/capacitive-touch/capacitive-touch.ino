
int touch=0;

void setup() {
    Serial.begin(115200);
    // touch_pad_filter_start(T8);
    // touch_pad_set_filter_period((32));
}

void loop() {  
    touch= touchRead((T8));    
    Serial.println(touch);
    delay(100);
}
