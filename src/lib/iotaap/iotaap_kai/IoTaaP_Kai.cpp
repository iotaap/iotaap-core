#include "IoTaaP_Kai.h"

/**
 * @brief Construct a new IoTaaP_Kai::IoTaaP_Kai object
 * 
 */
IoTaaP_Kai::IoTaaP_Kai()
{
}

/**
 * @brief Attaches servo motors
 * 
 * @param servo1Pin Top left servo
 * @param servo2Pin Top right servo
 * @param servo3Pin Bottom left servo
 * @param servo4Pin Bottom right servo
 */
void IoTaaP_Kai::init(int servo1Pin, int servo2Pin, int servo3Pin, int servo4Pin)
{
    this->_servo1.attach(servo1Pin);
    this->_servo2.attach(servo2Pin);
    this->_servo3.attach(servo3Pin);
    this->_servo4.attach(servo4Pin);
}

/**
 * @brief Initial position
 * 
 */
void IoTaaP_Kai::home()
{
    this->_count1 = 90;
    this->_count2 = 90;
    this->_count3 = 90;
    this->_count4 = 90;

    this->_pos1 = _count1;
    this->_pos2 = _count2;
    this->_pos3 = _count3;
    this->_pos4 = _count4;

    this->_servo1.write(this->_pos1);
    this->_servo2.write(this->_pos2);
    this->_servo3.write(this->_pos3);
    this->_servo4.write(this->_pos4);
}

/**
 * @brief Normal walk
 * TODO - Implement backward walking
 * @param T Servo step time (lower value = higher speed)
 * @param loops Number of step cycles
 * @param dir Walking direction (to be implemented)
 */
void IoTaaP_Kai::walk(unsigned long T, uint16_t loops, uint16_t dir)
{
    this->_executedLoops = 0;

    int servo1pos[] = {90, 70, 110, 90};
    int servo3pos[] = {110, 65, 110, 65};

    int servo2pos[] = {90, 70, 110, 90};
    int servo4pos[] = {110, 65, 110, 65};

    while (this->_executedLoops < loops)
    {

        if (this->_c4 == 3)
        {
            this->_c1 = 0;
            this->_c2 = 0;
            this->_c3 = 0;
            this->_c4 = 0;
            this->_executedLoops++;
        }

        if ((millis() - this->_servoTime) >= T)
        {
            this->_servoTime = millis();

            if (this->_count1 == this->_pos1 && this->_c1 != (sizeof(servo1pos) / sizeof(int)))
            {

                this->_pos1 = servo1pos[this->_c1];
                this->_c1++;
            }

            if (this->_count2 == this->_pos2 && this->_c2 != (sizeof(servo2pos) / sizeof(int)))
            {

                this->_pos2 = servo2pos[this->_c2];
                this->_c2++;
            }

            if (this->_count3 == this->_pos3 && this->_c3 != (sizeof(servo3pos) / sizeof(int)))
            {

                this->_pos3 = servo3pos[this->_c3];
                this->_c3++;
            }

            if (this->_count4 == this->_pos4 && this->_c4 != (sizeof(servo4pos) / sizeof(int)))
            {

                this->_pos4 = servo4pos[this->_c4];
                this->_c4++;
            }

            if (this->_count1 != this->_pos1)
            {
                if (this->_count1 > this->_pos1)
                {
                    this->_count1--;
                }
                else if (this->_count1 < this->_pos1)
                {
                    this->_count1++;
                }

                this->_servo1.write(this->_count1);
            }

            if (this->_count2 != this->_pos2)
            {
                if (this->_count2 > this->_pos2)
                {
                    this->_count2--;
                }
                else if (this->_count2 < this->_pos2)
                {
                    this->_count2++;
                }
                this->_servo2.write(this->_count2);
            }

            if (this->_count3 != this->_pos3)
            {
                if (this->_count3 > this->_pos3)
                {
                    this->_count3--;
                }
                else if (this->_count3 < this->_pos3)
                {
                    this->_count3++;
                }
                this->_servo3.write(this->_count3);
            }

            if (this->_count4 != this->_pos4)
            {
                if (this->_count4 > this->_pos4)
                {
                    this->_count4--;
                }
                else if (this->_count4 < this->_pos4)
                {
                    this->_count4++;
                }
                this->_servo4.write(this->_count4);
            }
        }
    }
    this->home();
}