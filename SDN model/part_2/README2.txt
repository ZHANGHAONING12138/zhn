Part_2
1.Abstract
This part contains Advanced Topology and Create Firewall in bonus 2

2.Code file
mytopo2.py   of_tutorial_l3rp2.py   of_tutorial_l3rp2fire.py

3.Test
Put the mytopo2.py into /mininet/mininet/custom/
Router Exercise
Put the of_tutorial_l3rp2.py and into /mininet/pox/pox/misc/,
open two SSHs, one goes into /mininet/custom, runs: sudo mn --custom mytopo2.py --topo mytopo2 --mac --controller remote
the other goes into /mininet/pox, runs: ./pox.py log.level --DEBUG misc.of_tutorial_l3rp2
Firewall Test
Repeat steps in Router Exercise by using of_tutorial_l3rp2fire.py




