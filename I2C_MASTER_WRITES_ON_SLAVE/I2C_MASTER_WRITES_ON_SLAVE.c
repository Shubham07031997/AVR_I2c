#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#include<lcdavr.h>
//##################### I2C WRITE ################

void i2c_write(unsigned char data)
{
TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN);
while((TWCR & (1<<TWINT))==0);
}


//###################### I2C START ###############

void i2c_start()
{
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while((TWCR & (1<<TWINT))==0);
}

//###################### I2C STOP ################

void i2c_stop()
{
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

//###################### I2C INIT ################

void i2c_init()
{
TWSR=0X00;   // SET PRESCALER BITS TO ZERO
TWBR=0X47;   // SCL FREQUENCY IS 50K FOR XTAL=8M
TWCR=0X04;   // ENABLE THE TWI MODULE
}

//##################### VOID MAIN ################
char dataa;
int main()
{DDRB=0xff;
lcd_init();
i2c_init();
i2c_start();                //TRANSMIT START CONDITION
i2c_write(0XA0);      // TRANSMIT SLA + W(0)
i2c_write(0b11110000);      // TRANSMIT DATA
i2c_stop();                 //TRANSMIT STOP CONDITION
while(1)
{
dataa=TWDR;
PORTB=dataa;
}
return 0;

}
