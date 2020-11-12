#include "PushButton.h"

/******************************************************************************
 *
 * CONSTRUTOR
 * Salva pino da push button;
 * Salva a lógica de ligação da push button (positiva ou negativa);
 * Salva delay estabelecido para debounce do botão (limite de 2s).
 * Configura pino do botão como entrada.
 * 
 * Lógica (_logic):
 *        true = lógica positiva (botão apertado vai para HIGH)
 *        false = lógica negativa (botão apertado vai para LOW)
 * 
 *****************************************************************************/
PushButton::PushButton(int pin, unsigned long delay, bool defaultState){
    pinMode(pin, INPUT);       
    _pin = pin;                             
    _logic = defaultState;
    _lastDebounceTime = 0;
    _longDelay = 2500;
    if(delay > 2000)
        _delay = 2000;
    else
        _delay = delay;
     
     // Inicializa variável _lastButtonState 
     // Com o que seria o valor do botão não pressionado (depende da lógica usada)
     if(_logic)
        _lastButtonState = LOW;
     else
        _lastButtonState = HIGH;
}


/******************************************************************************
 *
 * Método que indica se o botão foi apertado ou não.
 * Possui 2 blocos distintos: um para lógica positiva e outro para negativa.
 * 
 * Retorna true se o botão estiver pressionado após o tempo de debounce
 * 
 *****************************************************************************/
bool PushButton::isPressed(){ 

    //Se a lógica de ligação for POSITIVA (botão apertado = HIGH)
    if(_logic){
        int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _delay){
            if(buttonState == HIGH){
                _lastButtonState = buttonState;
                return true;
            }
        }
        _lastButtonState = buttonState;
        return false;
    }

    //Se a lógica de ligação for NEGATIVA (botão apertado = LOW)
    else {
    int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _delay){
            if(buttonState == LOW){
                _lastButtonState = buttonState;
                return true;
            }
        }
        _lastButtonState = buttonState;
        return false;
    }
}


bool PushButton::longPress(){
    
    //Se a lógica de ligação for POSITIVA (botão apertado = HIGH)
    if(_logic){
        int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _longDelay ){
            if(buttonState == HIGH){
                _lastButtonState = buttonState;
                return true;
            }
        }
        _lastButtonState = buttonState;
        return false;
    }

    //Se a lógica de ligação for NEGATIVA (botão apertado = LOW)
    else {
    int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _longDelay ){
            if(buttonState == LOW){
                _lastButtonState = buttonState;
                return true;
            }
        }
        _lastButtonState = buttonState;
        return false;
    }

}


/*
 * Retorna:
 * 0    - não apertado
 * 1    - click simples (click menor que 3 segundos)
 * -1   - click longo (duração de 3 segundos) 
 */
int PushButton::dualFunction(){
    
    //Se a lógica de ligação for POSITIVA (botão apertado = HIGH)
    if(_logic){
        int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _delay ){
            if(buttonState == HIGH){
                //Aguarda botão ser liberado (digitalRead() == LOW)
                //ou estourar o tempo limite para o click longo
                while( digitalRead(_pin) == HIGH && (millis() - _lastDebounceTime) < _longDelay );
                //Se o botão continua apertado, então foi um click longo
                if(digitalRead(_pin) == HIGH){
                    _lastButtonState = HIGH;
                    return -1;                      
                }
                //Se o botão não está mais apertado, então foi um click simples
                else{
                    _lastButtonState = LOW;
                    return 1;
                }
            }
        }
        _lastButtonState = buttonState;
        return 0;
    }

    //Se a lógica de ligação for NEGATIVA (botão apertado = LOW)
    else {
        int buttonState = digitalRead(_pin);

        if(buttonState != _lastButtonState)
            _lastDebounceTime = millis();

        if( (millis() - _lastDebounceTime) > _delay ){
            if(buttonState == LOW){
                //Aguarda botão ser liberado (digitalRead() == HIGH)
                //ou estourar o tempo limite para o click longo
                while( digitalRead(_pin) == LOW && (millis() - _lastDebounceTime) < _longDelay );
                //Se o botão continua apertado, então foi um click longo
                if(digitalRead(_pin) == LOW){
                    _lastButtonState = LOW;
                    return -1;                      
                }
                //Se o botão não está mais apertado, então foi um click simples
                else{
                    _lastButtonState = HIGH;
                    return 1;
                }
            }
        }
        _lastButtonState = buttonState;
        return 0;
    }


}



int PushButton::state(){
    return _lastButtonState;
}