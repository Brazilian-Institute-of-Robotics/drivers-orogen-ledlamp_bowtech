#ifndef ledlamp_bowtech_TYPES_HPP
#define ledlamp_bowtech_TYPES_HPP

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */
#include <stdint.h>
#include <string>

namespace ledlamp_bowtech {

	struct LedAttributes
	{
		uint8_t address;
		uint8_t light_level;
		uint8_t power_up_light_level;
	};

	struct LedLamp
	{
		std::string name;
		LedAttributes attribute;
	};
}

#endif

