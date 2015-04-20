#! /usr/bin/env ruby
# -*- coding: utf-8 -*-
# If you want to start the Microsoft Life Cam or the Gumstix camera e-CAM32
# you should use the corresponding ruby run-script. 

require 'orocos'
require 'vizkit'
include Orocos
Orocos.initialize

Orocos.run "ledlamp_bowtech::Task" => "lamp" do

    #Orocos.log_all

    lamp = TaskContext.get_provides 'ledlamp_bowtech::Task'
    lamp.apply_conf_file('./ConfigFiles/ledlamp.yml',['default'])

    lamp.configure
    lamp.start

    Vizkit.display lamp
    Vizkit.exec
end
   
