Bonus
1.Abstract
This part contains Advanced Topology in bonus 1. 

2.Code file
mytopo3.py   of_tutorial_l3rp3.py

3.Test
Put the mytopo3.py into /mininet/mininet/custom/
Router Exercise
Put the of_tutorial_l3rp3.py and into /mininet/pox/pox/misc/,
open two SSHs, one goes into /mininet/custom, runs: sudo mn --custom mytopo3.py --topo mytopo3 --mac --controller remote
the other goes into /mininet/pox, runs: ./pox.py log.level --DEBUG misc.of_tutorial_l3rp3



