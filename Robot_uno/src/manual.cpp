#include "manual.h"

void manual()
{
    while (true)
    {
        char command;

        while (!Serial.available())
            ;
        if (Serial.available())
        {
            command = Serial.read();
        }

        if (command == '1')
        {
            forward();
        }
        else if (command == '2')
        {
            backward();
        }
        else if (command == '3')
        {
            Tleft();
        }
        else if (command == '4')
        {
            Tright();
        }
        else if (command == '-')
        {
            toggle_mode();
            break;
        }
        else
        {
            Serial.println("Invalid command");
        }
        delay(100);
        off();
    }
}