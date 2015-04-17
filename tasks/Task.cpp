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

    //open serial port
    lamps.openSerial(_port.get(), _baud_rate.get());

    ////////////
    //TODO: test if the informed addresses are valid.
    ///////////

    led_list = _led_list.get();


    for (int i = 0; i < led_list.size(); ++i)
    {
    	lamps.setLightLevel(led_list[i].light_level, led_list[i].address);
    	lamps.setPowerUpLightLevel(led_list[i].power_up_light_level, led_list[i].address);
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
}
