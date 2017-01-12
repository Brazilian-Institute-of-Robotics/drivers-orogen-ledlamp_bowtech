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

	struct LedLamp
	{
		std::string name;
		uint8_t address;
		float light_level;
		float power_up_light_level;

	};
}

#endif

