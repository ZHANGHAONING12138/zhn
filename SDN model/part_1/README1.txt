Part_1
1.Abstract
This part contains Create a Learning Switch and Router Exercise. 

2.Code file
mytopo.py   of_tutorial_l3rp1.py   of_tutorial_switch.py

3.Test
Put the mytopo.py into /mininet/mininet/custom/
Create a Learning Switch
Put the of_tutorial_switch.py into /mininet/pox/pox/misc/
open two SSHs, one runs: sudo mn --topo single,3 --mac --switch ovsk --controller remote
the other goes into /mininet/pox, runs: ./pox.py log.level --DEBUG misc.of_tutorial_switch
Router Exercise
Put the of_tutorial_l3rp1.py into /mininet/pox/pox/misc/,
open two SSHs, one goes into /mininet/custom, runs: sudo mn --custom mytopo.py --topo mytopo --mac --controller remote
the other goes into /mininet/pox, runs: ./pox.py log.level --DEBUG misc.of_tutorial_l3rp1



