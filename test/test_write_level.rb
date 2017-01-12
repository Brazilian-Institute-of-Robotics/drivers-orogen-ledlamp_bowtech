require 'minitest/spec'
require 'orocos/test/component'
require 'minitest/autorun'
require 'socket'

describe 'ledlamp_bowtech::Task' do

    include Orocos::Test::Component
    start  'led_task', 'ledlamp_bowtech::Task' => 'led_task'
    writer 'led_task', 'led_input', attr_name: 'led_input'

    def driver_remote_port
        1234
    end

    def driver_local_port
        1235
    end

    before do
        @sock = UDPSocket.new
        @sock.bind("127.0.0.1", driver_remote_port)
        led_task.apply_conf_file('ledlamp.yml',['default'])
    end

    after do
        @sock.close
    end

    it 'should not break while configuring, starting, stopping and cleaning up' do
        led_task.configure
        led_task.start
        led_task.stop
        led_task.cleanup
    end

    it 'should fail to configure if light_level > 1.0' do
        newledlist = led_task.led_list
        newledlist[1].light_level = 1.2
        led_task.led_list = newledlist 
        assert_raises(Orocos::StateTransitionFailed) { led_task.configure }
    end

    it 'should fail to configure if light_level < 0.0' do
        newledlist = led_task.led_list 
        newledlist[1].light_level = -0.3
        led_task.led_list = newledlist 
        assert_raises(Orocos::StateTransitionFailed) { led_task.configure }
    end

    it 'should fail to configure if power_up_light_level > 1.0' do
        newledlist = led_task.led_list 
        newledlist[1].power_up_light_level = 1.1
        led_task.led_list = newledlist 
        assert_raises(Orocos::StateTransitionFailed) { led_task.configure }
    end

    it 'should fail to configure if power_up_light_level < 0.0' do
        newledlist = led_task.led_list 
        newledlist[1].power_up_light_level = -2
        led_task.led_list = newledlist 
        assert_raises(Orocos::StateTransitionFailed) { led_task.configure }
    end

    it 'transmitting proper led levels' do
        led_task.configure
        led_task.start

        proper_input = led_task.led_input.new_sample
        proper_input = [0.40, 0.40, 0.30, 0.20]
        led_input.write proper_input
        assert_state_change(led_task, timeout = 2) {|s| s == :RUNNING}
    end

    it 'transmitting few led levels' do
        led_task.configure
        led_task.start

        wrong_input = led_task.led_input.new_sample
        wrong_input = [0.40, 0.40, 0.30]
        led_input.write wrong_input
        assert_state_change(led_task, timeout = 2) {|s| s == :WRONG_INPUT_SIZE}
    end

    it 'transmitting too many led levels' do
        led_task.configure
        led_task.start

        wrong_input = led_task.led_input.new_sample
        wrong_input = [0.40, 0.40, 0.30, 0.20, 0.80]
        led_input.write wrong_input
        assert_state_change(led_task, timeout = 2) {|s| s == :WRONG_INPUT_SIZE}
    end

    it 'exceeding led level' do
        led_task.configure
        led_task.start

        wrong_input = led_task.led_input.new_sample
        wrong_input = [0.40, 1.40, 0.30, 0.20]
        led_input.write wrong_input
        assert_state_change(led_task, timeout = 2) {|s| s == :INPUT_RANGE_EXCEEDED}
    end

    it 'transmitting negative led level' do
        led_task.configure
        led_task.start

        wrong_input = led_task.led_input.new_sample
        wrong_input = [0.40, -0.40, 0.30, 0.20]
        led_input.write wrong_input
        assert_state_change(led_task, timeout = 2) {|s| s == :INPUT_RANGE_EXCEEDED}
    end

end