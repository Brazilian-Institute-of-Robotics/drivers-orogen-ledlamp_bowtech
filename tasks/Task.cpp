/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <stdexcept>

using namespace ledlamp_bowtech;

Task::Task(std::string const& name)
    : TaskBase(name)
{
    setDriver(&driver);
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
    setDriver(&driver);
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
        driver.openURI(_io_port.value());
    if (! TaskBase::configureHook())
        return false;
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;

    /* Set the initial light level */
    lamps = _lamps.get();
    for (unsigned int i = 0; i < lamps.size(); ++i)
    	driver.setLightLevel(lamps[i].level, lamps[i].address);

    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    std::vector<Lamp> levels;
    while (_levels.readNewest(levels) == RTT::NewData)
    {
        for (unsigned int i = 0; i < levels.size(); ++i)
        {
            int address = levels[i].address;
            if (!levels[i].name.empty())
                address = resolveLightAddress(levels[i].name);

            driver.setLightLevel(levels[i].level, address);
        }
    }
}

void Task::processIO()
{
    // Nothing to do here (or is there ?)
}

uint8_t Task::resolveLightAddress(std::string const& name) const
{
    for (unsigned int i = 0; i < lamps.size(); ++i)
        if (lamps[i].name == name)
            return lamps[i].address;
    throw std::invalid_argument("there is not ligth named " + name);
}

void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    /* Turn the lamps off */
    for (unsigned int i = 0; i < lamps.size(); ++i)
    	driver.setLightLevel(0, lamps[i].address);

    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}

