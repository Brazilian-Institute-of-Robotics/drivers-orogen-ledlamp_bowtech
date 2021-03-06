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
    if (!_io_port.get().empty())
        lamps.openURI(_io_port.value());

    setDriver(&lamps);

    if (! TaskBase::configureHook())
        return false;

    ledlist = _led_list.get();
    for (size_t i = 0; i < ledlist.size(); ++i)
    {
        if(ledlist[i].light_level<0.0 || ledlist[i].light_level>1.0)
        {
            RTT::log(RTT::Error) << "light_level range in config file should be [0.00, 1.00]" << RTT::endlog();
            return false;
        }
        if(ledlist[i].power_up_light_level<0.0 || ledlist[i].power_up_light_level>1.0)
        {
            RTT::log(RTT::Error) << "power_up_light_level range in config file should be [0.00, 1.00]" << RTT::endlog();
            return false;
        }
        lamps.setPowerUpLightLevel(ledlist[i].power_up_light_level, ledlist[i].address);
        usleep(100000);
        lamps.setLightLevel(ledlist[i].light_level, ledlist[i].address);
        usleep(100000);
    }

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}

void Task::processIO()
{

}

void Task::updateHook()
{
    TaskBase::updateHook();

    std::vector<double> led_level;
    if(_led_input.read(led_level) == RTT::NewData)
    {
        if(ledlist.size()!=led_level.size())
        {
            exception(WRONG_INPUT_SIZE);
            return;
        }
        for (size_t i = 0; i < ledlist.size(); ++i)
        {
            if(led_level[i]<0.0 || led_level[i]>1.0)
            {
                exception(INPUT_RANGE_EXCEEDED);
                return;
            }
            lamps.setLightLevel(led_level[i], ledlist[i].address);
            usleep(100000);
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
