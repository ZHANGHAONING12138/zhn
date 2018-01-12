"""Custom topology example
Adding the 'topos' dict with a key/value pair to generate our newly defined
topology enables one to pass in '--topo=mytopo' from the command line.
"""

from mininet.topo import Topo

class MyTopo( Topo ):
    "Simple topology example."

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        H1 = self.addHost( 'h1', ip = "10.0.1.100", defaultRoute = "via 10.0.1.1" )
        H2 = self.addHost( 'h2', ip = "10.0.2.100", defaultRoute = "via 10.0.2.1" )
        H3 = self.addHost( 'h3', ip = "10.0.3.100", defaultRoute = "via 10.0.3.1" )       
        Switch = self.addSwitch( 's1' )

        # Add links
        self.addLink( H1, Switch )
        self.addLink( H2, Switch )
        self.addLink( H3, Switch )


topos = { 'mytopo': ( lambda: MyTopo() ) }
