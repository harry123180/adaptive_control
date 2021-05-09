
import nidaqmx
t =0
while(True):
    t +=1
    with nidaqmx.Task() as task:
        task.ai_channels.add_ai_voltage_chan("Dev3/ai0")
        task.read()
    if(t>1000):
        break