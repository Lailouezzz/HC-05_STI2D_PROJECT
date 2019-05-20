/*
 Name:		HC05_project.ino
 Created:	18/05/2019 16:58:51
 Author: AlzoxX76
*/

#include <SoftwareSerial.h>

#define HC05_TX 13 // TODO : select your TX pin
#define HC05_RX 12 // TODO : select your RX pin
#define DEBUG
#ifdef DEBUG
#define printD(...) Serial.print(__VA_ARGS__)
#define printlnD(...) Serial.println(__VA_ARGS__)
#else
#define printD(x)
#define printlnD(x)
#endif

SoftwareSerial HC05(HC05_RX, HC05_TX);
int16_t pasPos = 0;


void setStepByStepEngine(int16_t pos);

void setup()
{
	pinMode(HC05_RX, INPUT);
	pinMode(HC05_TX, OUTPUT);
	HC05.begin(9600);
	Serial.begin(9600);
	// TODO : implémenter le calibrage du moteur pas à pas
}

void loop()
{
	if (HC05.available())
	{
		uint8_t opt;
		HC05.readBytes(&opt, 1); // Lecture du premier octet qui est l'option
		printD("OPTION : ");
		printlnD(opt, DEC);
		if (opt == 0) // Pince
		{
			uint8_t buf;
			while(!HC05.available()) {} // Wait for 1 byte
			HC05.readBytes(&buf, 1);
			if (buf == 1) // buf = 1 si la pince doit s'ouvrir
			{
				printlnD("OPEN THE CLAMP");
				// TODO : implémenter l'ouverture de la pince
			}
			else
			{
				printlnD("CLOSE THE CLAMP");
				// TODO : implémenter l'ouverture de la pince
			}
		}
		else if (opt == 1) // Rotation (moteur pas à pas)
		{
			int16_t pos;
			while (HC05.available() < 2) {} // Wait for 2 bytes
			HC05.readBytes(reinterpret_cast<uint8_t*>(&pos), 2);
			setStepByStepEngine(pos); // Pos est la position du moteur pas à pas à partir du point de départ
			printD("STEP BY STEP ENGINE POS : ");
			printlnD(pos);
		}
		else if (opt == 2) // Hauteur (servomoteur)
		{
			uint8_t pos;
			while (!HC05.available()) {} // Wait for 1 byte
			HC05.readBytes(&pos, 1);
			printD("SERVOMOTOR HEIGHT POS : ");
			printlnD(static_cast<unsigned int>(pos)); // Obligé de caster sinon au dessus de 127 pos est prit comme un signé
			if (pos > 120)
			{
				printlnD("ERROR POS HIGHER THAN 120");
			}
			else
			{
				// TODO : implémenter le mouvement du servomoteur
			}
		}
		else if (opt == 3) // Longueur (servomoteur)
		{
			uint8_t pos;
			while (!HC05.available()) {} // Wait for 1 byte
			HC05.readBytes(&pos, 1);
			printD("SERVOMOTOR LENGHT POS : ");
			printlnD(static_cast<unsigned int>(pos)); // Obligé de caster sinon au dessus de 127 pos est prit comme un signé
			if (pos > 170 || pos < 40)
			{
				printlnD("ERROR POS HIGHER THAN 170 OR SMALLER THAN 40");
			}
			else
			{
				// TODO : implémenter le mouvement du servomoteur
			}
		}
	}
}

void setStepByStepEngine(int16_t pos)
{
	int16_t nbPas = pos - pasPos;
	// TODO : implémenter l'application des step
	pasPos = pos;
}
