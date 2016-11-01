#! /usr/bin/env ruby
# -*- coding: utf-8 -*-
# If you want to start the Microsoft Life Cam or the Gumstix camera e-CAM32
# you should use the corresponding ruby run-script. 

require 'orocos'
include Orocos
Orocos.initialize

Orocos.run "ledlamp_bowtech::Task" => "lamp" do

    #Orocos.log_all

    lamp = TaskContext.get_provides 'ledlamp_bowtech::Task'
    lamp.apply_conf_file('./ConfigFiles/ledlamp.yml',['default'])

    lamp.configure
    lamp.start

    # writer example:
    input_port = lamp.led_input
    writer = input_port.writer
    sample = writer.new_sample
    sample = [0.40, 0.40, 0.30, 0.20] #led1 at 40%, led2 at 40%, led3 at 30% and led4 at 20%
    writer.write(sample)

    Orocos.watch(lamp)
end
   
