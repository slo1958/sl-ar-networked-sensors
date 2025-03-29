//
// This file must be the last in the sketchbook !!


void writeInputBuffer(){
    startWriting();
    mySerial.print(inputBuffer);
    doneWriting();
}

void echoInputBuffer(){
    //startWriting();
    Serial.print(inputBuffer);
    //doneWriting();
}
