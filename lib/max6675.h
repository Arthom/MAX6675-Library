#ifndef _MAX6675_H
#define _MAX6675_H

	class MAX6675 {
		private:
			uint8_t CS = 0, MISO = 0, SCK = 0;
		public:
			void begin(uint8_t csPin, uint8_t mosiPin, uint8_t sckPin);
			char SPIRead(void);
			double convertToCelsius(void);
	};

#endif