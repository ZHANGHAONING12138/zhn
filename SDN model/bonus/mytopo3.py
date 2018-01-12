"""Custom topology example

Two directly connected switches plus a host for each switch:

   host --- switch --- switch --- host

Adding the 'topos' dict with a key/value pair to generate our newly defined
topology enables one to pass in '--topo=mytopo' from the command line.
"""

from mininet.topo import Topo

class MyTopo3( Topo ):
    "Simple topology example."

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        H1 = self.addHost( 'h1',ip="10.0.1.100",defaultRoute="via 10.0.1.1" )
        H2 = self.addHost( 'h2',ip="10.0.1.200",defaultRoute="via 10.0.1.1" )
        H3 = self.addHost( 'h3',ip="10.0.2.100",defaultRoute="via 10.0.2.1" )
        H4 = self.addHost( 'h4',ip="10.0.2.200",defaultRoute="via 10.0.2.1" )
        H5 = self.addHost( 'h5',ip="10.0.3.100",defaultRoute="via 10.0.3.1" )
        H6 = self.addHost( 'h6',ip="10.0.3.200",defaultRoute="via 10.0.3.1" )
        H7 = self.addHost( 'h7',ip="10.0.4.100",defaultRoute="via 10.0.4.1" )
        H8 = self.addHost( 'h8',ip="10.0.4.200",defaultRoute="via 10.0.4.1" )
        Switch1 = self.addSwitch( 's1' )
        Switch2 = self.addSwitch( 's2' )
        Switch3 = self.addSwitch( 's3' )
        Switch4 = self.addSwitch( 's4' )
        # Add links
        self.addLink( H1, Switch1 )
        self.addLink( H2, Switch1 )
        self.addLink( H3, Switch2 )
        self.addLink( H4, Switch2 )
        self.addLink( H5, Switch3 )
        self.addLink( H6, Switch3 )
        self.addLink( H7, Switch4 )
        self.addLink( H8, Switch4 )
        self.addLink( Switch1, Switch2 )
        self.addLink( Switch2, Switch3 )
        self.addLink( Switch3, Switch4 )

topos = { 'mytopo3': ( lambda: MyTopo3() ) }
