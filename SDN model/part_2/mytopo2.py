"""Custom topology example

Adding the 'topos' dict with a key/value pair to generate our newly defined
topology enables one to pass in '--topo=mytopo' from the command line.
"""

from mininet.topo import Topo

class MyTopo2( Topo ):
    "Simple topology example."

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        H3 = self.addHost( 'h3',ip="10.0.1.2",defaultRoute="via 10.0.1.1" )
        H4 = self.addHost( 'h4',ip="10.0.1.3",defaultRoute="via 10.0.1.1" )
        H5 = self.addHost( 'h5',ip="10.0.2.2",defaultRoute="via 10.0.2.1" )
        Switch1 = self.addSwitch( 's1' )
        Switch2 = self.addSwitch( 's2' ) 
       

        # Add links
        self.addLink( H3, Switch1 )
        self.addLink( H4, Switch1 )
        self.addLink( H5, Switch2 )
        self.addLink( Switch1, Switch2 )

topos = { 'mytopo2': ( lambda: MyTopo2() ) }
