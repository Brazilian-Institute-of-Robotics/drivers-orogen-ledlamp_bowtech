/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace ledlamp_bowtech;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    /* Opens serial port */
    lamps.openSerial(_port.get(), _baud_rate.get());

    led_list = _led_list.get();

    light_level_all  = _light_level_all.get();

    /* Sets initializing properties of the lamps */
    for (int i = 0; i < led_list.size(); ++i)
    {
    	lamps.setPowerUpLightLevel(led_list[i].power_up_light_level, led_list[i].address);
    	usleep(100000);
    	lamps.setLightLevel(led_list[i].light_level, led_list[i].address);
    }

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    if (light_level_all != _light_level_all.get())
    {
    	light_level_all = _light_level_all.get();

    	/* This if-statement will set the light level of all lamps to the value
    	 * specified in the property _light_level_all */
    	if(light_level_all > 0)
    	{
    		lamps.setLightLevel(light_level_all);

    		for(int i = 0; i < led_list.size(); i++)
    			led_list[i].light_level = light_level_all;

    		_led_list.set(led_list);
    	}
    }
    else
    {
    	for(int i = 0; i < led_list.size(); i++)
    	{
    		/* If one of the lamps light level property has changed, the
    		 * property _light_level_all will be set as negative, and the lamps'
    		 * light level will be set individually */
    		if(led_list[i].light_level != _led_list.get()[i].light_level)
    		{
    			light_level_all = -1;
    			_light_level_all.set(light_level_all);
    			led_list[i].light_level = _led_list.get()[i].light_level;

    			lamps.setLightLevel(led_list[i].light_level, led_list[i].address);
    		}
    	}
    }

}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
    lamps.close();
}
